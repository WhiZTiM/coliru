#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("main.cpp",std::ios::binary);
    if (ifs.is_open())
    {       
        boost::iostreams::stream<boost::iostreams::mapped_file_source> is("main.cpp");
        if (is.seekg(200, is.beg))
            std::cout << is.rdbuf();
    }
}
