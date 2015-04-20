#include <boost/flyweight/flyweight.hpp>
#include <boost/flyweight/no_locking.hpp>
#include <boost/flyweight/refcounted.hpp>
#include <boost/flyweight/factory_tag.hpp>
#include <boost/flyweight/static_holder.hpp>
#include <utility>

using namespace boost::flyweights;

template<typename Entry,typename Key>
struct ValueRefFactory
{
  using handle_type=Entry*;
  
  template <typename E>
  handle_type insert(E&& x){return new Entry{std::forward<E>(x)};}
  void erase(handle_type h){delete h;}
  const Entry& entry(handle_type h){return *h;}
};

template<typename T>
using ValueRefImpl=flyweight<
  T,no_locking,
  factory<ValueRefFactory<boost::mpl::_1,boost::mpl::_2>>>;
  
template<typename T>
struct ValueRef:ValueRefImpl<T>
{
  using impl_type=ValueRefImpl<T>;
  const impl_type& impl()const{return *this;}
  using impl_type::impl_type;
  ValueRef(const ValueRef&x):impl_type(x.impl()){}
  ValueRef(ValueRef&x):impl_type(x.impl()){}
  ValueRef(const ValueRef&&x):impl_type(x.impl()){}
  ValueRef(ValueRef&&x):impl_type(x.impl()){}
  using impl_type::operator=;
  const T& operator*()const{return this->get();}
  const T* operator->()const{return &this->get();}
  bool identity(const ValueRef& x)const{return &**this==&*x;}
};

template<typename T,typename Q>
bool operator==(const ValueRef<T>& x,const Q& y){return *x==y;}
template<typename T,typename Q>
bool operator==(const T& x,const ValueRef<Q>& y){return x==*y;}
template<typename T,typename Q>
bool operator==(const ValueRef<T>& x,const ValueRef<Q>& y){return *x==*y;}
  
template<typename T,typename Q>
bool operator!=(const ValueRef<T>& x,const Q& y){return !(x==y);}
template<typename T,typename Q>
bool operator!=(const T& x,const ValueRef<Q>& y){return !(x==y);}
template<typename T,typename Q>
bool operator!=(const ValueRef<T>& x,const ValueRef<Q>& y){return !(x==y);}

#include <vector>
#include <cassert>

int main()
{
  /* type of ValueRef wrapped std::vector<int> */
  typedef ValueRef<std::vector<int> > ValueRefVecType;
    
  /* create vector of 10 elements via forwarding constructor */
  ValueRefVecType valueRefVector1(10,1);
    
  /* non-mutating/const op */
  assert( valueRefVector1->size() == 10 );
    
  /* non-mutating/const op */
  assert( (*valueRefVector1)[0] == 1 );
  
#if 0    
  /* error - compilation failure occurs calling a non-const op */
  (*valueRefVector1)[0] = 2;
#endif

  /* copy ctor */
  ValueRefVecType valueRefVector2(valueRefVector1);
    
  /* test for equality */
  assert( valueRefVector1 == valueRefVector2 );
    
  /* test for equality (implicit conversion) */
  assert( valueRefVector2 == std::vector<int>(10,1) );
    
  /* valueRefVector1 and valueRefVector2 share same std::vector */
  assert( valueRefVector1.identity(valueRefVector2) );

#if 0    
  /* ref count is no longer one */
  assert( !valueRefVector1.unique_instance() );
#endif

  /* new value */
  valueRefVector1 = std::vector<int>(5);
    
  /* non-mutating/const */
  assert( valueRefVector1->size() == 5 );
    
  /* test for equality - value semantics */
  assert( !(valueRefVector1 == valueRefVector2) );
    
  /* valueRefVector1 and valueRefVector2 do not share same std::vector */
  assert( !valueRefVector1.identity(valueRefVector2) );
}