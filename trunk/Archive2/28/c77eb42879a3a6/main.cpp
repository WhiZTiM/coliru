#include <iostream>
#include <cstdio>
#include <cstdlib>
 
int main()
{
    std::FILE* tmpf = std::tmpfile();
    std::fputs("Alan Turing\n", tmpf);
    std::fputs("John von Neumann\n", tmpf);
    std::fputs("Alonzo Churuuuuuuuuuuuuuch\n", tmpf);
 
    std::rewind(tmpf);
    char buf[8];
    while (std::fgets(buf, sizeof buf, tmpf) != NULL) {
        std::cout << '"' << buf << '"' << '\n';
    }
}