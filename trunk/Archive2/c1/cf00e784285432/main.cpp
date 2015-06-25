#include <string>
using std::string;

struct TNumeric {
    bool    Negative;
    string Integral;
    string Fraction;
};
union TValue {
    // The unnamed structs are needed because otherwise the compiler does not accept it...
    bool                Bit;
    struct {TNumeric    Numeric;};
    struct {string     Text;};
};

int main()
{
    TNumeric Numeric;
    TNumeric &rNumeric{ Numeric };
    rNumeric.Integral = "";
    rNumeric.Integral.push_back( 'X' ); //OK, no problem
    
    TValue Value;
    TValue &rValue{ Value };
    rValue.Text = "";
    rValue.Text.push_back( 'X' ); //OK, no problem
    
    rValue.Numeric.Integral = "";
    rValue.Numeric.Integral.push_back( 'X' ); // Exception
}