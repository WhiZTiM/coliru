g++ -O0 -ggdb main.cpp && echo -e 'set width 0\nset height 0\nset verbose off\n\nb Foo::operator+(int)\ncommands 1\n  frame 1\n  continue\nend\n\nrun\n' > a.out.gdb && gdb --batch --command=a.out.gdb ./a.out