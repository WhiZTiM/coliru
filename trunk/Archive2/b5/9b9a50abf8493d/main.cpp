
namespace ForADL {
  struct X {
    int i;   
  };
  
  X& operator*= (X& lhs, int rhs) { lhs.i *= rhs; return lhs; }

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