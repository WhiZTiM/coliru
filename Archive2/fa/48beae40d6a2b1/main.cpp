//#define MEMBER
//#define FREE
#define KOENIG

namespace ForADL {
  struct X {
    int i;
    #ifdef MEMBER
    X& operator*=(int rhs) {i*=rhs; return *this;}
    #endif
    #ifdef KOENIG
    friend X& operator*=(X& lhs, int rhs) { lhs.i *= rhs; return lhs; }
    #endif
  };
  #ifdef FREE
  X& operator*= (X& lhs, int rhs) { lhs.i *= rhs; return lhs; }
  #endif

  struct Z {
    X x;
    operator X&() {return x;}
  };
}


struct Y : ForADL::X 
{};
   
int main() { 
  Y y;
  y*=5;
  
  ForADL::Z z;
  z *= 42;
}