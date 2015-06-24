#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

struct A {
    boost::dynamic_bitset<> x;
  private:
    friend class boost::serialization::access;
    template <class Archive> void serialize(Archive &ar, const unsigned int) { 
        ar &x; 
    }
};

namespace boost { namespace serialization {

    template <typename Ar, typename Block, typename Alloc>
        void save(Ar& ar, dynamic_bitset<Block, Alloc> const& bs, unsigned) {
            size_t num_bits = bs.size();
            std::vector<Block> blocks(bs.num_blocks());
            to_block_range(bs, blocks.begin());

            ar & num_bits & blocks;
        }

    template <typename Ar, typename Block, typename Alloc>
        void load(Ar& ar, dynamic_bitset<Block, Alloc>& bs, unsigned) {
            size_t num_bits;
            std::vector<Block> blocks;
            ar & num_bits & blocks;

            bs.resize(num_bits);
            from_block_range(blocks.begin(), blocks.end(), bs);
            bs.resize(num_bits);
        }

    template <typename Ar, typename Block, typename Alloc>
        void serialize(Ar& ar, dynamic_bitset<Block, Alloc>& bs, unsigned version) {
            split_free(ar, bs, version);
        }

} }

int main() {
    A a;
    for (int i=0; i<128; ++i)
        a.x.resize(11*i, i%2);

    std::stringstream ss;
    {
        boost::archive::text_oarchive oa(ss);
        oa << a;
    }
    std::cout << ss.str();
    {
        boost::archive::text_iarchive ia(ss);
        A b;
        ia >> b;

        assert(a.x == b.x);
    }
}
