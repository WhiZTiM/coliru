g++ -std=c++11 -O2 -I /usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o Test.so
python2.7 <<HERE
from Test import *

print 'suckit'

class Bar(Base):
    def __init__(self):
        pass

print 'asd'
foo(Base()) #works
print 'qwe'
foo(Bar()) #error
print 'asd'

HERE