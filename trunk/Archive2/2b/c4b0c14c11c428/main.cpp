#include <iostream>

template <typename T>
class MoveNextCollection
{
    // Forward declaration
    class ConstIterator;

public:
    // Usual C++ collection typedefs
    typedef T value_type;
    typedef const value_type& const_reference;
    typedef ConstIterator const_iterator;

    const_iterator begin() const
    {
        if (MoveToStart(&_CurrentValue))
        {
            return const_iterator(this);
        }
        else
        {
            return end();
        }
    }

    const_iterator end() const
    {
        return const_iterator();
    }

    virtual ~MoveNextCollection()
    {
    }

private:

    class ConstIterator
    {
    public:
        ConstIterator(const MoveNextCollection *pMoveNextCollection = nullptr)
            : _pMoveNextCollection(pMoveNextCollection)
        {
        }

        const_reference operator*() const
        {
            return _pMoveNextCollection->GetCurrentValue();
        }

        bool operator==(const ConstIterator &iter) const
        {
            return (_pMoveNextCollection == iter._pMoveNextCollection);
        }

        bool operator!=(const ConstIterator &iter) const
        {
            return !operator==(iter);
        }

        ConstIterator &operator++()
        {
            if (!_pMoveNextCollection->MoveToNext())
            {
                _pMoveNextCollection = nullptr;
            }

            return (*this);
        }

    private:
        const MoveNextCollection *_pMoveNextCollection;
    };

    const_reference GetCurrentValue() const
    {
        return _CurrentValue;
    }

    bool MoveToNext() const
    {
        return MoveToNext(&_CurrentValue);
    }

private:
    virtual bool MoveToStart(value_type *) const = 0;
    virtual bool MoveToNext(value_type *) const = 0;

    mutable value_type _CurrentValue;
};

class Test
{
public:

    class Collection : public MoveNextCollection<int>
    {
    private:
        bool MoveToStart(int *pValue) const override
        {
            *pValue = 314; // Whatever
            return true;
        }

        bool MoveToNext(int *) const override
        {
            return false;
        }
    };

    const Collection& GetCollection() const
    {
        return _collection;
    }

private:
    Collection _collection;
};

int main()
{
    for (int val : Test().GetCollection())
    {
        std::cout << val << "\n";
    }
    
    return 0;
}
