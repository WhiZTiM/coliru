echo clang:
clang++ -std=c++1z -O3 -w -pedantic -pthread -stdlib=libc++ -frtti -D_LIBCPP_DEBUG main.cpp && ./a.out
echo gcc:
g++ -std=c++14 -O3 -w -pedantic -pthread -D_GLIBCXX_DEBUG main.cpp && ./a.out