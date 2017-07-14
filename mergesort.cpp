/* 
 *  Implementation of Merge Sort.
 *  O(n*log(n))
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define SIZE 10

void mergesort(int [], int, int);

int main () {

	int array[SIZE];

	// adding random numbers
	srand(time(NULL));

	for(int i = 0; i < SIZE; i++)
		array[i] = rand() % 100;

	cout << "Before sorting:" << endl;
	for(int i = 0; i < SIZE; i++)
		cout << i << " - " << array[i] << endl;

	mergesort(array, 0, SIZE);

	cout << "After sorting:" << endl;
	for(int i = 0; i < SIZE; i++)
		cout << i << " - " << array[i] << endl;

	return 0;
}

void mergesort(int array[], int start, int end){
	if(start+1 != end) {
		int half = (end-start)/2;
		mergesort(array, start, start+half);
		mergesort(array, start+half, end);
		

		int result[end-start];

		int i = 0;
		int l = start;
		int h = start+half;

		while(l!=start+half && h!=end) {
			if(array[l] < array[h]) {
				result[i] = array[l];
				l++;
				i++;
			}
			else {
				result[i] = array[h];
				h++;
				i++;
			}
		}
		while(l!=start+half) {
			result[i] = array[l];
			l++;
			i++;
		}
		while(h!=end) {
			result[i] = array[h];
			h++;
			i++;
		}

		for(i = 0; i < end-start; i++) {
			array[start+i] = result[i];
		}
	}
}