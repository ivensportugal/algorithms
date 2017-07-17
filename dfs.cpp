/*
 *  Implementation of the Breadth First Search algorithm
 *  to traverse graphs
 */

#include <iostream>
using namespace std;

#define SIZE 10

struct Vertex {
	int value;
	bool visited; 
};

void add_edge_int(int [][SIZE], int, int);
void rmv_edge_int(int [][SIZE], int, int);

void dfs(Vertex [], int [][SIZE], int s);
void dfs_recursive(Vertex[], int[][SIZE], int s);


int main () {

	Vertex graph[SIZE];
	int    adj_matrix[SIZE][SIZE];

	for(int i = 0; i < SIZE; i++) {
		graph[i].value = i;
		graph[i].visited = false;
	}

	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			adj_matrix[i][j] = 0;

	add_edge_int(adj_matrix, 0, 1);
	add_edge_int(adj_matrix, 1, 2);
	add_edge_int(adj_matrix, 2, 3);
	add_edge_int(adj_matrix, 3, 4);
	add_edge_int(adj_matrix, 4, 5);
	add_edge_int(adj_matrix, 5, 6);
	add_edge_int(adj_matrix, 6, 7);
	add_edge_int(adj_matrix, 7, 8);
	add_edge_int(adj_matrix, 8, 9);
	add_edge_int(adj_matrix, 9, 0);

	cout << "Using a stack:" << endl;
	dfs(graph, adj_matrix, 0);

	for(int i = 0; i < SIZE; i++)
		graph[i].visited = false;

	cout << endl;
	cout << "Using recursion:" << endl;
	dfs_recursive(graph, adj_matrix, 0);

	return 0;
}

void add_edge_int(int adj_matrix[][SIZE], int i, int j){
	adj_matrix[i][j] = 1;
	adj_matrix[j][i] = 1;
}

void rmv_edge_int(int* adj_matrix[SIZE], int i, int j){
	adj_matrix[i][j] = 0;
	adj_matrix[j][i] = 0;
}

void dfs(Vertex graph[], int adj_matrix[][SIZE], int s) {

	int stack[SIZE];
	int top = 0;

	stack[top] = s;
	top++;

	while(top > 0) {
		if(graph[s].visited == false) {
			graph[s].visited = 1;
			cout << "Node: " << graph[s].value << endl;

			for(int i = 0; i < SIZE; i++) {
				if(adj_matrix[s][i] == 1 && graph[i].visited == false) {
					stack[top] = i;
					top++;
				}
			}
		}

		top--;
		s = stack[top];
	}
}

void dfs_recursive(Vertex graph[], int adj_matrix[][SIZE], int s) {

	graph[s].visited = 1;
	cout << "Node: " << graph[s].value << endl;

	for(int i = 0; i < SIZE; i++)
		if(adj_matrix[s][i] == 1 && graph[i].visited == false)
				dfs_recursive(graph, adj_matrix, i);
}