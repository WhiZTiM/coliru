#include <iostream>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <vector>

#include <fstream>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;
using namespace boost;

class outer {
    friend class boost::serialization::access;

  public:
    int a;
    class inner {
        friend class boost::serialization::access;

      public:
        int a;
        inner(int a) { this->a = a; }
        template <class Archive> void serialize(Archive &ar, const unsigned int version) { ar &a; }
        inner() {}
    };
    vector<inner> inners;
    outer(int a = 0) : a(a), inners {a+1} { }

    template <class Archive> void serialize(Archive &ar, const unsigned int version) {
        ar &a;
        ar &inners;
    }
};


BOOST_CLASS_EXPORT(outer)

int main(int, char *[]) {
    {
        std::ofstream ofs("filename.dat");

        vector<outer> outers;
        for (int i = 0; i < 5; i++)
            outers.push_back(outer(i));

        {
            boost::archive::text_oarchive oa(ofs);
            oa << outers;
        }
    }

    {
        vector<outer> _outers;
        std::ifstream ifs("filename.dat");
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> _outers;

        for(auto& outer : _outers) {
            std::cout << "outer " << outer.a << "\n";

            for (auto& inner: outer.inners)
                std::cout << "   inner " << inner.a << "\n";
        }
    }
}
