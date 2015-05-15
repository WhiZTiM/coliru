clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 <<EOF
import example
import time
foo = example.Foo()
foo.start()
time.sleep(3)
foo.stop()
EOF
echo $?