#include <iostream>
#include <math.h>
using namespace std;

class Node {
    public:    
    int data;
    Node* p_next;

    Node(int myData, ptr = NULL) : data(myData),
                       p_next(ptr)  
                       {}

};

int main()
{
    
    Node n4(4);
    Node n3(3, &n4)
    Node n2(2, &n3);
    Node n1(1, &n2);
    
    Node* head = &n1;
    return 0;
}
    