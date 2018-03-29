/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 4
    March 28, 2018

*/

#include <cstddef>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

/**

Node

*/
#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
    private:
        T data;
        Node<T>* link;
    public:
        Node() {
            link = NULL;
        }

        Node(T ndata, Node<T>* nlink) {
            data = ndata;
            link = nlink;
        }

        T get_data() {
            return data;
        }

        void set_data(T data) {
            this->data = data;
        }

        Node<T>* get_next() {
            return link;
        }

        void set_next(Node<T>* link) {
            this->link = link;
        }
};

#endif

/**

LinkedList

*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
class LinkedList {
    public:
        LinkedList() {
            head = NULL;
        }

        void put(T input, int index) {
            if (index < 0) {
                std::cerr << "Negative Index Error: cannot put " << input << " at " << index << '\n';
                return;
            } else if (index == 0) {
                head = new Node<T>(input, head);
                return;
            } else {
                Node<T> *current = head;
                Node<T> *next = current->get_link();
                int count = 1;
                while(count < index) {
                    current = next;
                    next = current->get_link();
                    count++;
                }
                current->set_next(new Node<T>(input, next));
                return;
            }
        }

        void put(T input) {
            head = new Node<T>(input, head);
        }

        T get(int index) {
            int count = 0;
            Node<T>* searched;
            while(count < index) {
                searched = searched->get_link();
                count++;
            }
            return searched->data;
        }

        T remove(int index) {
            Node<T>* deleted;
            if (index < 0) {
                std::cerr << "Negative Index Error: cannot remove at " << index << '\n';
                return;
            } else if (index == 0) {
                deleted = head;
                head = head->get_link();
                delete deleted;
                return;
            } else {
                Node<T> *previous = head;
                Node<T> *current = previous->get_link();
                int count = 1;
                while(count < index) {
                    previous = current;
                    current = previous->get_link();
                    count++;
                }
                deleted = current;
                previous->set_next(deleted->get_next())
                delete deleted;
                return;
            }
        }

        int find(T key) {
            int i = 0;
            Node<T>* found = head;
            while(key != found->get_data()) {
                found = found->get_next();
                i++;
            }
            return i;
        }

    private:
        Node *head;
};

#endif

/**

Student

*/
#ifndef STUDENT_H
#define STUDENT_H

class Student {
    private:
        std::string name;
        int score;
    public:
        Student(std::string name, int score) {
            this->name = name;
            this->score = score;
        }

        std::string get_name() {
            return name;
        }

        int get_score() {
            return score;
        }
};

#endif

/**

RecordMode

*/
#ifndef RECORD_MODE_H
#define RECORD_MODE_H

enum class RecordMode {
    INSERT,
    DELETE,
    SEARCH
};

#endif

/**

StudentRecord

*/
#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

class StudentRecord {
    private:
        LinkedList<Student>* student_records;
        RecordMode mode;
    public:
        StudentRecord() {
            this->student_records = new LinkedList<Student>();
            mode = RecordMode::INSERT;
        }

        // returns whether or not the program should terminate
        bool change_mode(std::string command) {
            switch(command) {
                case "%INSERT":
                    mode = RecordMode::INSERT;
                    return false;
                case "%VISIT":

                case "%DELETE":
                    mode = RecordMode::DELETE;
                    return false;
                case "%SEARCH":
                    mode = RecordMode::SEARCH;
                    return false;
                case "%SORTASC":
                case "%SORTDES":
                case "%END":
                    return true;
                default:
                    return false;
            }
        }

        RecordMode get_mode() {
            return mode;
        }

        void print_records() {
            student_records->print();
        }
};

#endif

/**

main

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
    std::string contents[100];
    char file_name[] = "a4.txt";
    int size = read_file(contents, file_name);
    StudentRecord* records = new StudentRecord();

    int counter = 0;
    bool terminate = false;

    while (terminate != true) {
        std::string next_line = contents[counter];
        if (next_line == "") {
            counter++;
            continue;
        } else if (next_line[0] == '%') {
            terminate = records->change_mode(next_line);
        } else {
            switch(records->get_mode()) {
                case RecordMode::INSERT:
                case RecordMode::DELETE:
                case RecordMode::SEARCH:
                default:
                    terminate = true;
            }
        }
        counter++;
    }
    return 0;
}
