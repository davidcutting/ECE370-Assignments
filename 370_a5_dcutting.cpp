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
    for (int i = left; i < right; i++) {
        if (a[i] <= a[right]) {
            std::swap(a[left], a[i]);
            left++;
        }
    }
    std::swap(a[left], a[right]);
    return left;
}

void quicksort(int* a, int min, int max) {
    if (min < max) {
        int p = partition(a, min, max);
        std::cout << "Pivot: " << p << ", ";
        for(int i = 0; i < max; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << std::flush;
        std::cout << '\n';
        quicksort(a, min, p - 1);
        quicksort(a, p, max);
    }
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
            max = right;
        }
    }

    if (max != root) { // if the max is not the root
        std::swap(a[root], a[max]);
        heapify(a, max, size);
    }
}

// all loops are done backwards to put arrays in ascending order
void heapsort(int* a, int size) {
    // first build the heap
    std::cout << "Building the Heap:" << '\n';
    for (int i = size/2 -1; i >= 0; i--) {
        for(int j = 0; j < 10; j++) { // print out the first 10
            std::cout << a[j] << " ";
        }
        std::cout << '\n';
        heapify(a, i, size);
    }
    // sort the heap
    std::cout << "Sorting the Heap:" << '\n';
    for (int i = size - 1; i >= 0; i--) {
        std::swap(a[0], a[i]);
        for(int j = 0; j < 10; j++) { // print out the first 10
            std::cout << a[j] << " ";
        }
        std::cout << '\n';
        heapify(a, 0, i);
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

    std::cout << "Quicksort:" << '\n';
    quicksort(qsort_nums, 0, size - 1);
    std::cout << '\n';
    std::cout << std::flush;

    std::cout << "Heapsort:" << '\n';
    heapsort(hsort_nums, size);
    std::cout << '\n';
    std::cout << std::flush;

    std::cout << "Quicksort Results: " << '\n';
    for(int i = 0; i < size; i++) {
        std::cout << qsort_nums[i] << " ";
    }
    std::cout << '\n';
    std::cout << '\n';
    std::cout << std::flush;

    std::cout << "Heapsort Results: " << '\n';
    for(int i = 0; i < size; i++) {
        std::cout << hsort_nums[i] << " ";
    }
    std::cout << '\n';
    std::cout << '\n';
    std::cout << std::flush;
}
