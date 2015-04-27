#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <iostream>

#include <boost/random.hpp> // for test
#include <boost/range/empty.hpp>
#include <boost/range/iterator_range.hpp>

template <typename>
class Obj
{
  private:
    int value1;
    int value2;
    boost::tuple<int const&, int const&> key() const { return boost::tie(value1, value2); }
  public:
    int get_value1() const { return this->value1;}
    int get_value2() const { return this->value2;}
    Obj(int value1, int value2): value1(value1), value2(value2) {};

    struct Hash {
        size_t operator()(const Obj& a) const {
            size_t seed = 0;
            boost::hash_combine(seed, a.get_value1());
            boost::hash_combine(seed, a.get_value2());
            return seed;
        }
    };

    struct Equality {
        bool operator()(const Obj& lhs, const Obj& rhs) const {
            return lhs.key() == rhs.key(); 
        }
    };
};

typedef Obj<struct TagA> A;
typedef Obj<struct TagB> B;

int myrandom() {
    static boost::mt19937 prng(42);
    static boost::uniform_int<> dist(0, 1000);
    return dist(prng);
}

int main() {

    typedef boost::bimaps::bimap< 
            boost::bimaps::unordered_set_of<A, A::Hash, A::Equality>,
            boost::bimaps::unordered_set_of<B, B::Hash, B::Equality> 
        > CustomMap;

    CustomMap map;

    int dupes = 0;
    for (int i=0; i < 10000; ++i)
    {
        A a(myrandom(), myrandom());
        B b(myrandom(), myrandom());

        if (!map.insert(CustomMap::value_type(a, b)).second)
            ++dupes;
    }

    std::cout << dupes << " duplicate insertions were skipped\n";

    int left_hits = 0;
    for (int i=0; i <= 10000; ++i)
        if (!boost::empty(boost::make_iterator_range(map.left.equal_range(A(i,i)))))
            ++left_hits;

    int right_hits = 0;
    for (int i=0; i <= 10000; ++i)
        if (!boost::empty(boost::make_iterator_range(map.right.equal_range(B(i,i)))))
            ++right_hits;

    std::cout << "Random hits (left, right): (" << left_hits << ", " << right_hits << ")\n";
}
