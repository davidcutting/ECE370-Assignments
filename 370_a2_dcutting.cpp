/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 2
    February 25, 2018

*/

#include <cstddef>

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
            nlink = nlink;
        }

        ~Node();
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
            if (first == NULL) return first->data;
            Node<T>* popped = first;
            first = first->link;
            return popped->data;
        }

        bool isEmpty() {
            return first == NULL;
        }

        Queue() {
            first = NULL;
            last = NULL;
        }

        ~Queue();
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
            if (head == NULL) return head->data;
            Node<T>* popped = head;
            head = head->link;
            return popped->data;
        }

        T top() {
            return head->data;
        }

        bool isEmpty() {
            return head == NULL;
        }

        /** TODO:
        template <typename T>
        void display();
        */

        Stack() {
            head = NULL;
        }

        ~Stack();
};

#endif

/**

main.cpp

*/

#include <iostream>
#include <fstream>
#include <string>

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

int pre(char in) {
    switch(in) {
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '^':
            return 2;
        default:
            return 3;
    }
}

Queue<char>* infixToPostfix(std::string expression) {
    Stack<char> *stack = new Stack<char>();
    Queue<char> *queue = new Queue<char>();
    int counter = 0;
    while (expression[counter] != '\n') {
        switch(expression[counter]) {
            case '(':
                stack->push(expression[counter]);
                break;
            case ')':
                for (int i = 0; i < counter; i++) {
                    if (expression[counter] == '(') {
                        stack->pop();
                        break;
                    }
                    queue->append(stack->pop());
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while(pre(stack->top()) >= pre(expression[counter])) {
                    queue->append(stack->pop());
                }
                stack->push(expression[counter]);
                break;
            default:
                // its a number
                queue->append(expression[counter]);
                break;
        }
        while(stack->top() != NULL) {
            queue->append(stack->pop());
        }
    }
    return queue;
}

Stack<float>* evaluatePostfix(Queue<char>* queue) {
    Stack<float> *stack = new Stack<float>();
    while(!queue->isEmpty()) {
        switch(queue->first->data) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            default:
                //stack->push()
                break;
        }
    }
    return stack;
}

int main() {
    std::string contents[100];
    int size = readFile(contents, "a2.txt");
    for (int i = 0; i < size; i++) {
        Queue<char> *queue = infixToPostfix(contents[i]);
        while(!queue->isEmpty()) {
            std::cout << queue->serve() << '\n';
        }
    }
    return 0;
}
