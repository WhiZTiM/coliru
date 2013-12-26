#include <string>
#include <stack>
#include <queue>
using namespace std;

template<template<class,class> class T>
class Cont {
        T<int, allocator<int>> i;
        T<string, allocator<string>> s;

        void doSomething() {
                // puch exists on both stack and queue
                i.push(12);
                s.push("dasdd");
        }
};
 
int main() {
    Cont<stack> v;
    Cont<queue> q;
    
    /*v.doSomething();
    q.doSomething();*/
}