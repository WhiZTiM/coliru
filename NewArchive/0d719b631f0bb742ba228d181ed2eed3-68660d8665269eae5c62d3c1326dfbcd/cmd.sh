echo 'check ulimits'
ulimit
cat cmd.sh | grep ulimit
echo 'compiling...'
time g++ -std=c++11 -O2 -Wall -Wextra -Werror -pedantic-errors main.cpp -ltbb
echo 'running...'
time ./a.out
echo 'done!'

echo 'b'