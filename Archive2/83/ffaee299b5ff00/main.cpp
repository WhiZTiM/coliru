#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    std::string gameDirectory = "";
    for (int i = 1; i < argc; i++) {
        if (argv[i] == "-game")
            gameDirectory = argv[i + 1];
    }

    if (gameDirectory == "")
        exit(0);
    else
        std::cout << gameDirectory << '\n';
}
