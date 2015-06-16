#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

void insort(vector<int>& a)
{
    for (unsigned i=1; i<a.size(); i++)
    {
        int x = a[i];
        int j = i;
        while (j>0 && a[j-1] > x)
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = x;
    }
}

struct time_scope
{
   time_scope() { start_ = chrono::steady_clock::now(); }
  ~time_scope()
  {
      auto end = chrono::steady_clock::now();
      cout << "time_scope has: "
           << chrono::duration_cast<chrono::nanoseconds>(end - start_).count()
           << " nanoseconds\n";
  } 
  
  chrono::steady_clock::time_point start_;
};

int main()
{
    vector<int> v = {2,4,31,5,6,342,8,7,344,23,7,8,57,42,432,54,677};
    
    auto start = chrono::steady_clock::now();

    {
        time_scope();
        insort(v);
//        sort(begin(v), end(v));
    }
    
    auto end = chrono::steady_clock::now();
    
    for (const auto& a : v)
        cout << a << " ";
    cout << '\n';
        
    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << " nanoseconds.\n";

    return 0;
}