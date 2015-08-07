#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

class Node
{
    public:
        Node(int d) : data(d) {};
        int data;
        Node *left;
        Node *right;
};

int main()
{   
    std::vector<Node*> tree;
    Node *n1 = new Node(1);
    n1->left = new Node(2);
    n1->right = new Node(3);
    
    tree.push_back(n1);
    tree.push_back(n1->left);
    tree.push_back(n1->right);
    
    for(auto it = tree.begin(); it != tree.end(); it++) {
        std::cout << *it->data << std::endl;   
    }
}
