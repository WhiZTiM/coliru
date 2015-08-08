#include <cmath>
#include <limits>

template <typename T>
class Pascal
{
private:
    T val;

public:
    explicit Pascal(const T val_)
    {
        val = val_;
    }

    operator T() const
    {
        return val;
    }
};

template <typename T>
class dbSPL {
private:
    T val;

public:
    explicit dbSPL(const Pascal<T> p)
    {
        auto infProtect = std::numeric_limits<T>::min();
        val = 20.0 * std::log10( infProtect + p / 20e-6 );
    }
    
    operator T() const
    {
        return val;
    }
};

template <typename T>
dbSPL<T> make_dbspl(T t)
{
    return dbSPL<T>(Pascal<T>(t));
}

int main()
{
    auto dbspl = make_dbspl(0.5);
    
    (void)dbspl;
}
