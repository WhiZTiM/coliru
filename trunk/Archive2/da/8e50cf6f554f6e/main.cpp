#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newnode(int data)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
struct node* inser(struct node* node, int data)
{
    if(node == NULL)
        return newnode(data);
    if(data < node->data)
        node->left = inser(node->left,data);
    else if(data > node->data)
        node->right = inser(node->right,data);
    return node;
}
void inorder(struct node* node)
{
    if(node != NULL)
    {
        inorder(node->left);
        printf("%d  ",node->data);
        inorder(node->right);
    }
}
void preorder(struct node* node)
{
    if(node != NULL)
    {
        printf("%d  ",node->data);
        preorder(node->left);
        preorder(node->right);
    }
}
void postorder(struct node* node)
{
    if(node != NULL)
    {
        postorder(node->left);
        postorder(node->right);
        printf("%d  ",node->data);
    }
}
void desce(struct node* node)
{
    if(node != NULL)
    {
        desce(node->right);
        printf("%d  ",node->data);
        desce(node->left);
    }
}
int height(struct node* node)
{
    if(node == NULL)
        return 0;
    else
    {
         int lheight = height(node->left);
         int rheight = height(node->right);

        if(lheight>rheight)
            return(lheight+1);
        else
            return(rheight+1);
    }
}
void printgivenlevel(struct node* root, int level)
{
    if(root == NULL)
        return;
    if(level == 1)
        printf("%d ",root->data);
    else if(level >1)
    {
        printgivenlevel(root->left,level-1);
        printgivenlevel(root->right,level-1);
    }
}
void leverorder(struct node* node)
{
    int h = height(node);
    int i=1;
    while(i<=h)
        printgivenlevel(node,i++);
}

int main()
{
    struct node* root=NULL;
    root = inser(root,50);
    inser(root,30);
    inser(root,20);
    inser(root,40);
    inser(root,70);
    inser(root,60);
    inser(root,80);

    printf("Printing tree using In-Order traversal:");
    inorder(root);
    printf("\nPrinting tree using Pre-Order traversal:");
    preorder(root);
    printf("\nPrinting tree using Post-Order traversal:");
    postorder(root);
    printf("\nPrinting tree using desce-Order traversal:");
    desce(root);
    printf("\nPrinting tree using level-Order traversal:");
    leverorder(root);


    return 0;
}
