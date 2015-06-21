#include <iostream>
#include <typeinfo>

struct TDispatch
{
  template <class F>
  static int Encode1(F, float, double)
  {return 0;}
};

template <class F>
static int Encode2(F, float, double)
{return 0;}

template <class F>
struct TDecodeSig;

template <class F, class... TParams>
struct TDecodeSig<int (F, TParams...)>
{
  using T = int (TParams...);
};

using TDecode1Fun = TDecodeSig<decltype(TDispatch::Encode1<int>)>::T;
using TDecode2Fun = TDecodeSig<decltype(Encode2<int>)>::T;

auto main() -> int
{
  using namespace std;
  cout << "decltype(TDispatch::Encode1): " << typeid(decltype(TDispatch::Encode1<int>)).name() << endl;
  cout << "TDecode1Fun: " << typeid(TDecode1Fun).name() << endl;
  cout << "decltype(Encode2): " << typeid(decltype(Encode2<int>)).name() << endl;
  cout << "TDecode2Fun: " << typeid(TDecode2Fun).name() << endl;
  return 0;
}
