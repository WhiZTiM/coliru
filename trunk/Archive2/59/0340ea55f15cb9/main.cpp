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
        if (MoveToStart(&m_CurrentValue))
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
        ConstIterator(const MoveNextCollection *pColl = nullptr)
            : m_pColl(pColl)
        {
        }

        const_reference operator*() const
        {
            return m_pColl->GetCurrentValue();
        }

        bool operator==(const ConstIterator &iter) const
        {
            return (m_pColl == iter.m_pColl);
        }

        bool operator!=(const ConstIterator &iter) const
        {
            return !operator==(iter);
        }

        ConstIterator &operator++()
        {
            if (!m_pColl->MoveToNext())
            {
                m_pColl = 0;
            }

            return (*this);
        }

    private:
        const MoveNextCollection *m_pColl;
    };

    const_reference GetCurrentValue() const
    {
        return m_CurrentValue;
    }

    bool MoveToNext() const
    {
        return MoveToNext(&m_CurrentValue);
    }

private:
    virtual bool MoveToStart(value_type *) const = 0;
    virtual bool MoveToNext(value_type *) const = 0;

    mutable value_type m_CurrentValue;
};

class Test
{
public:
    Test() : _collection(this)
    {
    }

    class Collection : public MoveNextCollection<int>
    {
    private:
        friend class Test;

        Collection(const Test *pTest)
            : _pTest(pTest)
        {
        }

        bool MoveToStart(int *pValue) const override
        {
            *pValue = 2;
            return true;
        }

        bool MoveToNext(int *) const override
        {
            return false;
        }

    private:
        const Test *_pTest;
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
        std::cout << val;
    }
}
