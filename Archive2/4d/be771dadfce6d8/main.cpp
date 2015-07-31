#include <iostream>
#include <type_traits>

using namespace std;

template <typename T> class remove_all_pointers{
public:
    typedef T type;
};

template <typename T> class remove_all_pointers<T*>{
public:
    typedef typename remove_all_pointers<T>::type type;
};

template <typename T> class remove_all_pointers<T* const>{
public:
    typedef typename remove_all_pointers<T>::type type;
};

template <typename T> class remove_all_pointers<T* volatile>{
public:
    typedef typename remove_all_pointers<T>::type type;
};

template <typename T> class remove_all_pointers<T* const volatile >{
public:
    typedef typename remove_all_pointers<T>::type type;
};


class OverVoid{
public:

    static bool isOverVoid (){
    return true;
    }
    virtual ~OverVoid(){
    }
};

class Meta: public OverVoid{

};

class Physical{
public:

};

template<typename T, typename = typename std::enable_if<std::is_base_of<OverVoid, typename remove_all_pointers<T>::type>::value>::type>
class Move{
public:
    Move()
    {
        cout<<"### "<<remove_all_pointers<T>::type::isOverVoid()<<endl;
    }
};

/*
template<typename T,typename = typename std::enable_if<std::is_base_of<OverVoid, typename remove_all_pointers<T>::type>::value>::type>
class Move{
public:
    Move()
    {
        cout<<"### "<<remove_all_pointers<T>::type::isOverVoid()<<endl;
    }
};

template<typename T, typename = typename std::enable_if<std::is_base_of<OverVoid, typename remove_all_pointers<T>::type>::value>::type>
class Move{
public:
    Move()
    {
        cout<<"### "<<remove_all_pointers<T>::type::isOverVoid()<<endl;
    }
};
*/

int main(){

    Move<Meta***> z;
    Move<Meta**> w;
    Move<Meta*> x;
    Move<Meta> y;

}