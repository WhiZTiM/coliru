clang++ -std=c++1y -stdlib=libc++ main.cpp -lsupc++ -Os -DLIBRARY="\"libc++\"" && ./a.out; g++ -std=c++1y main.cpp -Os -DLIBRARY="\"libstdc++\"" && ./a.out