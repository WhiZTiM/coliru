#include <stdio.h>
#include <errno.h>
#include <stdint.h>


typedef struct
{
    const int id;
    const int type;
} Column_t;


typedef struct
{
    const int table_id;
    const Column_t *columns;
} Table_t;

const Table_t tables[] = {
    {1,  (const Column_t[]){{1,2},{3,4}} }, 
    {2,  (const Column_t[]){{1,2},{3,4},{5,6}} }
};

int main()
{
    
    printf("%d\r\n", tables[0].columns[1].type);
    printf("%d\r\n", tables[1].columns[2].type);
}

