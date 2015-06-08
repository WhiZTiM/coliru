#include <string>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/tags/tagged.hpp>

typedef double Address;

namespace bm = boost::bimaps;

template <class T>
class Test {
    private:
        struct key_idx;
        struct value_idx;
        typedef bm::bimap<
            bm::unordered_set_of<bm::tagged<T,       struct key_idx> >,
            bm::set_of          <bm::tagged<Address, struct value_idx> >
                > BidirectionalMap;

        typedef typename BidirectionalMap::value_type Record;

        BidirectionalMap _theBimap;

    public:
        void aFunction(const Address &anAddress, T const& parameters)
        {
            auto newRecord = _theBimap.insert(Record("TheGivenAdddress", anAddress));
            auto byNumber  = _theBimap.template by<value_idx>().find(anAddress);
            auto byAddress = _theBimap.template by<key_idx>().find(parameters);

            (void) newRecord, (void) byAddress, (void) byNumber;
        }
};

int main() {
    Test<std::string> t;
    t.aFunction(3.14, "hello");
}
