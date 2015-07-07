#ifndef __Test_HEADER__
#define __Test_HEADER__

#include <list>
#include <vector>
#include <iostream>
#include <initializer_list>

namespace walid
{
    template<typename T>
    class Test
    {
        public:
            std::vector<T> elements;
            int in_dim;

            Test(int input_dim, std::initializer_list<T> elem) {
                in_dim = input_dim;
                elements = std::vector<T>(elem);
            }

            void start(){};
            void stop(){};
    };
}

//#include "Test_serialization.inl"
namespace boost {
namespace serialization {

    template<class Archive, class T>
        inline void serialize(Archive & /*ar*/, walid::Test<T>& /*t*/, const unsigned int /*version*/)
        {
            std::cout << "serialize Test ..." << std::endl;
        }

    template<class Archive, class T>
        inline void save_construct_data (Archive & /*ar*/, const walid::Test<T>* /*t*/, const unsigned int /*version*/)
        {
            std::cout << "call save_construct_data Test ..." << std::endl;

    }

    template<class Archive, class T>
        inline void load_construct_data (Archive & /*ar*/, walid::Test<T>* t, const unsigned int /*version*/)
        {
            std::cout << "call load_construct_data Test ..." << std::endl;
            ::new (t) walid::Test<T> (2, {2.3f, -0.5f}) ;
        }
}
}

#endif

#include <vector>
#include <iostream>
//#include "Test.h"

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/serialization.hpp>

#include <boost/shared_ptr.hpp>

int main()
{
    using T = float;
    using Test = walid::Test<T>;

    {
        boost::shared_ptr<Test> shared_instance(new Test(2, {2.3f, -0.5f}));

        std::ofstream ofs("data");
        boost::archive::text_oarchive oa(ofs);
        oa << shared_instance;
    }

    {
        boost::shared_ptr<Test> deserialized;

        std::ifstream ifs("data");
        boost::archive::text_iarchive ia(ifs);
        ia >> deserialized;
    }
}
