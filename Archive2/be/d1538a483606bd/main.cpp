#include <iostream>
#include <memory>
#include <type_traits>

template<typename _type>
class handle
{
  using ptr = std::shared_ptr<_type>;
  using pptr = std::shared_ptr<ptr>;
public:
  //////////////////////////
  // big three and a half //
  //////////////////////////
  handle() :
    mData(make_pptr())
  {}
  handle(handle<_type> const & other) :
    mData(make_pptr(*(other.mData)))
  {}
  handle(handle<_type> && other) :
    mData(make_pptr(std::move(*(other.mData))))
  {}

  handle<_type> & operator=(handle<_type> const & other)
  {
    *mData = *(other.mData);
    return *this;
  }
  handle<_type> & operator=(handle<_type> && other)
  {
    *mData = std::move(*(other.mData));
    return *this;
  }

  ///////////////////////
  // sub type handling //
  ///////////////////////

  // type handling
  handle(_type const & data) :
    mData(make_pptr(data))
  {}
  handle(_type && data) :
    mData(make_pptr(std::move(data)))
  {}

  handle<_type> & operator=(_type const & data)
  {
    **mData = data;
    return *this;
  }
  handle<_type> & operator=(_type && data)
  {
    **mData = std::move(data);
    return *this;
  }

  // pointer handling
  handle(ptr const & pointer) :
    mData(make_pptr(pointer))
  {}
  handle(ptr && pointer) :
    mData(make_pptr(std::move(pointer)))
  {}

  handle<_type> & operator=(ptr const & pointer)
  {
    *mData = pointer;
    return *this;
  }
  handle<_type> & operator=(ptr && pointer)
  {
    *mData = std::move(pointer);
    return *this;
  }

  //////////////////////
  // public interface //
  //////////////////////

  bool is_valid() const
  {
    return static_cast<bool>(*this);
  }

  void swap(handle<_type> & other)
  {
    mData.swap(other.mData);
  }

  //////////////////////////
  // operator overloading //
  //////////////////////////
  _type * operator->() const
  {
    // if (!is_valid())
    //   throw handle_invalid_exception();
    return &(**mData);
  }

  _type & operator*()
  {
    // if (!is_valid())
    //   throw handle_invalid_exception();
    return **mData;
  }

  constexpr operator bool() const
  {
      return *mData != nullptr;
  }

  operator _type &()
  {
    // if (!is_valid())
    //   throw handle_invalid_exception();
    return **mData;
  }

  operator ptr()
  {
    // if (!is_valid())
    //   throw handle_invalid_exception();
    return *mData;
  }

private:
  pptr mData;

  /////////////////////
  // factory methods //
  /////////////////////
  constexpr auto make_ptr()
  {
    return std::make_shared<_type>(nullptr);
  }

  template<typename ..._args>
  constexpr auto make_ptr(_args && ...args)
  {
    return std::make_shared<_type>(std::forward<_args>(args)...);
  }

  constexpr auto make_pptr(ptr const & pointer)
  {
    return std::make_shared<ptr>(pointer);
  }

constexpr auto make_pptr(ptr & pointer)
{
return std::make_shared<ptr>(pointer);
}

  constexpr auto make_pptr(ptr && pointer)
  {
    return std::make_shared<ptr>(std::move(pointer));
  }

template<typename ..._args,
         typename = std::enable_if_t<
                        (sizeof...(_args) == 0) ||
                        not std::is_same<
                                ptr,
                                std::decay_t<
                                    typename std::tuple_element<0, std::tuple<_args...>>::type
                                >
                            >{}
                    >
        >
constexpr auto make_pptr(_args && ...args)
{
  return std::make_shared<ptr>(make_ptr(std::forward<_args>(args)...));
}
};

int main()
{
  handle<int> h = 5;
  if (h)
  {
    std::cout << h << std::endl;
  }
  handle<int> h2(h);
  if (h2)
  {
    std::cout << h2 << std::endl;
  }
}
