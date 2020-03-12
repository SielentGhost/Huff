#pragma once
#include<iostream>
#include<vector>
using namespace std;
class Node
{
public:
	int a;
	char c;
	Node *left, *right;
	Node() { left = right = NULL; }
	Node(Node *L, Node *R) {
		left = L;
		right = R;
		a = L->a + R->a;
	}
};
struct MyCompare {
	bool operator()(const Node* l, const Node* r) {
		return l->a < r->a;
	}
};
vector<bool> code;
map<char, vector<bool>>table;
void print(Node* root, unsigned k = 0) {
	if (root != NULL) {
		print(root->left, k + 3);
		for (unsigned i = 0; i < k; i++) {
			cout << "   ";
		}
		if (root->c) cout << root->a << " (" << root->c << ")" << endl;
		else cout << root->a << endl;
		print(root->right, k + 3);
	}
}
void BuildTable(Node *root) {
	if (root->left != NULL) {
		code.push_back(0);
		BuildTable(root->left);
	}
	if (root->right != NULL) {
		code.push_back(1);
		BuildTable(root->right);
	}
	//if (root->left == NULL && root->right == NULL) table[root->c] = code;
	if (root->c) table[root->c] = code;
	if (!code.empty())
		code.pop_back();
}
