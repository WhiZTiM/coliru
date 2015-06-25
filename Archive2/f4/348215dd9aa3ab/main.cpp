#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
} node;



node * newBeg(node * head, int value){
    node *temp1;
    char foundFlag = 0;
    temp1 = head;
    while(temp1->next && foundFlag == 0){
        if(temp1->next->value == value){
            printf("found\n");
            return temp1->next;
        }
    }
    return head;
}

int main()
{
    node *l = malloc(sizeof *l);
    l->value = 2;
    l->next = malloc(sizeof *l);
    l->next->value = 3;
    l->next->next = NULL;
    newBeg(l,3);
    free(l->next);
    free(l);
    //newBeg(NULL,3);   // will crach the program
    return 0;
}
