//Solve the LeetCode problem at https://leetcode.com/problems/min-stack/
#include <iostream>
#include <stack>

using namespace std;

class MinStack {
public:
    MinStack() { }
    
    void push(int x) {
        st.push(x);
        if (minst.empty() || x<minst.top()) {
            minst.push(x);
        }
    }
    void pop() {
        int data=st.top();
        st.pop();
        if (!minst.empty() && minst.top()==data) {
            minst.pop();
        }
    }
    int top() {
        return st.top();
    }
    int getMin() {
        return minst.top();
    }
private:
    stack<int> st;
    stack<int> minst;
};

int main()
{
    
}
