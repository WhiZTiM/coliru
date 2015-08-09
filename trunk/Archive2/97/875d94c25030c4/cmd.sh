ln -s /Archive2/44/34ae97fc622d99/main.cpp create.cpp
echo -e '======== create ==========' && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors create.cpp -o create && time ./create 
ls -l test.txt
echo -e '\n======== parse ==========' && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp -oparse && time ./parse test.txt test2.txt
echo -e '\n======== parse ==========' && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors main.cpp -oparse && time ./parse test.txt test2.txt