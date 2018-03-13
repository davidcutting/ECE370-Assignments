/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 3
    March 14, 2018

*/

/**

ClosedHash

*/
#ifndef CLOSEDHASH_H
#define CLOSEDHASH_H

class ClosedHash {
    public:

        ClosedHash(int size, int a, int b, int c) {
            closedhashb = size;
            table = new std::string(size);
            for(int i = 0; i < size; i++) {
                table[i] = "";
            }
            this->a = a;
            this->b = b;
            this->c = c;
        }

        int linear_find(std::string value) {
            int hash = get_hash(value);
            int count = 0;
            while(table[hash] != "") {
                hash = (hash + 1) % closedhashb;
                count++;
            }
            return count;
        }

        void linear_put(std::string value) {
            int hash = get_hash(value);
            while(table[hash] != "") {
                hash = (hash + 1) % closedhashb;
            }
            table[hash] = value;
        }

        int get_size() {
            return this->closedhashb;
        }

    private:

        std::string* table;
        int a;
        int b;
        int c;
        int closedhashb;

        int get_hash(std::string value) {
            return (a * value[0] + b * value[1] + c * value[2]) % closedhashb;
        }
};

#endif

/**

main.cpp

*/

int read_file(std::string* file_content, char* file_name) {
    std::fstream file;
    file.open(file_name, std::ios::in);
    int counter = 0;
    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            if(line == "")
                continue;
            file_content[counter] = line;
            counter++;
        }
    }
    file.close();
    return counter;
}

std::vector<std::string> split(std::string delimiter, std::string s) {
    int last = 0;
    int next = 0;
    std::vector<std::string> chopped;
    while((next == s.find(delimiter, last)) != string::npos) {
        chopped.append(s.substr(last, next - last));
        last = next + delimiter.length();
    }
    chopped.append(s.substr(last));
}

int main() {
    std::string contents[60];
    char file_name[] = "a3.txt";
    read_file(contents, file_name);
    int a = -1;
    int b = -1;
    int c = -1;
    for(auto s : split(contents[0])) {
        if(a == -1) a = s;
        else if(b == -1) b = s;
        else if(c == -1) c = s;
    }
    ClosedHash c_hash(60, a, b, c);
}
