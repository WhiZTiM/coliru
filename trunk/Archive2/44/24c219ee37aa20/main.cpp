#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/access.hpp>

// As best as I can tell, the following is legal per the spec.   However,
// being able to do something does not mean one should.  Remember, as
// Stan Lee would say, with great power comes great responsibility.

/// @brief Mocked up legacy type that cannot be modified.
template <typename T>
class A
{
public:
  A(const T &id) : m_id(id) {}
private:
  T m_id;
};

namespace privates {

// Use a Key class to provide pointer-to-member types, since there is no way to
// deduce the type or obtain the type in a standard compliant manner due to
// visibility.
template <typename Key,
          typename Key::type PointerToMember>
struct store
{
  // Inline friend defintion.  Two critical concepts:
  // - friend explicitly indicates that this get method is not a member of the
  //   class, but instead, it is a free function with scope of the class'
  //   containing namespace.  I.e. store.get(Key()) does not exists, but
  //   store::get(Key()) does.
  // - The defintion needs both the the type and non-type value, so it is
  //   inlined, as the friend function itself is not a template.
  friend typename Key::type get(Key)
  {
    return PointerToMember;
  }
};

// Must declare Key types in same namespace.

/// @brief Key for A<int>::m_id
struct A_int_m_id
{
  typedef int A<int>::*type;

  // Set the store's get method as a friend to supprt ADL with this tag.  This
  // declration allows invoking the inline friend store::get() function with just
  // this tag:  get(A_int_m_id()).
  friend type get(A_int_m_id);
};

// Per spec, it is legal to pass the address of private pointer-to-member as
// a non-typed template parameter in explicit template instantiation.  Use
// this rule to Associate the key with the pointer-to-member.  The key can
// then be used during ADL to indirectly get the pointer-to-member value.
template struct store<A_int_m_id, &A<int>::m_id>;

} // namespace privates

// Auxilliary function get get the m_id prviate variable on instance.
int& get_id(A<int>& instance)
{
  // Resolves to the get() function defined by store<A_int_m_id>, returning
  // a pointer to m_id.
  return instance.*(get(privates::A_int_m_id()));
}

namespace boost {
namespace serialization {

template <class Archive, typename T>
void serialize(Archive &ar, A<T> &a, const unsigned int)
{
  ar & boost::serialization::make_nvp("m_id", get_id(a));
}

} // namespace serialization
} // namespace boost

int main()
{
  A<int> a(42);
  boost::archive::xml_oarchive oa(std::cout);
  oa << BOOST_SERIALIZATION_NVP(a);
}
