#include <iostream>

using namespace std;

struct node 
{
    int data;
    struct node *next;
};

int main() 
{
    struct node* head = NULL;
    cout<<sizeof(struct node)<<"\n"<<sizeof(head)<<"\n"<<sizeof(int);
}