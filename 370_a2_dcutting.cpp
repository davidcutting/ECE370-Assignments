/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 2
    February 25, 2018

*/

#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>

/**

Node

*/
#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
    public:

        T data;
        Node<T>* link;

        Node() {
            link = NULL;
        }

        Node(T ndata, Node<T>* nlink) {
            data = ndata;
            link = nlink;
        }
};

#endif

/**

Queue

*/
#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue {
    private:
    public:

        Node<T>* first;
        Node<T>* last;

        void append(T data) {
            last = new Node<T>(data, last);
            if(first == NULL) first = last;
        }

        T serve() {
            Node<T>* tmp = first;
            T popped = first->data;
            first = first->link;
            delete tmp;
            return popped;
        }

        T front() {
            return first->data;
        }

        bool isEmpty() {
            return first == NULL;
        }

        void display() {
            Node<T>* next = first;
            std::cout << "Queue: " << '\n';
            while(next != NULL) {
                std::cout << "  " << next->data << '\n';
                next = next->link;
            }
        }

        Queue() {
            first = NULL;
            last = NULL;
        }
};

#endif

/**

Stack

*/
#ifndef STACK_H
#define STACK_H

template <class T>
class Stack {
    private:
    public:

        Node<T>* head;

        void push(T input) {
            head = new Node<T>(input, head);
        }

        T pop() {
            Node<T>* tmp = head;
            T popped = head->data;
            head = head->link;
            delete tmp;
            return popped;
        }

        T top() {
            return head->data;
        }

        bool isEmpty() {
            return head == NULL;
        }

        Stack() {
            head = NULL;
        }
};

#endif

/**

main.cpp

*/

int readFile(std::string* fileContent, char* fileName) {
    std::fstream file;
    file.open(fileName, std::ios::in);
    int counter = 0;
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            if (line == "")
                continue;
            fileContent[counter] = line;
            counter++;
        }
    }
    file.close();
    return counter;
}

int getPrecedence(char in) {
    switch(in) {
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
    }
}

bool hasHigherPrecedence(char in1, char in2) {
    return (getPrecedence(in1) >= getPrecedence(in2));
}

bool isOperand(char in) {
    if (in >= '0' && in <= '9') return true;
    else if (in >= 'a' && in <= 'z') return true;
    else if (in >= 'A' && in <= 'Z') return true;
    else return false;
}

bool isOperator(char in) {
    switch (in) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}

void infixToPostfix(Queue<char>* postfix, std::string expr) {
    Stack<char> tmpStack;
    int n = expr.length();
    for (int i = 0; i < n; i++) {
        char next = expr[i];

        if (isOperand(next)) {
            postfix->append(next);
        } else if (isOperator(next)) {
            while (!tmpStack.isEmpty() && hasHigherPrecedence(tmpStack.top(), next) && tmpStack.top() != '(') {
                postfix->append(tmpStack.pop());
            }
            tmpStack.push(next);
        } else if (next == '(') {
            tmpStack.push(next);
        } else if (next == ')') {
            while (tmpStack.top() != '(' && !tmpStack.isEmpty()) {
                postfix->append(tmpStack.pop());
            }
            if(!tmpStack.isEmpty()) tmpStack.pop();
        } else {
            std::cerr << "SOMETHING HAPPENED" << '\n';
            return;
        }
    }
    while (!tmpStack.isEmpty()) {
        postfix->append(tmpStack.pop());
    }
}

float evaluatePostfix(Queue<char>* postfix) {
    Stack<float>* result = new Stack<float>();
    while(!postfix->isEmpty()) {
        if (isOperand(postfix->front())) {
            int conv = postfix->serve();
            result->push(conv/1f);
        } else if (isOperator(postfix->front())) {
            float var1 = result->pop();
            float var2 = result->pop();
            switch(postfix->front()) {
                case '+':
                    result->push(var1 + var2);
                    break;
                case '-':
                    result->push(var1 - var2);
                    break;
                case '*':
                    result->push(var1 * var2);
                    break;
                case '/':
                    result->push(var1 / var2);
                    break;
                default:
                    std::cerr << "SOMETHING HAPPENED" << '\n';
                    break;
            }
        }
    }
    return result->pop();
}

float calcInfix(std::string line) {
    Queue<char>* postfix = new Queue<char>();
    std::cout << "Given: " << line << '\n';
    infixToPostfix(postfix, line);
    std::cout << "Postfix: " << '\n';
    postfix->display();
    return evaluatePostfix(postfix);
}

int main() {
    std::string contents[100];
    int size = readFile(contents, "a2.txt");
    for (int i = 0; i < size; i++) {
        std::cout << "Result: " << calcInfix(contents[i]) << '\n';
    }
    return 0;
}
