#include <iostream>
#include <fstream>

int main()
{
    const char* const path = "example.txt" ;

    // create file
    std::ofstream(path) << "first sentence\nsecond sentence\nthird sentence\n" ;

    // number of characters in file
    {
        std::ifstream file(path) ; // open as text
        char c ;
        std::streamoff cnt = 0 ;
        while( file.get(c) ) ++cnt ;
        std::cout << "file '" << path << "' contains " << cnt << " characters\n" ;
    }

    // number of bytes in file
    {
        std::ifstream file( path, std::ios::binary ) ; // open as binary
        char c ;
        std::streamoff cnt = 0 ;
        while( file.get(c) ) ++cnt ;
        std::cout << "file '" << path << "' contains " << cnt << " bytes\n" ;
    }

    {
        std::ofstream file( path, std::ios::in | std::ios::out ) ; // do not truncate
        file.seekp( 0, std::ios::end ) ; // seek to end
        std::cout << "after seek to end: " << std::streamoff( file.tellp() ) << '\n' ;

        for( int i = 0 ; i < 24 ; ++i ) file.put( '.' ) ; // write 24 dots
        std::streamoff offset( file.tellp() ) ;
        std::cout << "after writing 24 dots: " << offset << '\n' ;

        file << "should add this text from offset " << offset << '\n' ;
        std::cout << "after writing more stuff: " << std::streamoff( file.tellp() ) << '\n' ;
    }

    // dump the contents of the modified file
    std::cout << "\n====== contents of file '" << path << "' ==========\n\n"
              << std::ifstream(path).rdbuf() << "\n=========================\n" ;
}
