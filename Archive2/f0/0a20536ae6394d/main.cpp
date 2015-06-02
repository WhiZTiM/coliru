#include <cstdio>
#include <codecvt>
#include <clocale>
#include <fstream>
#include <iostream>
//#include <experimental/filesystem>
//namespace fs = std::experimental::filesystem;

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    std::locale::global(std::locale("en_US.utf8"));

//    fs::path p = fs::u8path(u8"要らない.txt");
    fs::path p = (u8"要らない.txt");
    // native string representation can be used with OS APIs
//    std::ofstream(p) << "contentx";
    std::ofstream(p.string()) << "contentx";
    if(std::FILE* f = std::fopen(p.c_str(), "r")) {
        int ch;
        while((ch=fgetc(f))!= EOF) putchar(ch);
        std::fclose(f);
    }

    std::cout.imbue(std::locale());
    std::cout << "\nFile name in narrow multibyte encoding: "
              << p.string() << '\n';
    // as wide string
    p.imbue(std::locale()); // TODO remove
    std::wbuffer_convert<std::codecvt_utf8<wchar_t>> convbuf(std::cout.rdbuf());
    std::wostream convout(&convbuf);
    convout << L"File name in wide encoding: "
            << p.wstring() << '\n';
            
    std::cout << " note: path::value_type on this platform is " << typeid(fs::path::value_type).name() << '\n';

    fs::remove(p);
}
