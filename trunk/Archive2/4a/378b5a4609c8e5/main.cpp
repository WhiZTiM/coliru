#include <iostream>
#include <fstream>

int main()
{
    std::ofstream fout( "out.txt" ) ;

    std::cout << "1. one\n" ; // this goes to stdout
    fout << "2. two\n" ; // this goes to out.txt

    // flush the buffers
    std::cout.flush() ;
    fout.flush() ;

    // replace the streambuf of cout with that of fout
    auto stdout_buf = std::cout.rdbuf( fout.rdbuf() ) ;

    std::cout << "3. three\n" ; // this goes to out.txt

    // restore the old streambuf
    std::cout.flush() ;
    std::cout.rdbuf( stdout_buf ) ;
    std::cout << "4. four\n" ; // this goes to stdout
}
