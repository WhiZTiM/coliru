#include <utility>
#include <cstdio>
#include <string>
#include <sstream>

enum varType {
    varIgnore,
    varOk,
};
struct var {
    template<class T>
    var(T&& t):
        type(varOk)
    {
        std::stringstream ss;
        ss << std::forward<T>(t);
        str = ss.str();
    }
    var()=default;
    var(var const&)=default;
    var(var &&)=default;
    
    var(var const&&o):var(o){}
    var(var &o):var( const_cast<var const&>(o) ){}
    
    std::string str;
    varType type = varIgnore;
    std::string toString() const { return str; }
};

void logVar(var const& a) {
    printf("%s ", a.toString().c_str());
}

template<class F>
void on_var( var const& v, F&& f ) {
  if (v.type != varIgnore)
    std::forward<F>(f)(v);
}
template<class T, class F>
void on_var( T&& t, F&& f ) {
  var v = std::forward<T>(t);
  on_var(const_cast<var const&>(v), std::forward<F>(f) );
}

template<class...Vars>
void log(var a, Vars&&...vars) {
  logVar(a);
  using discard=int[];
  (void)discard{0,(
    on_var(
        std::forward<Vars>(vars),
        [](var const&v){logVar(v);}
    )
  ,0)...};
  printf("\n");
  fflush(0);
}

int main() {
    log( "hello", 0, 1, 2, 3 );
}