#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <fstream>

char fmt[] = "%s\n";
static const int count = 3000000;
static char const *const string = "This is a string.";
static std::string s = std::string(string) + "\n";

class c_stream {
    FILE *file;
public:
    c_stream(char const *name) {
        file = fopen(name, "w");
    }
    operator FILE *() { return file; }
};

template <class stream, class F>
void show_time(F f, char const *fname, char const *caption) { 
    stream s ( fname );

    clock_t start = clock();
    f(s);
    clock_t ticks = clock()-start;
    std::cerr << std::setw(30) << caption 
        << ": " 
        << (double)ticks/CLOCKS_PER_SEC << "\n";
}

void use_printf(c_stream &f) {   
    for (int i=0; i<count; i++)
        fprintf(f, fmt, string);
}

void use_puts(c_stream &f) {
    for (int i=0; i<count; i++) 
        fputs(string, f);
}

void use_ostream(std::ostream &os) { 
    for (int i=0; i<count; i++)
        os << string << "\n";
}

void use_ostream_unsync(std::ostream &os) { 
    os.sync_with_stdio(false);
    for (int i=0; i<count; i++)
        os << string << "\n";
}

void use_stringstream(std::ostream &os) { 
    std::stringstream temp;
    for (int i=0; i<count; i++)
        temp << string << "\n";
    os << temp.str();
}

void use_endl(std::ostream &os) { 
    for (int i=0; i<count; i++)
        os << string << std::endl;
}

void use_fill_n(std::ostream &os) { 
    std::fill_n(std::ostream_iterator<char const *>(os, "\n"), count, string);
}

void use_write(std::ostream &os) {
    for (int i = 0; i < count; i++)
        os.write(s.data(), s.size());
}

int main() { 
    char const *filename = "/dev/null";
    show_time<c_stream>(use_printf, filename, "Time using printf");
    show_time<c_stream>(use_puts, filename, "Time using puts");
    show_time<std::ofstream>(use_ostream, filename, "Time using cout (synced)");
    show_time<std::ofstream>(use_ostream_unsync, filename, "Time using cout (un-synced)");
    show_time<std::ofstream>(use_stringstream, filename, "Time using stringstream");
    show_time<std::ofstream>(use_endl, filename, "Time using endl");
    show_time<std::ofstream>(use_fill_n, filename, "Time using fill_n");
    show_time<std::ofstream>(use_write, filename, "Time using write");
    return 0;
}

