#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

struct A {
    A() : a(0) {}
    A(int aa) : a(aa) {}
    int a;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& BOOST_SERIALIZATION_NVP(a);
    }
};

std::ostream& operator<<(std::ostream& os, const A& a) {
    os << "A{" << a.a << "}";
    return os;
}

template <typename T>
struct Ptr { // Ptr could use init constructor here but this is not the point
    Ptr()
    : m_elem(0)
    {}

    Ptr(const T* elem) {
        if (elem)
            m_elem = new T(*elem);
        else
            m_elem = 0;
    }
    Ptr(const T& elem)
    {
        m_elem = new T(elem);
	}
    
    // no copies
    Ptr(const Ptr&) = delete;
    Ptr& operator=(const Ptr&) = delete;

    // moves allowed
    Ptr(Ptr&& p)
    : m_elem(p.m_elem)
    {
        p.m_elem = 0;
    }
    Ptr& operator=(Ptr&& p)
    {
        Ptr tmp(std::move(p));
        std::swap(m_elem, tmp.m_elem);
        return *this;
    }

    // delete is a NOP when called with nullptr arg
    virtual ~Ptr() { delete m_elem; };

    T* get() const {
        return m_elem;
    }

    T& operator*() const {
        return *m_elem;
    }

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& BOOST_SERIALIZATION_NVP(m_elem);
    }

private:
    T* m_elem;
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Ptr<T>& p) {
    if (p.get()) {
        os << *p;
    }
    else {
        os << "{nullptr}";
    }
    return os;
}

int main()
{
    std::string payload;

    {
        Ptr<A> p;
        std::cout << p << std::endl;
        std::ostringstream oss;
        boost::archive::xml_oarchive oa(oss);
        oa << BOOST_SERIALIZATION_NVP(p);
        payload = oss.str();
        std::cout << payload << std::endl;

        p = Ptr<A>(A(6));
        std::cout << p << std::endl;
        oa << BOOST_SERIALIZATION_NVP(p);
        payload = oss.str();
        std::cout << payload << std::endl;
    }
    {

        Ptr<A> po;
        std::istringstream iss(payload);
        boost::archive::xml_iarchive ia(iss);
        ia >> BOOST_SERIALIZATION_NVP(po);
        std::cout << po << std::endl;

        ia >> BOOST_SERIALIZATION_NVP(po);
        std::cout << po << std::endl;
    }
    {
        Ptr<double> p(new double(2.0));

        std::ostringstream oss;
        boost::archive::xml_oarchive oa(oss);
        oa << BOOST_SERIALIZATION_NVP(p);
        std::cout << oss.str() << std::endl;
        
        //segfault
        Ptr<double> po;
        std::istringstream iss;
        iss.str(oss.str());
        boost::archive::xml_iarchive ia(iss);
        ia >> BOOST_SERIALIZATION_NVP(po);
    }
}