#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <sstream>

int main(int argc, char** argv) {

    std::stringstream ss, comp, decomp;
    ss << "Hello World";

    boost::iostreams::filtering_streambuf< boost::iostreams::input> in;
    in.push(boost::iostreams::gzip_compressor());
    in.push(ss);
    boost::iostreams::copy(in, comp);

    std::cout << "Compressed: ";
    std::cout << comp.str().size() << std::endl;

    comp.flush();
    comp.seekg(0ul);

    boost::iostreams::filtering_streambuf<boost::iostreams::input> inbuf;
    inbuf.push(boost::iostreams::gzip_decompressor());
    inbuf.push(comp);
    boost::iostreams::copy(inbuf, decomp);

    std::cout << "Decompressed: ";
    std::cout << decomp.str() << std::endl;
}
