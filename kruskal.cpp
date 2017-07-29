/*  
 *  Implementation of Kruskal's Algorithm to find minimal a Spanning Tree
 */

#include <iostream>
using namespace std;

#define SIZE 10
#define BITS_INT 32

int adj_matrix  [SIZE][SIZE][2]; // [0] - bool; [1] - weight
int adj_matrix_t[SIZE][SIZE][2]; // temp
bool adj_matrix_r[SIZE][SIZE]; // result

void setEdge(int, int, int);
void kruskal();
int clean_graph();
void find_edges(long*);
void sort_edges(long*, int, int);
void select_edges(long*, int);
bool check_cycle(int);

void print_edges();

int main (void) {

	for(int i = 0; i < SIZE; i++){
		for(int j = i; j < SIZE; j++){
			adj_matrix[i][j][0] = 0;
			adj_matrix[j][i][0] = 0;
			adj_matrix_r[i][j] = false;
			adj_matrix_r[j][i] = false;
		}
	}

	setEdge(0,1,3);
	setEdge(1,2,3);
	setEdge(2,3,3);
	setEdge(3,4,3);
	setEdge(4,5,3);
	setEdge(5,6,3);
	setEdge(6,7,3);
	setEdge(7,8,3);
	setEdge(8,9,3);
	setEdge(9,0,3);

	kruskal();

	print_edges();

	return 0;
	
}

void setEdge(int s, int e, int w) {
	adj_matrix[s][e][0] = 1;
	adj_matrix[e][s][0] = 1;
	adj_matrix[s][e][1] = w;
	adj_matrix[e][s][1] = w;
}

void kruskal() {

	int valid_edges_count = 0;
	valid_edges_count = clean_graph();

	long edges[valid_edges_count];
	find_edges(edges);
	sort_edges(edges, 0, valid_edges_count);

	select_edges(edges, valid_edges_count);

}

int clean_graph() {

	int valid_edges_count = 0;

	// remove parallel edges
	// for this algorithm, we do not have parallel edges

	// remove loops
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			if(i!=j) {
				adj_matrix_t[i][j][0] = adj_matrix[i][j][0];
				if(adj_matrix_t[i][j][0]) {
					adj_matrix_t[i][j][1] = adj_matrix[i][j][1];	
					valid_edges_count++;
				}
			}
			else
				adj_matrix_t[i][j][0] = 0;

	return valid_edges_count/2;
}

void find_edges(long* edges){
	int k = 0;
	for(int i = 0; i < SIZE; i++)
		for(int j = i; j < SIZE; j++)
			if(adj_matrix_t[i][j][0]) {
				edges[k] = ((long)i << BITS_INT) + j;
				k++;
			}
}

void sort_edges(long* edges, int start, int end) {

	//mergesort

	if(end-start > 1) {

		int pivot = end-1;
		int s = start;
		int e = end-2;

		while(true) {
			while(s <  pivot && adj_matrix_t[(int)(edges[s]>>BITS_INT)][(int)edges[s]][1] <  adj_matrix_t[(int)(edges[pivot]>>BITS_INT)][(int)edges[pivot]][1]) s++;
			while(e >= start && adj_matrix_t[(int)(edges[e]>>BITS_INT)][(int)edges[e]][1] >= adj_matrix_t[(int)(edges[pivot]>>BITS_INT)][(int)edges[pivot]][1]) e--;
			if(s < e) {
				edges[s] ^= edges[e];
				edges[e] ^= edges[s];
				edges[s] ^= edges[e];
			}
			else if(s >= e) {
				edges[s] ^= edges[pivot];
				edges[pivot] ^= edges[s];
				edges[s] ^= edges[pivot];

				sort_edges(edges, start, pivot);
				sort_edges(edges, pivot+1, end);
				break;
			}
		}
	}
}

void select_edges(long* edges, int valid_edges_count) {

	bool visited_edges[valid_edges_count];
	bool contains_cycle = false;
	int visited_edges_count = 0;

	for(int i = 0; i < valid_edges_count; i++)
		visited_edges[i] = false;

	for(int i = 0; i < valid_edges_count && visited_edges_count < valid_edges_count-1; i++) {
		int s = (int) (edges[i]>>BITS_INT);
		int e = (int) (edges[i]);
		adj_matrix_r[s][e] = true;
		if(visited_edges[s] == true && visited_edges[e] == true) {
			contains_cycle = check_cycle(s);
			if(contains_cycle)
				adj_matrix_r[s][e] = false;
		}
		else {
			visited_edges[s] = true;
			visited_edges[e] = true;
			visited_edges_count++;
		}
	}
}

bool check_cycle(int s) {
	
	// depth first search

	bool visited[SIZE];
	long stack[SIZE*SIZE];
	int top = 0;
	int node = s;
	int prev_node = s;

	for(int i = 0; i < SIZE; i++)
		visited[i] = false;

	visited[node] = true;
	stack[top++] = ((long)prev_node << BITS_INT) + node;

	while(top > 0){
		node = (int)(stack[--top]);

		prev_node = (int)(stack[top] >> BITS_INT);
		visited[node] = true;

		for(int i = 0; i < SIZE; i++) {
			if((adj_matrix_r[node][i] || adj_matrix_r[i][node]) && (i!=prev_node)) {
				if(visited[i]){cout << "returning" << i << endl; return true;}
				stack[top++] = ((long)node << BITS_INT) + i;
			}
		}
	}

	return false;

}

void print_edges() {
	for(int i = 0; i < SIZE; i++)
		for(int j = i; j < SIZE; j++) {
			if(adj_matrix_r[i][j])
				cout << "Edge: " << i << "-" << j << endl;
		}
}