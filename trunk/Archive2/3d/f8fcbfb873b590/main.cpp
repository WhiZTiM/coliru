#include <iostream>
#include <string>
#include <vector>


int main()
{
    #define COLUMN_TYPE( column_type, column_type_id ) \
        const int column_type = column_type_id;
    COLUMN_TYPE( UNSIGNED_INTEGER, 1)
    COLUMN_TYPE( INTEGER, 2)
    COLUMN_TYPE( BIT_FIELD, 3)
    #undef COLUMN_TYPE
    
	#define TABLE_ROW( table_name, table_id, column_name, column_unique_id, column_index, column_type, column_length, column_start_position, column_counter_type, wlan_command ) \
        column_type,
        
    #define DB_WLAN_T0_U0_COLUMN_STATUS_INDEX { \
        TABLE_ROW ( WLAN, 0, COLUMN_STATUS, 0, 0, UNSIGNED_INTEGER, 4, 0x0000, 0, "" ) \
        TABLE_ROW ( WLAN, 0, ANTENNA, 1, 1, UNSIGNED_INTEGER, 1, 0x0004, 0, "wl a" ) \
    }
    
    #define DB_WLAN_T0_TYPES { \
    	TABLE_ROW ( WLAN, 0, COLUMN_STATUS, 0, 0, UNSIGNED_INTEGER, 4, 0x0000, 0, "" ) \
        TABLE_ROW ( WLAN, 0, ANTENNA, 1, 1, UNSIGNED_INTEGER, 1, 0x0004, 0, "wl a" ) \
    }
    const uint8_t db_wlan_t0_types[]=DB_WLAN_T0_TYPES;
    
	#undef TABLE_ROW
    
    
	std::cout << "Unsigned integer column type value: " << UNSIGNED_INTEGER << std::endl;
    std::cout << "Integer column type value: " << INTEGER << std::endl;
    std::cout << "Bit field column type value: " << BIT_FIELD << std::endl;
    std::cout << "Column Type: " << (int)db_wlan_t0_types[0] << std::endl;
}