ln -s /Archive2/76/565f70a40bf923/main.cpp create.cpp
echo -e '======== create srce file (g++) ==========' && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors create.cpp -o create_srce && time ./create_srce 
ls -l test.txt
echo -e '\n======== create dest file (g++) ==========' && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors main.cpp -ocreate_dest && time ./create_dest test.txt test_out.txt 
ls -l test_out.txt