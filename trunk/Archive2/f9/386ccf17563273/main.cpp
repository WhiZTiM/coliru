#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>

#ifdef __GNUG__
#include <cxxabi.h>
#endif

class Type
{
public:
    virtual std::string name() const =0;
    virtual std::size_t size() const =0;
    virtual std::string toString() const =0;
    
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
    
    virtual std::string toString() const
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
    
    virtual T operator=(T val)
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
    virtual std::string toString() const \
    { \
        std::ostringstream oss; \
        oss << value; \
        return oss.str(); \
    } \
    virtual T operator=(T val) \
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
ANYTYPE_ENABLE(char*);
ANYTYPE_ENABLE(const char*);
ANYTYPE_ENABLE(std::string);
ANYTYPE_ENABLE(int);
ANYTYPE_ENABLE(float);
ANYTYPE_ENABLE(double);

class Value
{
public:
    Value() {}
    
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
        if (valueType.get() == nullptr)
        {
            valueType = new AnyType<T>(value);
            return value;
        }
            
		if (*valueType != AnyType<T>())
            throw std::string("Invalid type");
            
        return *static_cast<AnyType<T>*>(valueType.get()) = value;
	}
    
    template <typename T>
    operator T()
    {
        if (valueType.get() == nullptr)
            throw std::string("Value have any type");
        
        if (*valueType != AnyType<T>())
            throw std::string("Tipo invalido!");
            
        return *static_cast<AnyType<T>*>(valueType.get());      
    }
    
    std::string toString()
    {
        return valueType->toString();
    }
    
private:
    std::shared_ptr<Type> valueType;
};

struct Arguments {

    template<class... Args>
    Arguments(Args&&... tail)
    {
        Build(tail...);
    }
    
    virtual ~Arguments() {}
    
    template<class T, class... Args>
    void Build(T head, Args&&... tail) 
    { 
        contents.push_back(head); 
        Build(tail...);
    }

    template<class T>
    void Build(T head)
    { 
        contents.push_back(head); 
    }

    void Build() {}

    typedef std::vector<Value>::iterator iterator;
    typedef std::vector<Value>::const_iterator const_iterator;
    typedef std::vector<Value>::reverse_iterator reverse_iterator;
    typedef std::vector<Value>::const_reverse_iterator const_reverse_iterator;
    
    iterator begin()
    {
       return contents.begin();
    }
    
    iterator end()
    {
       return contents.end(); 
    }
    
    const_iterator begin() const
    {
       return contents.begin();
    }
    
    const_iterator end() const
    {
        return contents.end();
    }
    
    reverse_iterator rbegin()
    {
       return contents.rbegin();
    }
    
    reverse_iterator rend()
    {
        return contents.rend();
    }
    
    const_reverse_iterator rbegin() const
    {
       return contents.rbegin();
    }
    
    const_reverse_iterator rend() const
    {
        return contents.rend();
    }
    
    const_iterator cbegin() const
    {
       return contents.cbegin();
    }
    
    const_iterator cend() const
    {
        return contents.cend();
    }
    
    const_reverse_iterator crbegin() const
    {
       return contents.crbegin();
    }
    
    const_reverse_iterator crend() const
    {
        return contents.crend();
    }
    
    Value& operator[](int index)
    {
        return contents[index];
    }

private:
    std::vector<Value> contents;
};

int main()
{
    Arguments args(10, 20, 'a', 2.2, "Testando 123");
    
    for (Arguments::iterator it = args.begin(); it != args.end(); it++)
    {
        std::cout << it->type().name() << " " << it->toString() << std::endl;
    }

    return 0;
}
