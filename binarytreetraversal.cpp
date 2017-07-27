/*
 *  Implementation of a recursive breadth first search on a binary tree
 *  Testing of in-, pre-, and post-order traversal
 *  Testing of argument passing
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MAX 16

struct Node {
	int value;
	Node* left;
	Node* right;
};

void insert(Node* &, Node &);
void traverse(Node*, short int);

int main (int argc, char* argv[]) {

	if(argc != 2) {
		cout << "Usage: " << argv[0] << " [type_of_traversal]" << endl;
		cout << "where type_of_traversal can assume one of the following:" << endl;
		cout << "in or in-order\t\tfor in-order traversal" << endl;
		cout << "pre or pre-order\tfor in-order traversal" << endl;
		cout << "post or post-order\tfor in-order traversal" << endl;
		return 0;
	}

	Node* btree = NULL;
	short int t;

	     if(argv[argc-1] == "in"   || argv[argc-1] == "in-order")   t = 0;
	else if(argv[argc-1] == "pre"  || argv[argc-1] == "pre-order")  t = 1;
	else if(argv[argc-1] == "post" || argv[argc-1] == "post-order") t = 2;


	srand(time(NULL));
	Node nodes[MAX];
	for(int i = 0; i < MAX; i++) {
		nodes[i].value = rand() % (MAX*MAX);
		nodes[i].left = NULL;
		nodes[i].right = NULL;
		insert(btree, nodes[i]);
	}

	cout << "type of traversal: " << argv[argc-1] << endl;
	traverse(btree, t);

	return 0;
}

void insert(Node* &btree, Node &n) {

	if(btree != NULL) {
		Node* i = btree;
		while(true) {
			if(n.value < i->value){
				if(i->left != NULL)
					i = i->left;
				else {
					i->left = &n;
					break;
				}
			}
			else{
				if(i->right != NULL)
					i = i->right;
				else {
					i->right = &n;
					break;
				}

			}
		}
	} else {
		btree = &n;
	}
}

void traverse(Node* i, short int t) {
	if(t == 0) cout << "Node " << i->value << endl;
	if(i->left != NULL) traverse(i->left, t);
	if(t == 1) cout << "Node " << i->value << endl;
	if(i->right != NULL) traverse(i->right, t);
	if(t == 2) cout << "Node " << i->value << endl;
}