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

        Node(T const& ndata, Node<T>* nlink) {
            data = ndata;
            link = nlink;
        }

        T const& get_data() const {
            return data;
        }

        void set_data(T const& data) {
            this->data = data;
        }

        Node<T>* get_next() const {
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
    private:
        Node<T>* head;
    public:
        LinkedList() {
            head = NULL;
        }

        void put(T const& input) {
            head = new Node<T>(input, head);
        }

        void put(T const& input, int index) {
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

        T const& get(int index) const {
            int count = 0;
            Node<T>* searched;
            while(count < index) {
                searched = searched->get_link();
                count++;
            }
            return searched->data;
        }

        void remove(int index) {
            Node<T>* deleted;
            if (index < 0) {
                std::cerr << "Negative Index Error: cannot remove at " << index << '\n';
                return;
            } else if (index == 0) {
                deleted = head;
                head = head->get_next();
                delete deleted;
                return;
            } else {
                Node<T> *previous = head;
                Node<T> *current = previous->get_next();
                int count = 1;
                while(count < index) {
                    previous = current;
                    current = previous->get_next();
                    count++;
                }
                deleted = current;
                previous->set_next(deleted->get_next());
                delete deleted;
                return;
            }
        }

        int find(T const& key) const {
            int i = 0;
            Node<T>* found = head;
            while(key != found->get_data()) {
                found = found->get_next();
                i++;
            }
            return i;
        }

        void print(int index, std::string name) const {
            int count = 0;
            Node<T>* searched;
            while(count < index) {
                searched = searched->get_next();
                count++;
            }
            std::cout << "--- " << name << " ---" << '\n';
            std::cout << "index = " << index << '\n';
            searched->get_data().print();
        }
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
        Student() {
            this->name = "";
            this->score = 0;
        }

        Student(std::string name, int score) {
            this->name = name;
            this->score = score;
        }

        std::string get_name() const {
            return name;
        }

        int get_score() const {
            return score;
        }

        void print() const {
            std::cout << "name = " << name << '\n';
            std::cout << "score = " << score << '\n';
        }

        bool operator!= (Student const& st) const {
            return  this->get_score() != st.get_score();
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
        int size;
    public:
        StudentRecord() {
            this->student_records = new LinkedList<Student>();
            mode = RecordMode::INSERT;
            size = 0;
        }

        // returns whether or not the program should terminate
        bool change_mode(std::string command) {
            if (command == "%INSERT") {
                mode = RecordMode::INSERT;
                return false;
            } else if (command == "%VISIT") {
                print_records();
                return false;
            } else if (command == "%DELETE") {
                mode = RecordMode::DELETE;
                return false;
            } else if (command == "%SEARCH") {
                mode = RecordMode::SEARCH;
                return false;
            } else if (command == "%SORTASC") {
                sort_asc();
                return false;
            } else if (command == "%SORTDES") {
                sort_des();
                return false;
            } else if (command == "%END") {
                return true;
            } else {
                return false;
            }
        }

        void insert(Student const& st) {
            student_records->put(st);
            size++;
        }

        void remove(Student const& st) {
            int index = student_records->find(st);
            student_records->remove(index);
            size--;
        }

        void search(Student const& st) const {
            int index = student_records->find(st);
            student_records->print(index, "Record Found");
        }

        RecordMode const& get_mode() const {
            return mode;
        }

        void print_records() const {
            for(int i = 0; i < size; i++) {
                student_records->print(i, "Student Record");
            }
        }

        void sort_asc() {

        }

        void sort_des() {

        }
};

#endif

/**

main

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
    std::string contents[100];
    char file_name[] = "a4.txt";
    int size = read_file(contents, file_name);
    StudentRecord* records = new StudentRecord();

    int counter = 0;
    bool terminate = false;

    while (terminate != true || counter < size) {
        std::string next_line = contents[counter];
        if (next_line == "") {
            counter++;
            continue;
        } else if (next_line[0] == '%') {
            terminate = records->change_mode(next_line);
        } else {
            std::string s_name = split(" ", next_line)[0];
            int s_score = stoi(split(" ", next_line)[1]);
            Student* std = new Student(s_name, s_score);

            switch(records->get_mode()) {
                case RecordMode::INSERT:
                    records->insert(*std);
                    break;
                case RecordMode::DELETE:
                    records->remove(*std);
                    break;
                case RecordMode::SEARCH:
                    records->search(*std);
                    break;
                default:
                    terminate = true;
            }
        }
        counter++;
    }
    return 0;
}
