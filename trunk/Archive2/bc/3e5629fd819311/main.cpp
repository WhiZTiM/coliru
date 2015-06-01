#include <iostream>
using namespace std;
 
template<class T>
struct MyIter
{
    typedef T value_type;  // value_type定义
    T* ptr;
    MyIter(T* p=0) : ptr(p) {}
    T& operator*() const { return *ptr; }
};
 
template<class I>
int    // typename用于指明I::value_type是个类型, 并且作为返回值类型
func(I ite)
{
    return *ite;
}
 
int main(int argc, char **argv)
{
    MyIter<int> ite(new int(8)); //定义了一个对象，模板参数是int, 对象中的ptr指针指向了数值8
    cout << func(ite) << endl; // 函数模板中的参数类型I是 MyIter , 函数返回值类型是MyIter::value_type, return *ite即使执行重载后的*返回值
    //使用萃取技术，那么函数可以针对任意返回类型都是允许的，
 
    return 0;
}
// 输出8