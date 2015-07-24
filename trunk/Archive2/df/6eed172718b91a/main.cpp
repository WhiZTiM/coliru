#include <iostream>
using std::ios;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::flush;

#include <iomanip>
using std::setw;
using std::setfill;
using std::setprecision;
using std::setbase;
using std::hex;
using std::dec;

// demo-is-self-contained
#include <cmath>

void
print_fixed(const char *bla, double v, long nd, bool sq)
// Print exactly nd digits of v
// Print sign if sq!=0
{
    if ( bla )  cout << bla;
    if ( sq )  cout << (v>=0 ? '+' : '-');
    else       cout << (v>=0 ? ' ' : '-');
    if ( v < 0 )  v = -v;
    double f = floor(v);
    v -= f;
    cout << f;
    cout << '.';
    do { --nd; } while ( (f*=0.1)>1.0 );
    for ( ; nd>0; --nd)
    {
        v *= 10.0;
        f = floor(v);
        v -= f;
        cout << f;
    }
}
// -------------------------
#include <cstdlib>  // atol(), atof(), strtoul(), strtod()

// To suppress the output such as
//   arg 1: val == explanation
// insert the (following) line
//#define FXT_SILENT_NXARG
// before the inclusion of this header file.

// To prefix each line with a string, define
//#define FXT_PREF_NXARG  "## "
// This can be useful with redirections and filtering.

static int nextarg_act = 0;

template <typename Type>
void next_arg(Type &v, const char *vname, const char *what,
              int argc, char **argv)
{
    const Type def = v;
    ++nextarg_act;

    if ( argc > nextarg_act )
    {
        if ( argv[nextarg_act][0] != '.' )  // "." for default
        {
            int b = 10;  // default is base 10

            // leading "0x" for base 16:
            if ( (argv[nextarg_act][0]=='0') && (argv[nextarg_act][1]=='x') )  b = 16;

            // leading "_" for base 2:
            if ( argv[nextarg_act][0]=='_' )  { b = 2; argv[nextarg_act]+=1; }

            // check signed-ness:
            Type nextarg_x = 1;
            nextarg_x = -nextarg_x;
            if ( nextarg_x > 0 )  // we have an unsigned type
                v = (Type)strtoul(argv[nextarg_act], 0, b);
            else
                v = (Type)strtol(argv[nextarg_act], 0, b);
        }
    }


#ifndef FXT_SILENT_NXARG
#ifdef FXT_PREF_NXARG
    cout << FXT_PREF_NXARG;
#endif
    cout << "arg " << nextarg_act << ": ";
    cout << v << " == " << vname;
    cout << "  [" << what << "]";
    cout << "  default=" << def;
    cout << endl;
#else
    // supress warnings about unused parameters:
    (void)what;
    (void)vname;
    (void)def;
#endif

}
// -------------------------

void
next_float_arg(double &v, const char *vname, const char *what,
               int argc, char **argv)
{
    const double def = v;
    ++nextarg_act;

    if ( argc > nextarg_act )
    {
        // "." for default, but do parse .123
        if ( (argv[nextarg_act][0] != '.') && (argv[nextarg_act][1] != 0) )
            v = strtod(argv[nextarg_act], 0);
    }

#ifndef FXT_SILENT_NXARG
#ifdef FXT_PREF_NXARG
    cout << FXT_PREF_NXARG;
#endif
    cout << "arg " << nextarg_act << ": ";
    cout << v << " == " << vname;
    cout << "  [" << what << "]";
    cout << "  default=" << def;
    cout << endl;
#else
    // supress warnings about unused parameters:
    (void)what;
    (void)vname;
    (void)def;
#endif
}
// -------------------------

void
next_string_arg(char *&v, const char *vname, const char *what,
               int argc, char **argv,
                char *def)  // need explicit default with strings
{
//    cout << " :: String" << endl;

    ++nextarg_act;
    if ( argc > nextarg_act )  v = argv[nextarg_act];
    else  v = def;

#ifndef FXT_SILENT_NXARG
#ifdef FXT_PREF_NXARG
    cout << FXT_PREF_NXARG;
#endif
    cout << "arg " << nextarg_act << ": ";
    cout << '"' << v << '"' << " == " << vname;
    cout << "  [" << what << "]";
    cout << "  default=" << '"' << def << '"';
    cout << endl;
#else
    // supress warnings about unused parameters:
    (void)what;
    (void)vname;
#endif
}
// -------------------------


#define NXARG(v, what) { next_arg(v, #v, what, argc, argv); }
#define NXARGFL(v, what) { next_float_arg(v, #v, what, argc, argv); }
#define NXARGSTR(v, what, def) { next_string_arg(v, ""#v, what, argc, argv, (char *)def); }

#ifdef FXT_SILENT_NXARG
#define RESTARGS_MSG(what)  // silence
#else
#define RESTARGS_MSG(what) \
  cout << "args " << nextarg_act \
  << ","<< nextarg_act+1 << ",... : [" << what <<"]" << endl;
#endif

#define RESTARGS(what) { ++nextarg_act; RESTARGS_MSG(what); }



typedef  unsigned long         ulong;

//% CORDIC computation of sine and cosine.

template <typename T, std::size_t N>
class array_result {
private:
    constexpr static std::size_t size_ = N;
    T data_[N] {}; // T default constructor essential!
public:
    constexpr std::size_t size() const { return N; }
    constexpr T& operator[](std::size_t n)
        { return data_[n]; }
    constexpr const T& operator[](std::size_t n) const
        { return data_[n]; }
    using iterator = T*;
    constexpr iterator begin() { return &data_[0]; }
    constexpr iterator end() { return &data_[N]; }
};

// double *cordic_ctab;
template <typename T, std::size_t N>
constexpr auto generate_cordic_ctab()
{
    array_result<T, N> ret; // Init ret    
    double s = 1.0;
    for (size_t k=0; k<N; k += 1)
    {
        ret[k] = atan(s);
        s *= 0.5;
    }
    return ret; // Return ret
}

constexpr auto cordic_ctab 
    = generate_cordic_ctab<double, 64>();


constexpr double
pow_int(double base, int exp)
{
    if (exp < 0) {
        base = 1.0 / base;
        exp = -1 * exp;
    }
    double result = 1.0;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

constexpr double generate_cordic_1K()
{
    long double K = 1.0;
    for (int j=0; j<200; j += 1)
    {
        K *= sqrt(1.0 + pow_int(2.0,-2*j));
    }
    return 1.0/K; 
}

//const double cordic_K = 1.646760258121065648366051222282298435652376725701027409;
// == prod(j=0,200,sqrt(1+2.0^(-2*j)))
// const double cordic_1K = 0.6072529350088812561694467525049282631123908521500897724;
constexpr const double cordic_1K = generate_cordic_1K();
// -------------------------

//#define TEX
#ifdef TEX
#define COLSEP " &   "
#define ENDL " \\\\"
#else  // TEX
#define COLSEP "  "
#define ENDL ""
#endif  // TEX
const long nd = 9;  // Number of Digits displayed

void
print_xyza(long n, double x, double y, double z, double a)
{
    cout << setw(2) << n;
    print_fixed(COLSEP, x, nd, 0);
    print_fixed(COLSEP, y, nd, 0);
    print_fixed(COLSEP, z, nd, 1);
    print_fixed(COLSEP, a, nd, 1);
    cout << ENDL << endl;
}
// -------------------------


void
cordic_circ(double theta, double &s, double &c, ulong n)
{
    double x = cordic_1K;
    double y = 0;
    double z = theta;
    double v = 1.0;
    print_xyza(-1, x, y, z, 0);

    for (ulong k=0; k<n; ++k)
    {
        double d = ( z>=0 ? +1 : -1 );
        double tx = x - d * v * y;
        double ty = y + d * v * x;
        double tz = z - d * cordic_ctab[k];
        x = tx;  y = ty;  z = tz;
        v *= 0.5;

        print_xyza((long)k, x, y, z, -d*cordic_ctab[k]);
    }
    c = x;
    s = y;
}
// -------------------------


int
main(int argc, char **argv)
{
    double t = M_PI/3.0;
    NXARGFL(t, "Argument for CORDIC sin/cos computation");

    ulong n = 16;
    NXARG(n, "Number of iterations");

    //ulong na = 64;
    //cordic_ctab = new double[na];
    //make_cordic_ctab(na);

    double s, c;

    cordic_circ(t, s, c, n);

    cout << endl;
    double zs = sin(t), zc = cos(t);
    print_xyza(9999, zc, zs, 0.0, 0.0);

    cout << endl;
    cout << setprecision(19);
    cout << "dc = " << setw(12) << c-zc << endl;
    cout << "ds = " << setw(12) << s-zs << endl;
    cout << "2**(-n) = " << pow(2.0, -(double)n) << endl;
    cout << endl;

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/arith"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/arith/cordic-circ-demo.cc"
/// make-target2: "1demo DSRC=demo/arith/cordic-circ-demo.cc DEMOFLAGS=-DTIMING"
/// End:

/*

arg 1: 1.0472 == t  [Argument for CORDIC sin/cos computation]  default=1.0472
arg 2: 16 == n  [Number of iterations]  default=16
-1   0.60725293   0.00000000  +1.04719755  +0.00000000
 0   0.60725293   0.60725293  +0.26179938  -0.78539816
 1   0.30362646   0.91087940  -0.20184822  -0.46364760
 2   0.53134631   0.83497278  +0.04313044  +0.24497866
 3   0.42697471   0.90139107  -0.08122455  -0.12435499
 4   0.48331166   0.87470515  -0.01880574  +0.06241880
 5   0.51064619   0.85960166  +0.01243409  +0.03123983
 6   0.49721492   0.86758051  -0.00318963  -0.01562372
 7   0.50399289   0.86369602  +0.00462270  +0.00781234
 8   0.50061908   0.86566474  +0.00071647  -0.00390623
 9   0.49892833   0.86664251  -0.00123664  -0.00195312
10   0.49977466   0.86615528  -0.00026008  +0.00097656
11   0.50019758   0.86591124  +0.00022819  +0.00048828
12   0.49998618   0.86603336  -0.00001594  -0.00024414
13   0.50009190   0.86597233  +0.00010612  +0.00012207
14   0.50003904   0.86600285  +0.00004508  -0.00006103
15   0.50001261   0.86601811  +0.00001457  -0.00003051

9999   0.50000000   0.86602540  +0.00000000  +0.00000000

dc = 1.261868568147583858e-05
ds = -7.285703386816777538e-06
2**(-n) = 1.52587890625e-05

*/