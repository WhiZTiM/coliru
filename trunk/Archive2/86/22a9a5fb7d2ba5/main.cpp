// This code is released under the terms of the "CC0" license.  Full terms and conditions
// can be found at: http://creativecommons.org/publicdomain/zero/1.0/

#include <typeinfo>
#include <iostream>
#include <tuple>
#include <utility>
using namespace std;

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0 (EVAL0 (EVAL0 (__VA_ARGS__)))
#define EVAL2(...) EVAL1 (EVAL1 (EVAL1 (__VA_ARGS__)))
#define EVAL3(...) EVAL2 (EVAL2 (EVAL2 (__VA_ARGS__)))
#define EVAL4(...) EVAL3 (EVAL3 (EVAL3 (__VA_ARGS__)))
#define EVAL(...)  EVAL4 (EVAL4 (EVAL4 (__VA_ARGS__)))

#define MAP_END(...)
#define MAP_OUT

#define MAP_GET_END() 0, MAP_END
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) MAP_NEXT0 (test, next, 0)
#define MAP_NEXT(test, next)  MAP_NEXT1 (MAP_GET_END test, next)

#define MAP0(f, additional, x, peek, ...) f(x, additional) MAP_NEXT (peek, MAP1) (f, additional, peek, __VA_ARGS__)
#define MAP1(f, additional, x, peek, ...) f(x, additional) MAP_NEXT (peek, MAP0) (f, additional, peek, __VA_ARGS__)
#define MAP(f, additional, ...) EVAL (MAP1 (f, additional, __VA_ARGS__, (), 0))

#define PRINT(a, PREFIX) printf(#PREFIX": %d", a);
#define PRINT_ALL(PREFIX, ...) MAP(PRINT, PREFIX, __VA_ARGS__)

// test
int main()
{
    PRINT_ALL(("GAV", "aa"), 100, 200, 300, 400, 500, 600, 700, 800, 900);
	return 0;
}
