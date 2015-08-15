#include <typeinfo>

class Base {
      virtual bool less( Base const & rhs ) const {
        return false;
      }
    
      int b;
    
      friend bool operator < ( Base const & lhs, Base const & rhs ) {
        std::type_info const & ltype = typeid (lhs);
        std::type_info const & rtype = typeid (rhs);
        if ( ltype == rtype ) {
          if ( lhs.b < rhs.b ) return true;
          if ( rhs.b < lhs.b ) return false;
          return lhs.less( rhs ); // Dynamic types of lhs and rhs already match.
        }
        return ltype.before( rtype );
      }
      public:
      Base( int inb ) : b( inb ) {}
    };
    
    class Derived1 : public Base{
      virtual bool less( Base const & rhs_base ) const {
        Derived1 const & rhs = static_cast< Derived1 const & >( rhs_base );
        return d1 < rhs.d1;
      }
    
      int d1; 
      public:
      Derived1( int inb, int ind ) : Base( inb ), d1( ind ) {}
    };
    
    class Derived2 : public Base{
      virtual bool less( Base const & rhs_base ) const {
        Derived2 const & rhs = static_cast< Derived2 const & >( rhs_base );
        return d1 < rhs.d1;
      }
    
      int d1; 
      public:
      Derived2( int inb, int ind ) : Base( inb ), d1( ind ) {}
    };
    
#include <cassert>

int main() {
    Derived1 d1( 1, 2 ), d1a( 2, 1 ), d13( 1, 3 );
    Derived2 d2( 1, 2 );
    
    Base & d1b = d1, & d2b = d2;
    
    assert ( ! (d1 < d1b) && ! (d1b < d1) );
    assert ( ! (d2 < d2b) && ! (d2b < d2) );
    assert ( d1 < d1a );
    assert ( d1 < d13 );
    assert ( d1 < d2 );
}
