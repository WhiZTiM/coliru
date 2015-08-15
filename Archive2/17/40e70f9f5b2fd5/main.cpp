#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
	queue<int, vector<int>> s;
    
    s.push(10);
    
    cout << s.front() << endl;
    
    s.pop();
	
    return 0;
}