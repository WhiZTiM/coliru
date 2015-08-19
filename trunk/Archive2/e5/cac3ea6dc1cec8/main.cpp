#include <stdio.h>

struct Node {
    const char* data;
    struct Node* left;
    struct Node* right;
};

struct Node MY_TREE = {
  "root", &(struct Node){"left child"}
};

int main()
{
    printf("MY_TREE.left->data is %s\n", MY_TREE.left->data);
}
