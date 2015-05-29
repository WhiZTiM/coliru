cp /Archive2/d5/9ef7431cbf9ac4/main.cpp hello.hpp    \
&& cp /Archive2/85/fd964a11c56c41/main.cpp hello.cpp \
&& g++ -std=c++14 -Wall -c hello.cpp                 \
&& g++ -std=c++14 -Wall -c main.cpp                  \
&& g++ -std=c++14 -Wall *.o                          \
&& ./a.out