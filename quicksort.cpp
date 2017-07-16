/*
 * Implementation of Quick Sort.
 * O(n)
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define SIZE 100

void quicksort(int[], int, int);

int main () {

	int array[SIZE];

	// Creating an array of random numbers to be sorted
	srand(time(NULL));
	for(int i = 0; i < SIZE; i++)
		array[i] = rand();

	cout << "Before sorting:" << endl;
	for(int i = 0; i < SIZE; i++)
		cout << i << ": " << array[i] << endl;

	quicksort(array, 0, SIZE);

	cout << "After sorting:" << endl;
	for(int i = 0; i < SIZE; i++)
		cout << i << ": " << array[i] << endl;

	return 0;
}

void quicksort(int array[], int i_left, int i_right) {

	if(i_right-i_left > 1) {

		int right = i_right-2;
		int left  = i_left   ;
		int pivot = i_right-1;

		while(true) {

			while(array[left] <= array[pivot] && left < pivot) left++;
			while(array[right] > array[pivot] && right > i_left) right--;
			if(left < right) {
				// swap
				if(left != right) {
					array[left ] ^= array[right];
					array[right] ^= array[left ];
					array[left ] ^= array[right];
				}
			}
			else {
				// recursion
				if(left != pivot) {
					array[left]  ^= array[pivot];
					array[pivot] ^= array[left];
					array[left]  ^= array[pivot];
				}
				quicksort(array,i_left,left);
				quicksort(array,left+1,i_right);
				break;
			}
		}
	}
}