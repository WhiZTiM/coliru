#include <iostream>

class Node {
 private:
    Node* prev;

 public:
    void changeBaseLast(Node* base);
    
    explicit Node(Node* parent) : prev(parent) {

    Node* foo_ptr = this;

    while (foo_ptr->prev != 0) {
        foo_ptr = foo_ptr->prev;
    }
    
    changeBaseLast(foo_ptr);

        // foo_ptr points to Base, how can I now change Base::last?
    }
    
    int data;
};

class Base : public Node {
 private:
    Node* last;

 public:
    int flag;
    Base() : Node(0), last(this), flag(0) {}
    
};

void Node::changeBaseLast(Node* base) {
    Base* base_ptr = static_cast<Base*>(base);
    base_ptr->flag=1;
}



int main() {
    Node* n = new Base;
    new Node(n);
    std::cout << static_cast<Base*>(n)->flag << std::endl;
}