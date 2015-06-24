template<class T, class U>
void construct(T* destination, U&& source)
{
    ::new ((void*)destination) T(static_cast<U&&>(source));
}

template<class T>
void destruct(T* p)
{
    p->~T();
}

template<class FwdIt>
void recursive_destruct(FwdIt first, FwdIt last)
{
    if (first == last)
        return;
        
    auto curr = first;
    recursive_destruct(++first, last);
    destruct(&*curr);
}

template<class InIt, class FwdIt>
FwdIt uninitialized_copy(InIt first, InIt last, FwdIt out)
{
    auto hold = out;
    try
    {
        for (; first != last; ++first, ++out)
            construct(&*out, *first);
    }
    catch (...)
    {
        recursive_destruct(hold, out);
        throw;
    }
}

int main()
{
}