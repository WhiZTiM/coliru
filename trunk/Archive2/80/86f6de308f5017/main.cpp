/*
 * tree.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: Quang Hoang
 */

/*
 * main.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: Quang Hoang
 */
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Node {
public:
    int left;
	int height;
	Node * next;
	void setNext(Node nx);
	void insertChild(int l, int h);
	void delChild();
	Node():left(0),height(0),next(NULL){};
	Node(int l, int h);
};

void Node::insertChild(int l, int h) {
	Node nx = Node(l, h);
	nx.next = next;
	next = &nx;
}

Node::Node(int l, int h) {
	left = l;
	height = h;
	next = NULL;
}
void Node::setNext(Node nx) {
	next = &nx;
}

void Node::delChild() {
	next = next->next;
}

Node* current;
Node* temp;

void updateNode(Node *c, int r, int h) { // buildings starting with l until l>r or null
	Node temp;
	while (c->left < r) {
		if (c->next == NULL) {	// leaf
			c->height = h;	//update new height
			temp = Node(r, 0);	// new leaf
			c->next = &temp;
			return;	//done
		}
		//from now on c is not a leaf
		if (c->next->left >= r) {
			if (c->height > h) {
				if (c->next->left > r) {
					c->insertChild(r, h); // left passes r
					return;	//done
				}
			}
		} else {
			if (c->height > h) {
				c = c->next;
			} else {
				c->height = h;
				if (c->next->height <= h) {
					c->delChild();
				} else {
					c = c->next;
				}
			}
		}
	}
}
int main() {
	string line;
	int l = 0, h = 0, r = 0;	// input holders

	getline(cin, line);
	istringstream iss(line);
	iss >> l >> h >> r;

	Node root(l, h);
	Node end(r, 0);
	end.next = NULL;
	root.next = &end;

	while (getline(cin, line)) {
		istringstream iss(line);
		iss >> l >> h >> r;

		current = &root;
		temp = current;

		// add next building to the picture
		while (temp->next->left < l) {
			temp = temp->next;
		}

		// now current.left >= l
		if (temp->next == NULL) {	// reach end
			temp->next->insertChild(l, h);
			temp->next->next->insertChild(r, 0);
		}
		updateNode(temp,h,r);
	}
	while (current->next!=NULL){
	cout << (*current).left << current->height<<" ";
	current=current->next;
	}
}
