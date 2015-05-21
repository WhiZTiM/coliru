#include <stdio.h>
#include <stdlib.h>

typedef struct  s_node
{
    struct s_node*  next;
    int             value;
}               t_node;

t_node*    append(t_node* node, int value)
{
    t_node* newNode = (t_node*)malloc(sizeof(*newNode));
    
    newNode->value = value;
    newNode->next = NULL;
    node->next = newNode;
    return (newNode);
}

unsigned int listSize(t_node const* first)
{
    unsigned int    count = 0;
    t_node const*   current = first;
    
    while (current)
    {
        current = current->next;
        ++count;   
    }
    return (count);
}

void        destroyList(t_node* first)
{
    t_node* node = first;
    t_node* next = NULL;
    
    while (node)
    {
        next = node->next;
        printf("delete node: %d\n", node->value);
        free(node);
        node = next;
    }
}

void        printList(t_node const* first)
{
    t_node const* node = first;
    
    while (node)
    {
        printf("value: %d\n", node->value);
        node = node->next;
    }
}

void        fillArrayFromList(t_node const* first, int* intArray)
{
    t_node const*   current = first;
    
    while (current)
    {
        *intArray = current->value;
        current = current->next;
        ++intArray;
    }
}

void        swapInt(int* a, int* b)
{
    int temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
}

void        sortArray(int* intArray, unsigned int count)
{
    int             exchange = 1;
    unsigned int    i = count;
    unsigned int    j = 0;
    
    while (i > 0 && exchange)
    {
        j = 0;
        exchange = 0;
        while (j < i - 1)
        {
            if (intArray[j] > intArray[j + 1])
            {
                swapInt(intArray + j, intArray + j + 1);
                exchange = 1;
            }
            ++j;
        }
        --i;
    }
}

int main()
{
    t_node*         list = (t_node*)malloc(sizeof(*list));
    t_node*         temp = NULL;
    unsigned int    count = 0;
    int*            intArray = NULL;
    unsigned int    i = 0;
    
    list->value = 0;
    list->next = NULL;
    temp = append(list, 1);
    temp = append(temp, 814);
    temp = append(temp, 117);
    temp = append(temp, 1634);
    temp = append(temp, 2);
    temp = append(temp, 3);
    temp = append(temp, 9);
    temp = append(temp, 8);
    temp = append(temp, 7);
    temp = append(temp, 6);
    temp = append(temp, 8);
    temp = append(temp, 7);
    temp = append(temp, 6);
    temp = append(temp, 84);
    temp = append(temp, 17);
    temp = append(temp, 634);
    count = listSize(list);
    printList(list);
    intArray = (int *)malloc(sizeof(*intArray) * count);
    fillArrayFromList(list, intArray);
    sortArray(intArray, count);
    for (i = 0; i < count; ++i)
        printf("value %d: %d\n", i, intArray[i]);
    destroyList(list);
    free(intArray);
}
