#include<stdio.h>
#include<stdlib.h>
#define NO_OF_CHARS 256

struct node
{
    int data;
    struct node* next;
};

void push(struct node** node,int data)
{
    struct node* current = *node;
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;

    if(*(node) == NULL)
    {
        *node = temp;
        return;
    }

    while(current->next != NULL)
        current = current->next;
    current->next = temp;
}

void print(struct node* head)
{
    while(head != NULL)
    {
        printf("%d ->",head->data);
        head = head->next;
    }
}

void removedup(struct node* head)
{
    struct node* current = head;
    struct node* prev=NULL ;
    struct node* temp ;
    int binhash[NO_OF_CHARS]={0};

    int val;

    while(current->next!=NULL)
    {
        val = current->data;
        //printf("1:%d  \n",val);
        //printf("2:%d  ",binhash[temp]);
       if(binhash[val] == 0)
        {
            binhash[val]=1;
            //printf("1::%d\n",current->data);
            prev = current;
            current = current->next;
            //printf("2::%d\n",current->data);
            continue;
        }
        temp = current;
        prev->next = current->next;
        current = current->next;
        free(temp);
    }
    (current->next) = NULL;


}

int main()
{
    struct node* head=NULL;
    push(&head,12);
    push(&head,11);
    push(&head,12);
    push(&head,21);
    push(&head,41);
    push(&head,21);
    push(&head,43);

    print(head);
    removedup(head);

    printf("\nreverse:");
    print(head);
    
    printf("\n");

}
