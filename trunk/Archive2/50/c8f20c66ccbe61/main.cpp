
#include <vector>




template<typename T>
class base
{

protected:

    base() {}

    virtual ~base() {}

protected:

    virtual void method(void* const voidp) const = 0;

};

template<typename T>
class child : public base<T> // ERROR: child is not a template type
{

public:

    child(std::vector<T> arg)
        : _arg{arg}
    {
    }

    virtual ~child() {}

public:

    void method(void* const voidp) const
    {
       for( std::vector<T>::iterator it = _arg.begin(); it != _arg.end(); ++ it)
        {
           // method(voidp, *it);
        }
    }

protected:

    std::vector<T> _arg;

};

int main()
{
    std::vector<int> X;
   child<int>  c(X) ;
}
