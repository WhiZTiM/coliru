clang++ -std=c++1z -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 -pthread main.cpp /usr/lib/x86_64-linux-gnu/libstdc++.so.6 && ./a.out <<< 1 && ./a.out <<< 0
#g++ -std=c++1z -Wall -Wextra -pedantic-errors -O3 -pthread main.cpp && ./a.out
#clang++ -std=c++1z -E -P main.cpp
#clang -x c -std=c11 -Wall -Wextra -pedantic-errors -O3 main.cpp && ./a.out