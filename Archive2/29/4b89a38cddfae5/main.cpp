#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/serialize_ptr_vector.hpp>

using namespace boost;

// Allow serialization of `reference_wrapper`
namespace boost { namespace serialization {
    template<class Ar, class T> void save_construct_data(Ar & ar, std::reference_wrapper<T> const * t, unsigned) {
        T const * p = &t->get();
        ar << p;
    }
    template<class Ar, class T> void load_construct_data(Ar & ar, std::reference_wrapper<T> * t, unsigned) {
        T* p = nullptr;
        ar >> p;
        std::reference_wrapper<T> rw(*p);
        ::new(t) std::reference_wrapper<T>(rw);
    }

    template <class Ar, typename T> inline void serialize(Ar &, std::reference_wrapper<T>&, unsigned) { }
} }

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
    std::vector<std::reference_wrapper<B> > refvect;

    void fill_sample() {
        storage.push_back(new D1);
        storage.push_back(new D1);
        storage.push_back(new D2);
        storage.push_back(new D1);

        refvect.assign(storage.rbegin(), storage.rend());
    }

    friend std::ostream& operator<<(std::ostream& os, Data const& data) {
        for (B const& i : data.refvect) i.print(std::cout) << "\n";
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
#if 0 // doesn't work due to reference_wrapper not default constructible
    {
        archive::binary_iarchive ia(stream);

        Data y;
        ia >> y;
        std::cout << "After:\n" << y << "\n";
    }
#endif
}
