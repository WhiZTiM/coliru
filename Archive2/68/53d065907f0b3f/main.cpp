struct Base {};

#define b() Base

struct A: ::b() {};