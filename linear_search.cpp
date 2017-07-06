#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define SIZE 100

int search(int, int[]);

int main () {

	// the array
	int array[SIZE];

	// some random numbers for testing
	srand(time(NULL));
	for(int i = 0; i < SIZE; i++)
		array[i] = rand() % SIZE;

	int n = 5; // number to search
	int pos = search(5, array);

	if(pos >= 0)
		cout << "number " << n << " is on position " << pos << "." <<endl;
	else
		cout << "could not locate number " << n << "." << endl;

	return 0;
}

int search(int n, int array[]) {
	for(int i = 0; i < SIZE; i++) {
		if (*(array + i) == n)
			return i;
	}
	return -1;
}