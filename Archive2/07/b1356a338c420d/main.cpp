
#include <iostream>
#include <array>
#include <algorithm>

class Node;

struct
{
   bool operator()(Node* const &a, Node* const &b) { return uintptr_t(a) < uintptr_t(b); } 
} node_comparison;

int main() {
   std::vector<Node *> vector(10);
   for (int i = 9; i >= 0; i--)
   {
       vector[i] = (Node *)malloc(100);
   }
    
    std::sort(vector.begin(), vector.end(), node_comparison);
    
    for (int i=0 ; i < 10; i++)
        printf("%p\n", (void *)vector[i]);
}