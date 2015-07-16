#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

struct node
{
    double value;
    node * next_ptr;
    node(){}
    node(double val, node * p): value(val), next_ptr(p) {}
    ~node(){}
};

node * create()
{
    node* temp = nullptr;
    node* result;
    for(int i=0; i<5; ++i)
    {
        result = new node;
        result->value = i;
        result->next_ptr = temp;
        temp = result;
    }
    return result;
}

int main() {
    for (node* list = create(); list != nullptr; list = list->next_ptr)
        std::cout << list->value << ' ';
}