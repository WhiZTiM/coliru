#include <string>
#include <vector>


void read(std::string& str);
template <typename T>
void read(std::vector<T>& vec);

template <typename T>
T read()
{
    T value;
    read(value); // gcc compile error here
    return value;
}

void read(std::string& str)
{
}

template <typename T>
void read(std::vector<T>& vec)
{
}

int main(int argc, char** argv) {

    read<std::string>();
    read<std::vector<int>>();
    read<std::vector<float>>();

    return 0;
}