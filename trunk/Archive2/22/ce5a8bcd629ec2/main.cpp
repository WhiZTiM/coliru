#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>

template <typename T>
void printVector(T vec)
{   
    for(auto tmp : vec)
    {
        ++tmp;
    }
    for(auto tmp : vec)
    {
        std::cout<<tmp;
    }
}

void printReverseVector(std::vector<char> &vec)
{
    std::for_each(vec.crbegin(), vec.crend(), [] 
    (const char & symbol)
    {
        std::cout<<symbol;
    }
    );
}

void fillVector(std::vector<char> & vec)
{
    for (char i ='A'; i < ('Z'+1); ++i)
    {
        vec.push_back(i);
        vec.push_back(' ');
    }  
}

int main()
{
    size_t size = 'Z'-'A' + 1;
    std::vector<char> myVector;
    myVector.reserve(size);
    std::cout<<"Vector capacity:" << myVector.capacity()<<std::endl; // I know that it's not size;

    fillVector(myVector);
    std::cout<<myVector.capacity()<<std::endl;
    std::vector<char> myVec2(myVector);
    myVec2[1] = 'q';
    std::list<char> foo(10);
    foo.push_back('q');
    foo.push_back('z');
//    std::copy(myVector.cbegin(), myVector.cend(), (foo.begin())); 
    auto it = foo.begin();
    std::advance(it,5);
    std::generate(foo.begin(), it, [] { return 'a';});
    std::iter_swap(foo.begin(), --foo.end());
    std::replace(foo.begin(), it, 'a', 'q');
    std::swap_ranges(myVector.begin(), myVector.end(), foo.begin());
//    std::cout<<*foo.begin();
     printVector(foo);
     std::cout<<std::endl;
      printVector(myVector);
//    std::fill_n(std::front_inserter(myVec2), 5, 'Q');
//    std::cout<<std::equal(myVector.cbegin(), myVector.cend(), myVec2.cbegin());
//    auto it = std::adjacent_find(myVector.begin(), myVector.end());
//    myVector.insert(++it,'S');
//    std::cout<<std::count(myVector.cbegin(), myVector.cend(), ' ');

//    printVector(myVec2);
    std::cout<<std::endl;
//    printReverseVector(myVector);

//    printVector(myVector);
    return 0;
}

