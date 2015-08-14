echo -e "Clang:\n" && clang++ -std=c++14 -O3 -Wall -pedantic-errors -pthread main.cpp && ./a.out
echo -e "\nGCC:\n"  && g++ -std=c++14 -O3 -Wall -pedantic-errors -pthread main.cpp && ./a.out