#include <iostream>
#include <string>
#include <stack>
#include <vector>

template <typename T>
class MyQu
{
    public:
        T front();
        T back() const { return stack1.top(); }
        void pop();
        void push(const T & val);
    private:
        std::stack<T> stack1;
        std::stack<T> stack2;       
        void reverseSwapStack();
};

template <typename T>
void MyQu<T>::push(const T & val)
{
    stack1.push(val);
}

template <typename T>
void MyQu<T>::reverseSwapStack()
{
    std::stack<T> &src = stack1.empty() ? stack2 : stack1;
    std::stack<T> &dest = !stack1.empty() ? stack2 : stack1;
    while(!src.empty())
    {
        dest.push(src.top());
        src.pop();
    }
}

template <typename T>
T MyQu<T>::front()
{
    reverseSwapStack();
    T tmp = stack2.top();
    reverseSwapStack();
    return tmp;    
}

template <typename T>
void MyQu<T>::pop()
{
    reverseSwapStack();
    stack2.pop();
    reverseSwapStack();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    MyQu<char> queue;
    queue.push('a');
    queue.push('b');
    queue.push('c');
    std::cout<<queue.back();
    std::cout<<queue.front();
    queue.pop();
    std::cout<<queue.back();
    std::cout<<queue.front();
//    queu
}
