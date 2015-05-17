#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/serialize_ptr_vector.hpp>
#include <functional>

using namespace boost;

/////////////////////////////////////////////////
// defining a virtual class hierarchy...
struct B {
    virtual ~B() = default;
    virtual std::ostream& print(std::ostream& os) const { return os << __PRETTY_FUNCTION__; }

  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar&, unsigned) const {
    }
};

struct D1 : B {
    virtual std::ostream& print(std::ostream& os) const { return os << __PRETTY_FUNCTION__; }

  private:
    std::string _data = "forty two";

    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned) {
        ar & boost::serialization::base_object<B>(*this);
        ar & _data;
    }
};

struct D2 : B {
    virtual std::ostream& print(std::ostream& os) const { return os << __PRETTY_FUNCTION__; }

  private:
    int _data = 42;

    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned) {
        ar & boost::serialization::base_object<B>(*this);
        ar & _data;
    }
};

BOOST_CLASS_EXPORT(B)
BOOST_CLASS_EXPORT(D1)
BOOST_CLASS_EXPORT(D2)

/////////////////////////////////////////////////
// sample data structure representing our program

struct Data {
    ptr_vector<B> storage;
    std::vector<B*> refvect;

    void fill_sample() {
        storage.push_back(new D1);
        storage.push_back(new D1);
        storage.push_back(new D2);
        storage.push_back(new D1);

        refvect.clear();
        for (auto it = storage.rbegin(); it != storage.rend(); ++it)
            refvect.push_back(&*it);
    }

    friend std::ostream& operator<<(std::ostream& os, Data const& data) {
        for (auto i : data.refvect) i->print(std::cout) << "\n";
        return os;
    }

    template <typename Ar> void serialize(Ar& ar, unsigned) {
        ar & storage & refvect;
    }
};

#include <sstream>
int main() {

    std::stringstream stream;
    {
        archive::binary_oarchive oa(stream);

        Data x;
        x.fill_sample();
        oa << x;

        std::cout << "Before:\n" << x << "\n";
    }

    {
        archive::binary_iarchive ia(stream);

        Data y;
        ia >> y;
        std::cout << "After:\n" << y << "\n";
    }

}
