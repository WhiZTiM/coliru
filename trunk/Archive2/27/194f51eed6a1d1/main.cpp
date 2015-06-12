#include <fstream>
#include <iostream>

/// 8-bit unsigned byte.
typedef unsigned char my_byte;

/// byte based streams
typedef std::basic_ofstream<my_byte, std::char_traits<my_byte> > my_byte_ofstream;
typedef std::basic_ifstream<my_byte, std::char_traits<my_byte> > my_byte_ifstream;

int main()
{
  // Writing...
  {
    my_byte_ofstream fout( "test.dat", std::ios::out|std::ios::trunc|std::ios::binary );
    fout.write( (const my_byte*)"Hello world!", 6 );
    if( !fout )
    {
      std::cout << "Error writing" << std::endl;;
      return 1;
    }
  }

  // Reading...
  my_byte buf[6];
  my_byte_ifstream fin( "test.dat" );
  fin.read( buf, 6 );

  // Output what we've read (expected to be similar to what we've wrote)
  std::cout << buf[0] << buf[1] << buf[2] << buf[3] << buf[4] << buf[5] << std::endl;

  return 0;
}