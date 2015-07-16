#include <iostream>
#include <list>
#include <memory>
#include <string>

#ifdef __GNUG__
#include <cxxabi.h>
#endif

class Type
{
public:
    virtual std::string name() const =0;
    virtual std::size_t size() const =0;
    
    virtual bool operator==(const Type& type)
    {
        return name() == type.name() && size() == type.size();   
    }
    
    virtual bool operator!=(const Type& type)
    {
        return name() != type.name() || size() != type.size();   
    }
};

template <typename T>
class AnyType: public Type
{
    T value;
    
public:
    AnyType() {}
    AnyType(T value): value(value) {}
    
    virtual std::string name() const
    {
#if defined(__GXX_RTTI) || defined(_CPPRTTI)
        static std::string n;

        if (n.empty())
        {
            n = typeid(T).name();

#ifdef __GNUG__
            char * name = 0;
            int status;
            
            name = abi::__cxa_demangle(n.c_str(), 0, 0, &status);
            if (name != 0) {
                n = name;
            }
#elif _MSC_VER
            int pos = sname.find(" ");
    		if (pos > 0)
				sname = sname.substr(pos+1);
#endif
        }
        
        return n;
#else
        return std::string();
#endif
    }
    
    virtual std::size_t size() const
    {
        return sizeof(T);
    }
    
    virtual T operator=(const T& val)
    {
        return value = val;
    }
    
    virtual operator T()
    {
        return value;
    }
};

#define ANYTYPE_ENABLE(T) \
template <> \
class AnyType<T>: public Type \
{ \
    T value; \
    \
public: \
    AnyType() {} \
    AnyType(T value): value(value) {} \
    \
    virtual std::string name() const \
    { \
        static const std::string n(#T); \
        return n; \
    } \
    \
    virtual std::size_t size() const \
    { \
        return sizeof(T); \
    } \
    \
    virtual T operator=(const T& val) \
    { \
        return value = val; \
    } \
    \
    virtual operator T() \
    { \
        return value; \
    } \
};

ANYTYPE_ENABLE(char);
ANYTYPE_ENABLE(int);
ANYTYPE_ENABLE(float);
ANYTYPE_ENABLE(double);

class Value
{
public:
    Value(): valueType(nullptr) {}
    
	Type& type()
    {
        return *valueType;   
    }
	
	template <typename T>
	Value (T data):
        valueType(new AnyType<T>(data))
	{
	}
	
	template <typename T>
	T operator=(const T& value)
	{
        if (valueType == nullptr)
        {
            valueType = new AnyType<T>(value);
            return value;
        }
            
		if (*valueType != AnyType<T>())
            throw std::string("Invalid type");
            
        return *static_cast<AnyType<T>*>(valueType) = value;
	}
    
    template <typename T>
    operator T()
    {
        if (valueType == nullptr)
            throw std::string("Value have any type");
        
        if (*valueType != AnyType<T>())
            throw std::string("Tipo invalido!");
            
        return *static_cast<AnyType<T>*>(valueType);      
    }
    
private:
    Type* valueType;
};

int main()
{
    Value val(10);
    
    std::cout << (int)val << std::endl;
    
    return 0;
}