g++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp && ./a.out <<INPUT
#define FOO
led_zeppelin=9
the_shins=9
dead_mau5=6
portishead=10
#ifdef FOO
foo_fighters=7
#define ZOO
#else
the_who=6
#define QUX
#endif

#ifdef EXTERNAL

#ifdef ZOO
zoowasdefined=yes
#else
zoowasdefined=no
#endif

#ifdef QUX
quxwasdefined=yes
#else
quxwasdefined=no
#endif
#endif

kanye_west=4
#undef FOO
#define BAR
INPUT