#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list
{
    int nb;
    struct linked_list  *next;
} linked_list;

linked_list*    CreateNewItem()
{
    linked_list* item = (linked_list*) malloc(sizeof(linked_list));
    item->nb = 0;
    item->next = NULL;
    return (item);
}

void    CreateLinkedList(linked_list **linkedList)
{
    *linkedList = CreateNewItem();
}

void    AddItem(linked_list** sList, int nbValue)
{
    linked_list *ptr = *sList;
    linked_list *newItem = CreateNewItem();
    newItem->nb = nbValue;
    
    while (ptr->next != NULL)
        ptr = ptr->next;
        
    ptr->next = newItem;
}

void    DumpList(linked_list** sList)
{
    linked_list *ptr = *sList;
    
    printf("-- Dump list --\n");
    while (ptr != NULL)
    {
        printf("%d\n", ptr->nb);
        ptr = ptr->next;
    }
}

void    FreeList(linked_list** sList)
{
    linked_list *ptr = *sList;
    linked_list *toRemove;
    
    while (ptr != NULL)
    {
        toRemove = ptr;
        ptr = ptr->next;
        free(toRemove);
        printf("Free item\n");
    }
    
    *sList = NULL;
}

void    InvertList(linked_list **sList)
{
    linked_list *current = *sList;
    linked_list *prev = NULL;
    linked_list *next = current->next;
    
    while (current != NULL)
    {
        prev = current;
        current = next;
        
        if (prev == *sList)
            prev->next = NULL;
        
        if (current != NULL)
        {
            next = current->next;
            current->next = prev;
        }
    }
    
    *sList = prev;
}

int main()
{
    linked_list* list = NULL;
    
    CreateLinkedList(&list);
    list->nb = 1;
    AddItem(&list, 2);
    AddItem(&list, 3);
    AddItem(&list, 4);
    
    DumpList(&list);
    InvertList(&list);
    DumpList(&list);
    
    FreeList(&list);
    
    return (0);
}