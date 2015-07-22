clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 << EOF
import example
day = example.build_day(1, 2);
assert(day)
EOF
echo $?