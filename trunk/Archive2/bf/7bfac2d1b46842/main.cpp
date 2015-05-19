#include <iostream>
#include <stdexcept>
#include <type_traits>

using namespace std;

template<typename Num_t> // Función recursiva, carácter a carácter.
Num_t getNum(string const& str, Num_t num, signed char sign, size_t i, unsigned char nextc)
{
    if (i == str.size()) return num;
    if (nextc > 9) throw invalid_argument("Eso no es un numero.");
    
    Num_t next = num * 10 + sign * nextc;
    
    if (sign == 1 ? (next < num) : (next > num))
        throw invalid_argument("Numero demasiado grande.");
    
    return getNum(str, next, sign, i + 1, str[i + 1] - '0');
}

template<typename Num_t>
Num_t getNum(string const& str)
{
    if (str.size() == 0) throw invalid_argument("Introduzca un numero.");
    
    size_t i = 0;
    signed char sign = 1;
    
    if (str[i] == '-') {
        if (is_unsigned<Num_t>::value)
            throw invalid_argument("Un numero natural no puede ser < 0.");
            
        ++i; sign = -1;
    } else if (str[i] == '+')
        ++i;
    
    while (str[i] == '0') ++i; // Ignoramos prefijo de 0s.
        
    return getNum<Num_t>(str, 0, sign, i, str[i] - '0');
}

int main()
{   
    while (cin.good()) // Hasta que no me des un número (y quede entrada) no te escapas.
        try {
            string str;
            getline(cin, str); cin.ignore();
            cout << getNum<int>(str) << endl;
            break;
        } catch (invalid_argument const& e) {
            cerr << e.what() << endl;
        }
    
    return 0;
}