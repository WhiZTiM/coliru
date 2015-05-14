#include <fstream>

int main() {
    std::ofstream f("foo.txt");
    f << "test";
}