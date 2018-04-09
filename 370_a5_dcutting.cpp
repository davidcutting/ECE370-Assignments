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

int find_pivot(int* input_array, int& left, int& right) {
    if (input_array[0] > input_array[1]) {
        return input_array[0];
    } else if (input_array[1] > input_array[0]) {
        return input_array[1];
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

void quicksort(int* input_array, int& left, int& right) {
    int pivot = find_pivot(input_array, left, right);
    int l = partition(input_array, left, right, pivot);
    quicksort(input_array, left, l-1);
    quicksort(input_array, l, right);
}

void

/**

Heapsort

*/

int main() {

}
