#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <fstream>

class outer {
    friend class boost::serialization::access;

  public:
    int a;
    class inner {
        friend class boost::serialization::access;

      public:
        int a;
        inner(int a) { this->a = a; }
        template <class Archive> void serialize(Archive &ar, unsigned) { ar &a; }
        inner() {}
    };
    std::vector<inner> inners;
    outer(int a = 0) : a(a), inners {a+1} { }

    template <class Archive> void serialize(Archive &ar, unsigned) {
        ar &a;
        ar &inners;
    }
};


BOOST_CLASS_EXPORT(outer)

int main(int, char *[]) {
    {
        std::ofstream ofs("filename.dat");

        std::vector<outer> outers(5);
        std::iota(outers.begin(), outers.end(), 0u);

        {
            boost::archive::text_oarchive oa(ofs);
            oa << outers;
        }
    }

    {
        // read class state from archive
        std::vector<outer> _outers;
        std::ifstream ifs("filename.dat");
        boost::archive::text_iarchive ia(ifs);
        ia >> _outers;

        for(auto& outer : _outers) {
            std::cout << "outer " << outer.a << "\n";

            for (auto& inner: outer.inners)
                std::cout << "   inner " << inner.a << "\n";
        }
    }
}
