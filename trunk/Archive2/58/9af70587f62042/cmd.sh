clang++ -std=c++14 -O2 -I/usr/include/python2.7 -ftemplate-backtrace-limit=0 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 << EOF
import example
print "done importing example"
test1 = example.Test()
test2 = example.Test()
test1 = None
example.use_test(test2)
print "end of python script"
EOF
echo $?