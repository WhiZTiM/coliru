#include <iostream>
#include <string>
#include <vector> // dynamically growing array collection
#include <list> // link link of nodes
#include <mutex>
#include <conio.h>
#include <stdio.h>
#include <memory>

using namespace std;

mutex m;

int i = 0;

void F1()
{
    lock_guard<mutex> lg(m);
}

void F2()
{
    lock_guard<mutex> lg(m);
}

int main()
{
    thread t1(F1);
    thread t2(F2);
    
    return 0;
}
/*
class Stack
{
    vector<int> items;
public:
    void Push(int item)
    {
        items.push_back(item);
    }
    int Pull()
    {
        int lastItem = items[items.size() - 1];
        items.pop_back();
        
        return lastItem;
    }
};

template<typename TCollection>
class Stack
{
    TCollection<int> items;
public:
    void Push(int item)
    {
        items.push_back(item);
    }
    int Pull()
    {
        int lastItem = items[items.size() - 1];
        items.pop_back();
        
        return lastItem;
    }
};

class Stack : private vector<int>, private list<int>
{
public:
    void Push(int item)
    {
        this->push_back(item);
    }
    int Pull()
    {
        int lastItem = (*this)[this->size() - 1];
        this->pop_back();
        
        return lastItem;
    }
};

int main()
{
    Stack<list<int>> s1;
    
    s1.Push(100);
    s1.Push(200);
    s1.Push(300);
    s1.Push(400);
    
    cout << s1.Pull() << endl;
    cout << s1.Pull() << endl;
    return 0;
}*/
