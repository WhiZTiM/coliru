clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 << EOF
import example
assert 42 == example.spam(*range(14))
assert isinstance(example.spam(*range(16)), list)
print example.spam.__doc__
EOF
echo $?