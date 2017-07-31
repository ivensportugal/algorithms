/*
 *  Implementation of Prim's Algorithm
 *  to find the minimum cost spanning tree
 */

#include <iostream>
using namespace std;

#define SIZE 10
#define BITS_INT 32

int adj_matrix  [SIZE][SIZE][2];
int adj_matrix_r[SIZE][SIZE];

void insert(int, int, int);
void prim(int);
bool check_cycle();
void print();

int main (void) {

	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++) {
			adj_matrix[i][j][0] = 0;
			adj_matrix[i][j][1] = 0;
		}

	insert(0,1,1);
	insert(1,2,5);
	insert(2,3,7);
	insert(3,4,5);
	insert(4,8,0);
	insert(8,9,2);
	insert(1,5,9);
	insert(5,6,1);
	insert(6,7,9);
	insert(7,8,0);
	insert(3,7,2);
	insert(4,6,3);

	prim(0);

	print();
	
	return 0;
}

void insert(int s, int e, int weight) {
	adj_matrix[s][e][0] = 1;
	adj_matrix[e][s][0] = 1;

	adj_matrix[e][s][1] = weight;
	adj_matrix[s][e][1] = weight;
}

void prim(int node) {

	bool included[SIZE];
	int num_included = 0;
	long border_edges[SIZE*SIZE];
	int border_edges_size = 0;

	for(int i = 0; i < SIZE; i++)
		included[i] = false;

	// initiate with the selected node
	included[node] = true;
	num_included++;
	for(int i = 0; i < SIZE; i++)
		if(adj_matrix[node][i][0] == 1 && !included[i])
			border_edges[border_edges_size++] = ((long)node << BITS_INT) + i;


	while(num_included < SIZE) {

		// get the crossing border edge whose weight is the smallest
		int min_weight_pos = 0;
		int min_weight = adj_matrix[(int)(border_edges[0] >> BITS_INT)][(int)(border_edges[0])][1];

		for(int k = 1; k < border_edges_size; k++) {
			int i = (int)(border_edges[k] >> BITS_INT);
			int j = (int)(border_edges[k]);
			if(adj_matrix[i][j][1] < min_weight) {
				min_weight_pos = k;
				min_weight = adj_matrix[i][j][1];
			}
		}

		// update counters
		int s = (int)(border_edges[min_weight_pos] >> BITS_INT); 
		int e = (int)(border_edges[min_weight_pos]);
		adj_matrix_r[s][e] = true;
		adj_matrix_r[e][s] = true;
		included[e] = true;
		num_included++;

		// check if it violates spanning tree rules (cycle)
		bool has_cycle = check_cycle();
		if(has_cycle) {
			// restore counters
			adj_matrix_r[s][e] = false;
			adj_matrix_r[e][s] = false;
			included[e] = false;
			num_included--;

			// remove edge that would form a cycle
			border_edges[min_weight_pos] = border_edges[--border_edges_size];
			continue;
		}

		// remove internal edges
		for(int k = 0; k < border_edges_size; k++) {
			int i = (int)(border_edges[k] >> BITS_INT);
			int j = (int)(border_edges[k]);
			if(j == e) {
				border_edges[k] = border_edges[--border_edges_size];
			}
		}

		// add new edges
		for(int i = 0; i < SIZE; i++)
			if(adj_matrix[e][i][0] == 1 && !included[i])
				border_edges[border_edges_size++] = ((long)e << BITS_INT) + i;

	}
}

bool check_cycle() {

	// dfs
	bool visited[SIZE];
	long stack[SIZE*SIZE];
	int top = 0;
	long prev_node = 0;
	int node = 0;

	for(int i = 0; i < SIZE; i++)
		visited[i] = false;

	stack[top++] = ((long)prev_node << BITS_INT) + node;

	while(top > 0) {

		top--;
		node = (int)(stack[top] >> BITS_INT);
		prev_node = (int)(stack[top]);
		visited[node] = true;

		for(int i = 0; i < SIZE; i++)
			if(adj_matrix_r[node][i] && i !=  prev_node && i!=node) {
				if(visited[i]) return true;
				stack[top++] = ((long)node << BITS_INT) + i;
			}
	}

	return false;
}

void print() {
	for(int i = 0; i < SIZE; i++)
		for(int j = i; j < SIZE; j++) {
			if(adj_matrix_r[i][j])
				cout << "Edge: " << i << "-" << j << endl;
		}
}