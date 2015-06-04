#include <tuple>
#include <iostream>  
#include <ostream>
using namespace std;

template<class Type>
struct haveChildren
{   
    const std::tuple<int, Type> myChildren;

    template<typename... Args>
    haveChildren(Args&&... args) : myChildren(5, Type{std::forward<Args>(args)...}) {}

    friend ostream& operator<< (ostream& streamReceiver, const haveChildren<Type>& streamSender)
    {
        int myInt;  int myChar;
        std::tie(myInt, myChar) =   std::get<1>(streamSender.myChildren);

        return streamReceiver << "My int is " << myInt << " my char is " << ((char)myChar);
    }
};

struct haveChildrenCharAndInt : public haveChildren<std::tuple<int, char>>
{
    haveChildrenCharAndInt() : haveChildren(10,'x') {}
};

int main()
{
    cout << haveChildrenCharAndInt();
    return 0;
}
