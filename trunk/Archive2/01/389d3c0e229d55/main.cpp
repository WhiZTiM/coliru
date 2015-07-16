#include <iostream> // std::cout, std::endl
#include <memory> // std::shared_ptr, std::weak_ptr
#include <boost/python.hpp>

/// @brief legacy namespace that cannot be changed.
namespace legacy {

void initialize() { std::cout << "legacy::initialize()" << std::endl; }
void shutdown()   { std::cout << "legacy::shutdown()" << std::endl;   }

class Test
{
public:
  Test()          { std::cout << "legacy::Test::Test()" << std::endl;  }
  virtual ~Test() { std::cout << "legacy::Test::~Test()" << std::endl; }
};

void use_test(Test&) {}

} // namespace legacy

namespace {

/// @brief Guard that will initialize or shutdown the legacy API.
struct legacy_api_guard
{
  legacy_api_guard()  { legacy::initialize(); }
  ~legacy_api_guard() { legacy::shutdown();   }
};

/// @brief Global shared guard for the legacy API.
std::weak_ptr<legacy_api_guard> legacy_api_guard_;

/// @brief Get (or create) guard for legacy API.
std::shared_ptr<legacy_api_guard> get_api_guard()
{
  auto shared = legacy_api_guard_.lock();
  if (!shared)
  {
    shared = std::make_shared<legacy_api_guard>();
    legacy_api_guard_ = shared;
  }
  return shared;
}

} // namespace 

/// @brief legacy_object_holder is a smart pointer that will hold
///        legacy types and help guarantee the legacy API is initialized
///        while these objects are alive.  This smart pointer will remain
///        transparent to the legacy library and the user-facing Python.
template <typename T>
class legacy_object_holder
{
public:

  typedef T element_type;

  template <typename... Args>
  legacy_object_holder(Args&&... args)
    : legacy_guard_(::get_api_guard()),
      ptr_(std::make_shared<T>(std::forward<Args>(args)...))
  {}

  legacy_object_holder(legacy_object_holder& rhs) = default;

  element_type* get() const { return ptr_.get(); }

private:

  // Order of declaration is critical here.  The guard should be
  // allocated first, then the element.  This allows for the
  // element to be destroyed first, followed by the guard.
  std::shared_ptr<legacy_api_guard> legacy_guard_;
  std::shared_ptr<element_type> ptr_;
};

/// @brief Helper function used to extract the pointed to object from
///        an object_holder.  Boost.Python will use this through ADL.
template <typename T>
T* get_pointer(const legacy_object_holder<T>& holder)
{
  return holder.get();
}

/// Auxiliary function to make exposing legacy objects easier.
template <typename T, typename ...Args>
legacy_object_holder<T>* make_legacy_object(Args&&... args)
{
  return new legacy_object_holder<T>(std::forward<Args>(args)...);
}

// Wrap the legacy::use_test function, passing the managed object.
void legacy_use_test_wrap(legacy_object_holder<legacy::Test>& holder)
{
  return legacy::use_test(*holder.get());
}

BOOST_PYTHON_MODULE(example)
{
  namespace python = boost::python;
  python::class_<
      legacy::Test, legacy_object_holder<legacy::Test>, 
      boost::noncopyable>("Test", python::no_init)
    .def("__init__", python::make_constructor(
      &make_legacy_object<legacy::Test>))
    ;

  python::def("use_test", &legacy_use_test_wrap);
}