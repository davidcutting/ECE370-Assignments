/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 3
    March 14, 2018

*/

/**

HashNode

*/
#ifndef HASHNODE_H
#define HASHNODE_H

template <class K>
template <class V>
class HashNode {
    public:

        HashNode(K key, V value) {
            this->key = key;
            this->value = value;
        }

        K get_key() {
            return this->key;
        }

        V get_value() {
            return this->value;
        }

    private:

        K key;
        V value;
};

#endif

/**

HashNode

*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

template <class K>
template <class V>
class HashTable {
    public:

        HashMap(int size) {
            hash_size = size;
            table = new HashNode*[size];
            for(int i = 0; i < size; i++) {
                table[i] = NULL;
            }
        }

        V linear_find(std::string value) {
            int hash = get_hash();
            while(table[hash] != NULL && table[hash]->get_key() != key) {
                hash = (hash + 1) % hash_size;
            }
            if (table[hash] != NULL) {
                return table[hash]->get_value();
            }
            return NULL;
        }

        void linear_put(K key, std::string value) {
            int hash = get_hash(value);
            while(table[hash] != NULL && table[hash]->get_key() != key) {
                hash = (hash + 1) % hash_size;
            }
            if (table[hash] != NULL) {
                delete table[hash];
            }
            table[hash] = new HashNode<K,std::string>(key, value);
        }

        int get_size() {
            return this->hash_size;
        }

    private:

        HashNode** table;
        int a;
        int b;
        int c;
        int hash_size = 60;

        int get_hash(std::string value) {
            return (a * value[0] + b * value[1] + c * value[2]) % hash_size;
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
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            if (line == "")
                continue;
            file_content[counter] = line;
            counter++;
        }
    }
    file.close();
    return counter;
}

int main() {
    std::string contents[60];
    char file_name[] = "a3.txt";
    read_file(contents, file_name);
}
