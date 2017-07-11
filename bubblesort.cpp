/*
 *  Implementation of bubble sort
 *  O(n^2)
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define SIZE 10

int main () {
	
	int array[SIZE];

	//adding some random numbers
	srand(time(NULL));

	for(int i = 0; i < SIZE; i++)
		array[i] = rand();

	cout << "Before sorting:" << endl;
	for(int i = 0; i < SIZE; i++)
		cout << i << " - " << array[i] << endl;

	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE-1; j++)
			if(array[j] > array[j+1]) {
				array[j  ] ^= array[j+1];
				array[j+1] ^= array[j  ];
				array[j  ] ^= array[j+1];
			}

	cout << "After sorting:" << endl;
	for(int i = 0; i < SIZE; i++)
		cout << i << " - " << array[i] << endl;

	return 0;

}