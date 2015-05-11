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
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
struct node* inser(struct node* root, int data)
{
    if(root == NULL)
        return newnode(data);
    else if(data<root->data)
        root->left = inser(root->left,data);
    else
        root->right = inser(root->right,data);
    return root;
}
void inorder(struct node* root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%d  ",root->data);
        inorder(root->right);
    }
}
int noofnodes(struct node* root)
{
    if(root == NULL)
        return 0;
    else
        return (noofnodes(root->left)+1+noofnodes(root->right));
}
int nooffullnodes(struct node* root)
{
    if(root==NULL)
        return 0;
    else if(root->left==NULL&&root->right == NULL)
        return 0;
    else if(root->left!=NULL && root->right==NULL)
        nooffullnodes(root->left);
    else if(root->left==NULL&& root->right!=NULL)
        nooffullnodes(root->right);
    else if(root->left!=NULL && root->right!=NULL)
        return 1+nooffullnodes(root->left)+nooffullnodes(root->right);
}
void printinrange(struct node* root,int k1,int k2)
{
    if(root == NULL)
        return;
    if(k1 < root->data)
        printinrange(root->left,k1,k2);
    if(k1 <= root->data && k2 >= root->data)
        printf(" %d",root->data);
    if(k2 > root->data)
        printinrange(root->right,k1,k2);
}

int main()
{
    struct node* root = NULL;
    root = inser(root,50);
    inser(root,30);
    inser(root,20);
    inser(root,40);
    inser(root,70);
    inser(root,60);
    inser(root,80);
    printf("printing using In-Order traversal:");
    inorder(root);
    printf("\n No of nodes:%d",noofnodes(root));
    printf("\n nooffullnodes : %d",nooffullnodes(root));
    printf("\nNo of elements in range:");
    printinrange(root,30,70);
}
