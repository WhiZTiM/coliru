#include <iostream>
#include <algorithm>

using namespace std;


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
        Array = new Element[size]();
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

int size = 100; //for testing

class bigint
{
    SafeArray<int> arr;
public:
    bool sign;
    bigint()                                                   //initializes to zero
    {
        for (int i = 0; i < size; i++)
            arr.set(i, 0);
    }

    void print()                                               //prints numbers without zeroes in front
    {
        bool start_num = false;
        for (int i = 0; i <arr.get_size(); i++)
        {
            if (arr.get(i) != 0 && start_num == false)
            {
                start_num = true;
                cout << arr.get(i);
            }
            else if (start_num == true)
                cout << arr.get(i);

        }

        cout << endl;
    }

    void assign(const bigint &A)                         
    {
        for (int i = 0; i<arr.get_size(); i++)
            arr.set(i, A.arr.get(i));
    }

    void assign(string num)
    {
        long len = num.length();
        int j = arr.get_size() - 1;
        for (long i = len - 1; i >= 0; i--)
        {
            arr.set(j, num[i] - 48);
            j--;
        }
    }
    void add_pos(const bigint &A)                                //add big ints
    {
        int carry = 0;
        for (int i = size - 1; i >= 0; i--)
        {
            int result = arr.get(i) + A.arr.get(i) + carry;
            arr.set(i, result % 10);
            carry = result / 10;
        }
    }

    void sub_pos(const bigint &A)
    {
        int borrow = 0;
        for (int i = size - 1; i >= 0; i--)
        {
            int result = ((arr.get(i) - A.arr.get(i) - borrow));
            if (result<0)
            {
                arr.set(i, result + 10);
                borrow = 1;
            }
            else
            {
                arr.set(i, result);
                borrow = 0;
            }
        }
    }

    bool is_zero() const
    {
        for (int i = 0; i < size; ++i )
            if (arr.get(i) > 0)
                return false;
        return true;
    }

    void multiply(const bigint &A)
    {
        bigint tempInt(*this);
        bigint startVal(*this);
        bigint startA(A);
        bigint subtractor;
        subtractor.assign("1");
        startA.sub_pos(subtractor);
        while (!startA.is_zero()) 
        {
            startVal.add_pos(tempInt);
            startA.sub_pos(subtractor);
        } 
        *this = startVal;
    }
};

int main()
{
    bigint a, b;
    a.assign("1234");
    b.assign("1234");
    a.multiply(b);
    a.print();

    return 0;
}
