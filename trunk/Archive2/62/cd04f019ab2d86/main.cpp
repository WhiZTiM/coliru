#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdio>

char EventList[16][11] = { "0123456789", "9876543210" };

uint8_t AgsEventStringArray[   16
   * 7
   // Zero Padding
   + 16*( 4 - (7%4)) %4
   + 16*sizeof(uint16_t) 
   + 16*sizeof(uint16_t)
   + sizeof(uint16_t)  ];
   
uint8_t* getAgsEvent_List( void )
{
  uint32_t event_count = 2; //MissionDatabase_getEventCount();
  uint32_t i,j;

  //EventList = MissionDatabase_getEventList();

  AgsEventStringArray[ 0 ] = static_cast<uint8_t>(event_count >> 8);
  AgsEventStringArray[ 1 ] = event_count & 0xFF;
  size_t count = 2;
  size_t length = 0;
  size_t padlength = 0;

  for( i = 0 ; i < event_count; i++ )
  {
     AgsEventStringArray[ count++ ] = static_cast<uint8_t>(( i+1 ) >> 8);
     AgsEventStringArray[ count++ ] = ( i+1 ) & 0XFF ;

     length = strlen( EventList[i] );

     AgsEventStringArray[ count++ ] = static_cast<uint8_t>(( length+1 ) >> 8);
     AgsEventStringArray[ count++ ] = ( length+1 ) & 0XFF ;

     for( j =0 ; j< length; ++j )
     {
        AgsEventStringArray[ count++ ] = EventList[i][j];
     }
     AgsEventStringArray[ count++ ] = 0;
     /* Pad the string array entry to 32 bits */
     padlength = (4 - ( (length+1) %4)) %4;
     for( ; padlength > 0; padlength-- )
     {
        AgsEventStringArray[ count++ ] = 0;
     }
  }

  std::cout << count << '\n' ;
  return AgsEventStringArray;
}

int main()
{
    getAgsEvent_List();
    
    for ( uint32_t i =0 ; i < 34; ++i )
    printf( "%02X ", AgsEventStringArray[i] );
}