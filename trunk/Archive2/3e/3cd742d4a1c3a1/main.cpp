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


bool is_greater( int a, int b )
{
return a > b;
}







int main()
{
    int arr[] = { 4, 2, 5, 1, 3 };
    vector<int> numbers(arr,arr+5);
    
    std::sort( numbers.begin(), numbers.end(), is_greater ); // sort in descending order

    for(auto n : numbers )
        cout << n << " ";
    cout << endl;
}