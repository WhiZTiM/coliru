#include <algorithm>

template<typename Element>
class SafeArray
{
    int size;
    Element*Array;
    Element def;

public:
    SafeArray()                         //default constructor(with no parameter)
    {
        size = 10;
        Array = new Element[size];
    }

    SafeArray(int value)         //constructor with one int
    {
        size = value;
        Array = new Element[value];
        for (int i = 0; i < size; ++i)
            Array[i] = 0;
    }

    ~SafeArray() {
        delete[] Array;
    }                                       //destructor

    SafeArray(const SafeArray& rhs) : size(rhs.size), Array(new Element[size]), def(rhs.def)
    {
        for (int i = 0; i < size; ++i )
            Array[i] = rhs.Array[i];
    }

    SafeArray& operator=(SafeArray rhs)
    {
        std::swap(Array, rhs.Array);
        std::swap(size, rhs.size);
        std::swap(def, rhs.def);
        return *this;
    }

    Element get(int pos)    const                 //get method
    {
        if (pos<0)
        {
            cout << "error";
        }

        return Array[pos];
    }

    void set(int pos, Element val)
    {
        if (pos<0)
        {
            cout << "error";
            return;
        }
        if (pos >= size)
        {
            resize(pos + 1);
        }
        Array[pos] = val;
    }
    
    void resize(int new_size)
    {
        Element*temp = new Element[new_size];
        for (int i = 0; i<size; i++)
        {
            temp[i] = Array[i];
        }
        delete[]Array;
        Array = temp;
        size = new_size;
    }
    
    void set_default(Element d)        //set_default
    {
        def = d;
    }
    
    int get_size()                       //get size
    {
        return size;
    }
};
