#ifndef TEST_H
#define TEST_H

#include <iostream>

using namespace std;

class Test {
public:
    void func(float f, int i) {
        cout<<"func" << i <<endl;
    }
    void print(float f) {
        cout << "nil" << endl;
    }
    void print(float f, int n, char *str) {
        cout << n << str << endl;
    }
    void print(float f, int n, int m) {
        cout << n << "," << m << endl;
    }

    template<typename ... Args>
    void test(float, Args ... args) ;
};