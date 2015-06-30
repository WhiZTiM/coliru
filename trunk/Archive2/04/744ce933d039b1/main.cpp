#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::placeholders;

void print( string message, int n )
{
    cout << message << n << endl;
}

struct call
{
    void (*fun)(string,int);
    string message;
    void operator() (int n)
    {
        fun(message, n);
    }
    call( void(*f)(string,int), string msg) 
        : fun(f), message(msg) {}
};





int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    vector<int> numbers(arr,arr+5);
    
    std::for_each(numbers.begin(), numbers.end(), call(print,"Number is "));

}