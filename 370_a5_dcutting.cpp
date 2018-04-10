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

int find_pivot(int* a) {
    if (a[0] > a[1]) {
        return a[0];
    } else if (a[1] > a[0]) {
        return a[1];
    }
}

int partition(int* input_array, int& left, int& right, int& pivot) {
	while (left <= right) {
		while (input_array[left] < pivot) left++;
		while (input_array[right] > pivot) right--;
		if (left <= right) {
            std::swap(left, right);
			left++;
			right--;
		}
	}
	return left;
}

void quicksort(int* a, int& left, int& right) {
    int pivot = find_pivot(a);
    int pi = partition(a, left, right, pivot);
    quicksort(a, left, pi - 1);
    quicksort(a, pi + 1, right);
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

}

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
    int size = readFile(file_contents, "a5.txt");
    int qsort_nums[size];
    int hsort_nums[size];
    for(int i = 0; i < size; i++) {
        qsort_nums = stoi(file_contents[i]);
        hsort_nums = stoi(file_contents[i]);
    }

    int left = 0;
    int right = size;
    quicksort(qsort_nums, left, right);
    heapsort(hsort_nums, size);
}
