#include <stdio.h>
#include <stdlib.h>

#define POLY_CRC16  0xa001
#define INIT_CRC16  0

unsigned short checksum_crc16(unsigned char *in, int length)
{
  register unsigned short crc, bit;
  // do stuff
  return crc;
}

int main( int argc, char *argv[] ) {
  unsigned char test[] = "abcd";

  fprintf( stdout, "check '%s' of size %lu output: %u\n", "lol", sizeof test, checksum_crc16( test, sizeof test ) );
}