/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 1
    January 22, 2018

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Person {
  public:
    string name;
    int id;
    string address;
};

int makePeople(Person *people)
{
    fstream file;
    file.open("a1.txt", ios::in);
    string line;
    string content[100];
    int counter = 0;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line == "")
                continue;
            content[counter] = line;
            counter++;
        }
    }
    file.close();

    for (int i = 0; i < counter; i++)
    {
        switch (i % 3)
        {
        case 0:
            people[i / 3].name = content[i];
        case 1:
            people[i / 3].id = atoi(content[i].c_str());
        case 2:
            people[i / 3].address = content[i];
        default:
            break;
        }
    }
    return (counter / 3);
}

int addPeople(int size, Person *people)
{
    bool userAdding = true;
    while (userAdding)
    {
        if (size + 1 > 20)
        {
            cout << endl
                 << "The database is full!";
            userAdding = false;
            continue;
        }

        string decision;
        cout << endl
             << "Would you like to add a record? [Y/n]: ";
        cin >> decision;
        cin.ignore();

        if (decision == "y" || decision == "Y")
        {
            userAdding = true;
        }

        else if (decision == "n" || decision == "N")
        {
            userAdding = false;
            continue;
        }

        else
        {
            cout << endl
                 << "Sorry, I couldn't understand you. Beep boop." << endl;
            userAdding = true;
            continue;
        }

        cout << endl
             << "Name? ";
        string name;
        getline(cin, name);
        people[size].name = name;

        cout << endl
             << "ID? ";
        int id;
        cin >> id;
        cin.ignore();
        people[size].id = id;

        cout << endl
             << "Address? ";
        string address;
        getline(cin, address);
        people[size].address = address;

        size = size + 1;
    }
    return size;
}

string getLastName(string name) {
    string str;
    for(int i = 0; i < name.length(); i++) {
        if (name[i] == ',') break;
        else str += name[i];
    }
    return str;
}

int peopleQuery(int size, Person *people, Person *caughtPeople)
{
    bool userQuerying = true;
    int counter = 0;

    while (userQuerying)
    {
        string decision;
        cout << endl
             << "Would you like to query the records? [Y/n]: ";
        cin >> decision;
        cin.ignore();

        if (decision == "y" || decision == "Y")
        {
            userQuerying = true;
        }

        else if (decision == "n" || decision == "N")
        {
            userQuerying = false;
            continue;
        }

        else
        {
            cout << endl
                 << "Sorry, I couldn't understand you. Beep boop." << endl;
            userQuerying = true;
            continue;
        }

        string nameInput;
        cout << "Please enter a last name to find the record: ";
        cin >> nameInput;

        for(int i = 0; i < size; i++) {
            if(getLastName(people[i].name) == nameInput) {
                caughtPeople[counter] = people[i];
                counter++;
            }
        }
    }
    return counter;
}

void sortPeople(int passes, int numPeople, Person *people)
{
    for (int i = 0; i < passes; i++)
    {
        for (int j = 0; j < numPeople - 1; j++)
        {
            if (people[j].id > people[j + 1].id)
            {
                swap(people[j], people[j + 1]);
            }
        }
    }
}

void printPeople(int amnt, Person *people)
{
    for (int i = 0; i < amnt; i++)
    {
        cout << "Name: " << people[i].name << endl;
        cout << "ID:       " << people[i].id << endl;
        cout << "ADDR:     " << people[i].address << endl;
        cout << endl;
    }
}

int main()
{
    // #1
    Person *people = new Person[20]; // Array which can hold max 20 people
    int size = makePeople(people);   // Read from a1.txt and put it in array
    sortPeople(size, size, people);  // Sort people ascending order

    // #2
    printPeople(size, people); // Print...

    // #3
    size = addPeople(size, people); // User input for adding people to list
    sortPeople(size, size, people); // Sort people again now that people may have been added.

    // #4
    Person *queriedPeople = new Person[size];
    int queriedSize = peopleQuery(size, people, queriedPeople); // User input for query

    // #5
    printPeople(queriedSize, queriedPeople); // Print people that were found in query
    return 0;
}
