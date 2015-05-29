#include <iostream>

//Proper encapsulation is not included for terseness and clarity
class Node {
public:
    int num;
    Node* next;
    
    Node(int n) :
        num(n),
        next(nullptr) {
    };
    
    ~Node() {}
};

int main() {
    Node a(0);
    Node b(1);
    Node c(2);
    Node d(3);
    Node e(4);
    
    //String the nodes together, linking like metal chainlinks
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    
    //Can you see how the "link" actually works here?
    //Each Node's "next" pointer points to the next node.
    std::cout << "Node a: " << a.num << std::endl;
    std::cout << "Node b: " << a.next->num << std::endl;
    std::cout << "Node c: " << a.next->next->num << std::endl;
    std::cout << "Node d: " << a.next->next->next->num << std::endl;
    std::cout << "Node e: " << a.next->next->next->next->num << std::endl;
    
    //What if I were to point e to the start of a?
    e.next = &a;
    
    std::cout << "Node e->next: " << e.next->num << std::endl;
    //It's node a!
    
    //Node e.next is now accessible through the linked list:
    std::cout << "Node e->next = a.next->next->next->next->next: " << a.next->next->next->next->next->num << std::endl;
    
    //Usually people just use a for loop for this type of stuff.
    //Let's use a lambda function to write one right here:
    auto index_func = [](Node* head, size_t index) {
        Node* current = head;
        Node* next = head->next;
        
        for (int i = 0; i < index; ++i) {
            if (next != nullptr) {
                //Hey, look at the pointers fly!
                current = next;
                next = current->next;
            } else {
                std::cout << "Whoops, we hit a null pointer before we got to our index!" << std::endl;
                break;
            }
        }
        
        return current->num;
    };
    
    //This is the same as finding the 6th node in the list (but since it's zero-indexing it's [5])
    std::cout << index_func(&a, 5) << std::endl;
    
    //We can also continue to do this:
    std::cout << index_func(&a, 499) << std::endl;
    //This is me accessing the 500th element, which, since our back links to our head node, it's the 4th node, d.
    
    return 0;   
}