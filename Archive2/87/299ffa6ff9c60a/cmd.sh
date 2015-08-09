ln -s /Archive2/76/565f70a40bf923/main.cpp create.cpp
echo -e '======== create (clang++) ==========' && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors create.cpp -o create && time ./create 
ls -l test.txt
echo -e '\n======== parse (clang++) ==========' && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp -oparse && time ./parse
echo -e '======== create (g++) ==========' && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors create.cpp -o create && time ./create 
ls -l test.txt
echo -e '\n======== parse (g++) ==========' && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors main.cpp -oparse && time ./parse