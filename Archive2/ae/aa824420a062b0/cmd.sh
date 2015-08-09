ln -s /Archive2/c4/a63c3bec60f2fb/main.cpp create.cpp
echo -e '======== create ==========' && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors create.cpp -o create && time ./create 
ls -l test.txt
echo -e '\n======== parse ==========' && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp -oparse && time ./parse
echo -e '\n======== parse ==========' && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors main.cpp -oparse && time ./parse