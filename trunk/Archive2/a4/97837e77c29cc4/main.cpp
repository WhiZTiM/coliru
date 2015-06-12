#include <algorithm>
#include <boost/operators.hpp>
#include <ostream>

template <typename T = double, int _Min = 0, int _Max = 1>
class clamped_value : 
      boost::ordered_euclidian_ring_operators<clamped_value<T,_Min,_Max>
    , boost::unit_steppable<clamped_value<T,_Min,_Max>
    , boost::equivalent<clamped_value<T,_Min,_Max>
    , boost::ordered_euclidian_ring_operators<clamped_value<T,_Min,_Max>, T
    , boost::equivalent<clamped_value<T,_Min,_Max>, T
    > > > > >
{
  public:
    constexpr clamped_value() = default;
    explicit constexpr clamped_value(T x) : x(clamped(x)) {}
    explicit operator T() const { return x; }

    clamped_value& operator=(clamped_value const& rhs) = default;
    clamped_value& operator=(T rhs) { return (*this) = clamped_value{rhs}; }

    clamped_value& operator+= (T rhs) { return (*this) += clamped_value{rhs}; } 
    clamped_value& operator-= (T rhs) { return (*this) -= clamped_value{rhs}; } 
    clamped_value& operator*= (T rhs) { return (*this) *= clamped_value{rhs}; } 
    clamped_value& operator/= (T rhs) { return (*this) /= clamped_value{rhs}; } 

  private:
    clamped_value& operator+= (clamped_value rhs) { x = clamped(x + rhs.x); return *this; } 
    clamped_value& operator-= (clamped_value rhs) { x = clamped(x - rhs.x); return *this; } 
    clamped_value& operator*= (clamped_value rhs) { x = clamped(x * rhs.x); return *this; } 
    clamped_value& operator/= (clamped_value rhs) { x = clamped(x / rhs.x); return *this; } 

    static constexpr T clamped(T v) { 
        return std::min(std::max(v, static_cast<T>(_Min)), static_cast<T>(_Max));
    }
    T x;
};

#include <boost/type_traits.hpp>
static_assert(boost::is_pod<clamped_value<> >::value,            "should not hurt performance");
static_assert(boost::is_pod<clamped_value<int, -3, 30> >::value, "should not hurt performance");
static_assert(boost::is_pod<clamped_value<float> >::value,       "should not hurt performance");

#include <boost/multiprecision/cpp_dec_float.hpp>
static_assert(not boost::is_pod<clamped_value<boost::multiprecision::cpp_dec_float_100> >::value, "non-pod T is also OK, of course");

#include <map>
#include <random>
#include <iostream>
#include <iomanip>

using Float = boost::multiprecision::cpp_dec_float_100;

int main() {
    using namespace std;
    mt19937 rng { random_device{}() };
    auto key   = std::bind(uniform_int_distribution<size_t>(0, 100), rng);
    auto value = std::bind(uniform_real_distribution<double>(-3, 3), rng);

    map<size_t, clamped_value<Float> > fuzzy;
    for (auto i = 0; i < 10000; ++i)
        switch(i%3) {
            case 0: fuzzy[key()] += value(); break;
            case 1: fuzzy[key()] -= value(); break;
            case 2: fuzzy[key()] *= value(); break;
        }

    for(auto& e : fuzzy)
        cout << e.first << " " << right << setprecision(2) << setw(8) << fixed << 100*static_cast<Float>(e.second) << "%\n";
}
