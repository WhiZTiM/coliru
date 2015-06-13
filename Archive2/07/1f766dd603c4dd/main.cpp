//
// Simplest bs_array
//
// Author: Vidar Hasfjord
// Date: 2014-12-09 (last revision 2015-06-09)
// Reply-to: <surname> at btinternet.com
//
// ISO/IEC JTC1/SC22/WG21 Working Paper References:
//
// N3810, "Alternatives for Array Extensions", Bjarne Stroustrup, 2013-10-13
// N4025, "Exploring classes of runtime size", Jeff Snyder and Richard Smith, 2014-05-23
// N4294, "Arrays of run-time bounds as data members", J. Daniel Garcia, 2014-11-23
//

#define ENABLED_WIN32_EXAMPLE 0 // 0 | 1

#if ENABLED_WIN32_EXAMPLE
#include <windows.h>
#endif

#include <malloc.h>
#include <memory>
#include <tuple>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <cassert>
#include <iostream>

//
// Simulates the proposed context-sensitive keyword `__auto_storage(auto_size_fun)`.
//
// This new keyword shall only be used as the default argument for the last parameter of a
// function. This parameter shall be of type `void*`.
//
// The keyword signals to the compiler that it shall:
//
// 1. Call the given function `auto_size_fun`, passing the preceding arguments that were passed to
//    the associated function.
//
// 2. Call `alloca` with the result of (1).
//
// 3. Pass the result of (2) as the last function argument.
//
// Arguments shall only be evaluated once throughout the calling procedure.
//
// A function that uses this feature is an Automatic Storage Allocating Function (ASAF). A class
// with a constructor that uses this feature is an Automatic Storage Allocating Class (ASAC).
//
#define __auto_storage(auto_size_fun) nullptr

//
// Simulates the construction procedure performed by the compiler for an ASAC instance.
// Note that this macro re-evaluates the arguments. The intrinsic construction procedure shall not
// do so; arguments shall be evaluated once only.
//
#define CONSTRUCT_ASAC(cls, ...)\
  cls(__VA_ARGS__, alloca(cls::auto_size(__VA_ARGS__)))

//
// Example ASAC; Array of fixed size determined at run-time
// Bike shed issue: Find a proper name for standardisation.
//
template <class T>
class bs_array
{
public:

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using iterator = pointer;
  using const_iterator = const_pointer;

  // Storage size queries (must match constructors)

  static auto auto_size(size_t n) -> size_t
  { return n * sizeof(value_type); }

  template <class FwdIt>
  static auto auto_size(FwdIt first, FwdIt last) -> size_t
  { return std::distance(first, last) * sizeof(value_type); }

  static auto auto_size(const std::initializer_list<T>& i) -> size_t
  { return i.size() * sizeof(value_type); }

  template <class... Ts>
  static auto auto_size(const std::tuple<Ts...>& args) -> size_t
  { return sizeof...(Ts) * sizeof(value_type); }

  // Construction

  explicit bs_array(size_t n_, void* storage = __auto_storage(auto_size))
    : n{n_}, a{static_cast<pointer>(storage)}
  { std::uninitialized_fill_n(a, n, value_type{}); }

  template <class FwdIt>
  bs_array(FwdIt first, FwdIt last, void* storage = __auto_storage(auto_size))
    : n{static_cast<size_t>(std::distance(first, last))}, a{static_cast<pointer>(storage)}
  { std::uninitialized_copy(first, last, a); }

  bs_array(const std::initializer_list<T>& i, void* storage = __auto_storage(auto_size))
    : n{i.size()}, a{static_cast<pointer>(storage)}
  { std::uninitialized_copy(i.begin(), i.end(), a); }

  template <class... Ts>
  explicit bs_array(const std::tuple<Ts...>& args, void* storage = __auto_storage(auto_size))
    : n{sizeof...(Ts)}, a{static_cast<pointer>(storage)}
  { uninitialized_copy_tuple(args, a); }

  // Destruction

  ~bs_array()
  {
    const auto b = std::reverse_iterator<pointer>(a + n);
    const auto e = std::reverse_iterator<pointer>(a);
    std::for_each(b, e, [](value_type& v) { v.~value_type(); });
  }

  // Array interface

  auto operator[](size_t i) -> reference { return a[i]; }
  auto operator[](size_t i) const -> const_reference { return a[i]; }
  auto begin() -> iterator { return a; }
  auto begin() const -> const_iterator { return a; }
  auto end() -> iterator { return a + n; }
  auto end() const -> const_iterator { return a + n; }
  auto size() const -> size_t { return n; }
  auto data() -> pointer { return a; }
  auto data() const -> const_pointer { return a; }

private:

  const size_t n;
  const pointer a;

  template <class Tuple>
  static void uninitialized_copy_tuple(const Tuple& args, pointer p)
  { 
    uninitialized_copy_tuple_t<std::tuple_size<Tuple>::value>::copy(args, p); 
  }

  template <int N, int Index = 0>
  struct uninitialized_copy_tuple_t
  {
    template <class Tuple>
    static void copy(const Tuple& args, pointer p)
    {
      new(p)value_type{std::get<Index>(args)};
      uninitialized_copy_tuple_t<N, Index + 1>::copy(args, p + 1);
    }
  };

  template <int N>
  struct uninitialized_copy_tuple_t<N, N>
  { static void copy(...) {} };

};

//
// Composition example
// Converts data in Array-Of-Structures (AOS) format to Structure-Of-Arrays (SOA).
// This conversion can be useful in parallel processing (such as graphics) and
// algorithms in which contiguity of data is an important consideration.
//
template <class T>
class aos_to_soa_converter
{
public:

  template <class S>
  static auto auto_size(const S*, size_t n) -> size_t
  { return 3 * n * sizeof(T); }

  template <class S>
  aos_to_soa_converter(const S* a, size_t n, void* storage = __auto_storage(auto_size))
    : x{n, storage},
    y{n, static_cast<char*>(storage) + n * sizeof(T)},
    z{n, static_cast<char*>(storage) + 2 * n * sizeof(T)}
  {
    using std::placeholders::_1;
    std::transform(a, a + n, x.begin(), std::bind(&S::x, _1));
    std::transform(a, a + n, y.begin(), std::bind(&S::y, _1));
    std::transform(a, a + n, z.begin(), std::bind(&S::z, _1));
  }

  using A = bs_array<T>;
  A x;
  A y;
  A z;

};

#if ENABLED_WIN32_EXAMPLE

//
// Dynamic structure encapsulation example
//
// Dynamic structures require that dynamic allocations are performed to copy the structure. While
// such allocations are commonly performed on the heap, an ASAC can provide a more efficient
// encapsulation that allocates space on the current stack frame.
//
// This example encapsulates the printer DEVMODE structure defined by the Windows API.
// The DEVMODE structure is a /versioned structure/ that defines a larger /dynamic structure/
// consisting of the DEVMODE base with additional unknown members as indicated by the members
// dmSize and dmDriverExtra. Subsequent versions of Windows have added additional members to the
// structure and increased dmSize accordingly, and a printer device may add additional trailing
// private data and set dmDriverExtra accordingly.
//
// See: http://msdn.microsoft.com/en-us/library/windows/desktop/dd183565.aspx
//
class device_mode
{
public:

  //
  // Queries the device driver for the size of the device-specific DEVMODE-based structure.
  //
  static auto auto_size(const std::string& device) -> size_t
  { 
    const auto n = const_cast<LPSTR>(device.c_str());
    const auto s = DocumentPropertiesA(nullptr, nullptr, n, nullptr, nullptr, 0);
    if (s < 0) throw std::runtime_error("auto_size: DocumentProperties failed");
    return s;
  }

  //
  // Retrieves the initialisation information for the given printer device.
  // Note that this may include an arbitrary amount of device-specific private data.
  //
  device_mode(const std::string& device, void* storage = __auto_storage(auto_size))
    : d{static_cast<DEVMODE*>(storage)}
  { 
    assert(storage);
    const auto n = const_cast<LPSTR>(device.c_str());
    const auto r = DocumentPropertiesA(nullptr, nullptr, n, d, nullptr, DM_OUT_BUFFER);
    if (r != IDOK) throw std::runtime_error("device_mode: DocumentProperties failed");
  }

  //
  // Updates the device mode structure based on the current public settings.
  // Note that this is needed to update the device-specific private parts of the structure.
  //
  void update()
  {
    const auto n = reinterpret_cast<LPSTR>(&d->dmDeviceName[0]);
    const auto r = DocumentPropertiesA(nullptr, nullptr, n, d, d, DM_IN_BUFFER | DM_OUT_BUFFER);
    if (r != IDOK) throw std::runtime_error("update: DocumentProperties failed");
  }

  auto operator ->() -> DEVMODE* { return d; }
  auto operator ->() const -> const DEVMODE* { return d; }
  auto operator *() -> DEVMODE& { return *d; }
  auto operator *() const -> const DEVMODE& { return *d; }

private:

  DEVMODE* const d;

};

#endif

//
// Test
//
auto main() -> int
{
  using namespace std;
  using A = vector<int>;
  using B = bs_array<int>;

  // Test basic construction.

  const auto a = A{1, 2, 3};
  const auto bs = CONSTRUCT_ASAC(B, a.size());
  const auto bi = CONSTRUCT_ASAC(B, a.begin(), a.end());
  const auto bl = CONSTRUCT_ASAC(B, {1, 2, 3});
  const auto bt = CONSTRUCT_ASAC(B, make_tuple(1, 2, 3));

  assert(static_cast<size_t>(count(begin(bs), end(bs), 0)) == a.size());
  assert(equal(begin(bi), end(bi), begin(a)));
  assert(equal(begin(bl), end(bl), begin(a)));
  assert(equal(begin(bt), end(bt), begin(a)));

  // Test composition.

  using C = aos_to_soa_converter<double>;
  using P = struct { double x, y, z; };
  const auto aos = vector<P>{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
  const auto soa = CONSTRUCT_ASAC(C, &aos[0], aos.size());

  assert(soa.x.size() == aos.size());
  assert(soa.y.size() == aos.size());
  assert(soa.z.size() == aos.size());
  assert(equal(begin(soa.x), end(soa.x), begin(aos), [](auto x, const P& p) { return x == p.x; }));
  assert(equal(begin(soa.y), end(soa.y), begin(aos), [](auto y, const P& p) { return y == p.y; }));
  assert(equal(begin(soa.z), end(soa.z), begin(aos), [](auto z, const P& p) { return z == p.z; }));

#if ENABLED_WIN32_EXAMPLE

  // Test dynamic structure.
  //
  // This test performs pretty much the same tasks as those demonstrated in the Microsoft Support
  // article "How to Modify Printer Settings with the DocumentProperties Function" (KB167345).
  // See: http://support.microsoft.com/kb/167345
  //
  try
  {
    const auto device = []()
    {
      auto n = DWORD{};
      GetDefaultPrinterA(nullptr, &n);
      auto s = string(n, '\0');
      auto r = GetDefaultPrinterA(&s[0], &n);
      if (!r) throw runtime_error("main: GetDefaultPrinter failed");
      return s;
    }();
    auto d = CONSTRUCT_ASAC(device_mode, device);

    // Configure the device settings.
    //
    if (d->dmFields & DM_ORIENTATION)
      d->dmOrientation = DMORIENT_LANDSCAPE;
    if (d->dmFields & DM_DUPLEX)
      d->dmDuplex = DMDUP_HORIZONTAL;
    d.update();

    // Check validity by creating a device context.
    //
    const auto dc = CreateDCA(nullptr, device.c_str(), nullptr, &*d);
    assert(dc != nullptr);
    DeleteDC(dc);
  }
  catch (const std::exception& x)
  {
    cout << "Exception: " << x.what() << endl;
    return 1;
  }

#endif

  cout << "Test succeeded!" << endl;
  return 0;
}
