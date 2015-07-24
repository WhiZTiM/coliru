clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors -pthread main.cpp && ./a.out
#echo ========== && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors -pthread main.cpp && ./a.out
for file in $( ls *.txt ); 
do 
   echo path: $file && cat $file && echo
done