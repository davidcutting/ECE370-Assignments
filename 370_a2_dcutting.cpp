/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 2
    February 25, 2018

*/
#include <iostream>
#include <fstream>
#include <string>
/**

Node.h

*/
template <class T>
class Node {
    public:
        T data;
        Node *link;
        Node(T ndata, Node *nlink);
        ~Node();
};

/**

Node.cpp

*/
template <class T>
Node<T>::Node() {
    link = NULL;
}

template <class T>
Node<T>::Node(T ndata, Node *nlink) {
    data = ndata;
    nlink = nlink;
}

/**

Queue.h

*/
template <class T>
class Queue {
    public:
        void append(T data);
        T serve();
        bool isEmpty();
        Queue();
        ~Queue();
    private:
        Node *first;
        Node *last;
};

/**

Queue.cpp

*/
template <class T>
void Queue<T>::append(T data) {
    last = new Node<T>(data, last);
    if(first == NULL) first = last;
}

template <class T>
T Queue<T>::serve() {
    if (first == NULL) return first;
    Node *popped = first;
    first = first->link;
    return popped;
}

template <class T>
bool Queue<T>::isEmpty() {
    return first == NULL;
}

template <class T>
Queue<T>::Queue() {
    first = NULL;
    last = NULL;
}

/**

Stack.h

*/
template <class T>
class Stack {
    public:
        void push(T* input);
        T* pop();
        T* top();
        bool isEmpty();
        void display();
        Stack();
        ~Stack();
    private:
        Node* top;
};

/**

Stack.cpp

*/
template <class T>
void Stack<T>::push(T input) {
    top = new Node<T>(input, top);
}

template <class T>
T* Stack<T>::pop() {
    if (top == NULL) return top;
    Node *popped = top;
    top = top->link;
    return popped;
}

template <class T>
T* Stack<T>::top() {
    return top;
}

template <class T>
bool Stack<T>::isEmpty() {
    return top == NULL;
}

template <class T>
Stack<T>::Stack() {
    top = NULL;
}

/**

main.cpp

*/

int readFile(string* fileContent, char* fileName) {
    fstream file;
    file.open(fileName, ios::in);
    string line;
    int counter = 0;
    if (file.is_open())
    {
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

Queue *queue = new Queue<char>();
Stack *stack = new Stack<char>();
void infixToPostfix(string expression) {
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
                while() {
                    // pre(top) >= pre(Next)
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
}

void evaluatePostfix(string expression) {

}

int main() {
    string contents[100];
    int size = readFile(contents, "a2.txt");
    return 0;
}
