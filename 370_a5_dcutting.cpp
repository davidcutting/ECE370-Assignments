/**

  ECE 370 - Advanced Software Techniques in Computer Engineering

    David Cutting
    Assignment 4
    April 12, 2018

*/

#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>

/**

Quicksort

*/

int partition(int* a, int left, int right) {
    int p = a[right];
    for (int i = left; i < right; i++) {
        if (a[i] <= p) {
            std::swap(a[left], a[i]);
            left++;
        }
    }
    std::swap(a[left], a[right]);
    return left;
}

void quicksort(int* a, int const& min, int const& max) {
    int p = partition(a, min, max);
    quicksort(a, min, p - 1);
    quicksort(a, p + 1, max);
}

/**

Heapsort

*/

void heapify(int* a, int root, int size) {
    int max = root; // max is root
    int left = (2 * root) + 1;
    int right = (2 * root) + 2; // right is left + 1

    if (left < size) { // left child > root
        if (a[left] > a[max]) {
            max = left;
        }
    }

    if (right < size) { // right child > max
        if (a[right] > a[max]) {
            max = left;
        }
    }

    if (max != root) { // if the max is not the root
        std::swap(a[root], a[max]);
        heapify(a, root, max);
    }
}

void heapsort(int* a, int size) {
    // first build the heap
    for (int i = size/2; i >= 1; i--) {
        heapify(a, i, size);
    }
    // sort the heap
    for (int i = size; i >= 2; i--) {
        std::swap(a[1], a[i]);
        heapify(a, 1, i - 1);
    }
}

/**

main

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

int main(int argc, char const* argv[]) {
    std::string file_contents[50];
    char file_name[] = "a5.txt";
    int size = readFile(file_contents, file_name);
    int qsort_nums[size];
    int hsort_nums[size];
    for(int i = 0; i < size; i++) {
        qsort_nums[i] = stoi(file_contents[i]);
        hsort_nums[i] = stoi(file_contents[i]);
    }

    int left = 0;
    int right = size;
    quicksort(qsort_nums, left, right);
    heapsort(hsort_nums, size);
}
