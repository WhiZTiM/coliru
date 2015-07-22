g++ -I /usr/include/python2.7 -fpic -pedantic -Wall -c -o orm.o main.cpp
g++ -o orm.so -shared orm.o -lboost_python -lpython2.7
python << EOF
import orm
o = orm.ORM()
o.foo()
EOF