#ifndef VECTOR_H
#include<cstdlib>
#include<vector>
#include<iostream>
template < typename T>
class MyClass
{
public:
    MyClass() : size(10), index(0) { vec = new T[10] };
    MyClass(int i) : size(i), index(0) { vec = new T[i] };
    friend bool add(T i);
    virtual ~MyClass();
    friend ostream& operator<<(ostream& out, const T& obj); //HERE

private:
    T * vec;
    int size;
    int index;
};
template <typename T>
virtual MyClass::~MyClass()
{
    delete[] vec;
}
template <typename T>
osteam& operator<<(operator& out, const MyClass& obj){
    for (int i = 0; i < index; ++i)
        out << obj[i] << " ";
    out << endl;
}
template <typename T>
virtual bool MyClass::add(T i){
    if (size == index){
        size *= 2;
        realloc(vec, size);
    }

    vec[index++] = i;

}
#endif // !VECTOR_H