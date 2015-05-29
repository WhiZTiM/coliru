cp /Archive2/7a/4651ddb4aaef15/main.cpp hello.hpp    \
&& cp /Archive2/85/fd964a11c56c41/main.cpp hello.cpp \
&& g++ -std=c++14 -Wall -c hello.cpp                 \
&& g++ -std=c++14 -Wall -c main.cpp                  \
&& g++ -std=c++14 -Wall *.o                          \
&& ./a.out