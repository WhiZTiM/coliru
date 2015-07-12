//mystd plays a role of the std namespace
//which does not allow any new overloads in it
//so we define one in the global namespace
namespace mystd {

template<typename T>
struct A {};

}

//if one uncomment this, everything works as designed
//int f(const mystd::A<int>& v);

//this some namespace which is supposed to be the main one
namespace a {

template<typename T>
int f(const T& v) {
  return 0;
}

template<typename T>
int operator-(const T& v) {
  return 0;
}

}

//this should be different from ::a
//so that `using namespace a;` would import global functions 
//as well as all functions from namespace a, since 
//the global namespace is the nearest common namespace
//see http://www.open-std.org/jtc1/sc22/open/n2356/dcl.html#namespace.udir 
namespace b {

template<typename T>
int Call(const T& v) {
  using namespace ::a;
  return -v + f(v);
}

}

int operator-(const mystd::A<int>&) {
  return 1;
}
int f(const mystd::A<int>&) {
  return 2;
}

int main() {
  //why this returns 1, not 3?
  //what is the difference between operator-() & f()?
  return b::Call(mystd::A<int>());
}
