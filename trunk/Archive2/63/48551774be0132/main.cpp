#include <stdio.h>
#include <stdlib.h>

typedef struct SimpleList SimpleList;

struct SimpleList
{
    int value;
    SimpleList* next;
};

void        addSimpleListStart(SimpleList** ptrSimpleListStart, int iValue)
{
    SimpleList* ptrSimpleListNew;

    if (!(ptrSimpleListNew = (SimpleList*)malloc(sizeof(ptrSimpleListNew))))
    {
        fprintf(stderr, "Error : malloc failed\n");
        return;
    }
    ptrSimpleListNew->value = iValue;
    ptrSimpleListNew->next = *ptrSimpleListStart;
    *ptrSimpleListStart = ptrSimpleListNew;
}

void        addSimpleListEnd(SimpleList** ptrSimpleListStart, int iValue)
{
    SimpleList* ptrSimpleListNew;
    SimpleList* ptrSimpleListEnd;

    if (!(ptrSimpleListNew = (SimpleList*)malloc(sizeof(ptrSimpleListNew))))
    {
        fprintf(stderr, "Error : malloc failed\n");
        return;
    }
    for (ptrSimpleListEnd = *ptrSimpleListStart;
         ptrSimpleListEnd && ptrSimpleListEnd->next;
         ptrSimpleListEnd = ptrSimpleListEnd->next);
    ptrSimpleListNew->value = iValue;
    ptrSimpleListNew->next = NULL;
    if (!ptrSimpleListEnd)
        *ptrSimpleListStart = ptrSimpleListNew;
    else
        ptrSimpleListEnd->next = ptrSimpleListNew;
}

void        deleteSimpleList(SimpleList** ptrSimpleListStart, SimpleList* ptrSimpleListDelete)
{
    SimpleList* ptrSimpleListPrevious;

    if (!*ptrSimpleListStart || !ptrSimpleListDelete)
    {
        fprintf(stderr, "Error : can't delete NULL element\n");
        return;
    }
    if (*ptrSimpleListStart == ptrSimpleListDelete)
    {
        *ptrSimpleListStart = ptrSimpleListDelete->next;
        free(ptrSimpleListDelete);
        return;
    }
    for (ptrSimpleListPrevious = *ptrSimpleListStart;
         ptrSimpleListPrevious && ptrSimpleListPrevious->next != ptrSimpleListDelete;
         ptrSimpleListPrevious = ptrSimpleListPrevious->next);
    if (!ptrSimpleListPrevious)
    {
        fprintf(stderr, "Error : can't find element\n");
        return;
    }
    ptrSimpleListPrevious->next = ptrSimpleListDelete->next;
    free(ptrSimpleListDelete);
}

void        printSimpleList(SimpleList* ptrSimpleListStart)
{
    SimpleList* ptrSimpleListElement;

    printf("---Print SimpleList :\n");
    for (ptrSimpleListElement = ptrSimpleListStart; ptrSimpleListElement;
         ptrSimpleListElement = ptrSimpleListElement->next)
        printf("%d\n", ptrSimpleListElement->value);
}

int main()
{
    SimpleList* ptrSimpleListStart = NULL;

    for (int i = 10; i != 20; i++)
        addSimpleListEnd(&ptrSimpleListStart, i);
    printSimpleList(ptrSimpleListStart); // 10 à 19
    for (int i = 0; i != 10; i++)
        addSimpleListStart(&ptrSimpleListStart, i); // 9 à 0 && 10 à 19
    printSimpleList(ptrSimpleListStart);
    for (int i = 20; i != 40; i += 2)
    {
        addSimpleListStart(&ptrSimpleListStart, i);
        addSimpleListEnd(&ptrSimpleListStart, i + 1);
    }
    printSimpleList(ptrSimpleListStart); // 39 à 20 && 9 à 0 && 10 à 19 && 22 à 38
    for (int i = 0; i != 10; i++)
        deleteSimpleList(&ptrSimpleListStart, ptrSimpleListStart->next);
    printSimpleList(ptrSimpleListStart);
    for (SimpleList* ptrSimpleListDelete = ptrSimpleListStart; ptrSimpleListDelete;
         ptrSimpleListDelete = ptrSimpleListStart)
        deleteSimpleList(&ptrSimpleListStart, ptrSimpleListDelete);
    printSimpleList(ptrSimpleListStart);
    return 0;
}
