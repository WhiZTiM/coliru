template <class T>
class className
{
public:
    typedef struct structName
    {
        T* data;
        int moreData;
    } structName;

private:
    structName* specialPointer;

public:
    className();
    
    // Here is where I have no clue what I'm doing anymore
    typename T::node* get_specialPointer();
    
    
};

template <class T>
className<T>::className()
{
    specialPointer = 0;  // Null ptr, doesn't matter here.
}

template <class T>
typename T::node* className<T>::get_specialPointer()  // Still don't know what I'm doing
{
    return specialPointer;
}