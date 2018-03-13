/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 3
    March 14, 2018

*/

#include <cstddef>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

/**

ClosedHash

*/
#ifndef CLOSEDHASH_H
#define CLOSEDHASH_H

class ClosedHash {
    public:

        ClosedHash(int size, int a, int b, int c) {
            this->a = a;
            this->b = b;
            this->c = c;
            closedhashb = size;
            table = new std::string[size];
            for(int i = 0; i < size; i++) {
                table[i] = "";
            }
        }

        int linear_find(std::string value) {
            if(value == "") return -1;
            int hash = get_hash(value);
            int count = 0;
            while(table[hash] != "") {
                hash = (hash + 1) % closedhashb;
                count++;
            }
            return count;
        }

        void linear_put(std::string value) {
            if(value == "") return;
            int hash = get_hash(value);
            while(table[hash] != "") {
                hash = (hash + 1) % closedhashb;
            }
            table[hash] = value;
            std::cout << "Put " << value << ": " << hash << '\n';
        }

        int get_size() {
            return this->closedhashb;
        }

    private:

        int a;
        int b;
        int c;
        int closedhashb;
        std::string* table;

        int get_hash(std::string value) {
            return (a * value[0] + b * value[1] + c * value[2]) % closedhashb;
        }
};

#endif

/**

main.cpp

*/
std::string to_uppercase(std::string& lower) {
    std::string upper = "";
    for(char c : lower) {
        upper += std::toupper(c);
    }
    return upper;
}

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
            file_content[counter] = to_uppercase(line);
            counter++;
        }
    }
    file.close();
    return counter;
}

std::vector<std::string> split(std::string delimiter, std::string s) {
    size_t last = 0;
    size_t next = 0;
    std::vector<std::string> chopped;
    while((next = s.find(delimiter, last)) != std::string::npos) {
        chopped.push_back(s.substr(last, next - last));
        last = next + delimiter.length();
    }
    chopped.push_back(s.substr(last));
    return chopped;
}

int main() {
    std::string contents[60];
    char file_name[] = "a3.txt";
    read_file(contents, file_name);
    int a = stoi(split(" ", contents[0])[0]);
    int b = stoi(split(" ", contents[0])[1]);
    int c = stoi(split(" ", contents[0])[2]);
    ClosedHash c_hash(60, a, b, c);

    for(int i = 1; i < 60; i++) {

        c_hash.linear_put(contents[i]);
    }
}
