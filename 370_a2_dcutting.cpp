/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 2
    February 21, 2018

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
            if(last == NULL) last = new Node<T>(data, last);
            else {
                Node<T>* oldLast = last;
                last = new Node<T>(data, oldLast->link);
                oldLast->link = last;
            }
            if(first == NULL) first = last;
        }

        T serve() {
            T popped = first->data;
            first = first->link;
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
            while(next != NULL) {
                std::cout << " " << next->data;
                next = next->link;
            }
            std::cout << '\n';
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
            float conv = (float) (postfix->serve() - '0');
            result->push(conv);
        } else if (isOperator(postfix->front())) {
            float var2 = result->pop();
            float var1 = result->pop();
            float v;
            switch(postfix->front()) {
                case '+':
                    v = var1 + var2;
                    result->push(v);
                    postfix->serve();
                    break;
                case '-':
                    v = var1 - var2;
                    result->push(v);
                    postfix->serve();
                    break;
                case '*':
                    v = var1 * var2;
                    result->push(v);
                    postfix->serve();
                    break;
                case '/':
                    v = var1 / var2;
                    result->push(v);
                    postfix->serve();
                    break;
                default:
                    postfix->serve();
                    std::cerr << "SOMETHING HAPPENED" << '\n';
                    break;
            }
        }
    }
    return result->pop();
}

float calcInfix(std::string line) {
    Queue<char>* postfix = new Queue<char>();
    std::cout << "\n--------------------------" << '\n';
    std::cout << "Given: " << line << '\n';

    infixToPostfix(postfix, line);
    std::cout << "\nPostfix: " << '\n';
    postfix->display();

    float result = evaluatePostfix(postfix);
    std::cout << "\nResult: " << result << '\n';
    std::cout << "--------------------------" << '\n';
    return result;
}

int main() {
    std::string contents[100];
    char fileName[] = "a2.txt";
    int size = readFile(contents, fileName);
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += calcInfix(contents[i]);
    }
    std::cout << "Total: " << sum << '\n';
    return 0;
}
