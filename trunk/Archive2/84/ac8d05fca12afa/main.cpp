#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* prev;
    struct node* next;
};
void append(struct node** head,int data)
{
    struct node* current = *head;
    struct node* temp=(struct node*)malloc(sizeof(struct node*));
    temp->data = data;
    temp->next = NULL;
    if(*(head)== NULL)
    {
        temp->prev = NULL;
        *head = temp;
        return;
    }
    while(current->next != NULL)
        current = current->next;
    temp->prev=current;
    current->next = temp;
}
void print(struct node* head)
{
    while(head!= NULL)
    {
        printf("%d  ",head->data);
        head=head->next;
    }
}
void deletelist(struct node** head, int data)
{
    struct node* temp = NULL;
    struct node* current = *head;
    if((*head)->data == data)
    {
        temp = *head;
        *head = (*head)->next;
        return;
    }
    while(current->next != NULL)
    {
        if(current->data == data)
        {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            temp = current;
            free(temp);
        }
        current = current->next;
    }
    if(current->next == NULL && current->data == data)
    {
        current->prev->next = NULL;
        temp = current;
        free(temp);
    }
}
void reverselist(struct node** head)
{
    struct node* temp = NULL;
    struct node* current = *head;
    while(current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if(temp!=NULL)
        *head = temp->prev;
}
int main()
{
    struct node* head;
    append(&head,10);
    append(&head,20);
    append(&head,30);
    append(&head,40);
    append(&head,50);

    print(head);
    printf("\n");
    reverselist(&head);
    print(head);
    deletelist(&head,50);
    printf("\n");
    print(head);
}
