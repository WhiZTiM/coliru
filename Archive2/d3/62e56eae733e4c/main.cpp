#include <stdio.h>
#include <errno.h>
#include <stdint.h>


typedef struct
{
    const uint8_t id;
    const uint8_t type;
    const uint8_t length;
    const uint8_t start_pos;
    const uint8_t col_counter;
    const uint8_t * const defaults;
} Column_t;


typedef struct
{
    const uint16_t table_id;
    
    const uint16_t schema_version;
    const uint16_t table_start_address;
    const uint16_t no_of_columns;
    const uint16_t max_no_of_rows;
    const uint16_t row_length;
    
    const Column_t * const columns;
    
} Table_t;

const Table_t const tables [] = {
    {
        0,  
        0x0102,
        0xBEEF,
        1,
        64,
        192,
        
        (const Column_t[]){
            {
                0,
                1,
                4,
                0,
                0,
                (const uint8_t[]){'T','E','S','T','\0'}
            }
        } 
    }
};

int main()
{
    
    printf("%s\r\n", tables[0].columns[0].defaults);
}

