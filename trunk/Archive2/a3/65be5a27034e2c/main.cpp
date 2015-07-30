#include <iostream>
#include <complex>
#include <cmath>
#include <iterator>
#include <vector>

using namespace std;

using cx = complex<double>;
using vcx = vector<cx>;

unsigned int bitReverse(size_t x, size_t log2n)
{
    size_t n = 0;
	for (size_t i = 0; i < log2n; i++)
	{
		n <<= 1;
		n |= (x & 1);
		x >>= 1;
	}
	return n;
}
const double PI = 2.0*asin(1.0);

vcx fft(vcx const& a)
{
    size_t n = a.size();
    size_t log2n = log2(n);
    vcx b(n,0);
	const cx J(0, 1);
	for (size_t i = 0; i < n; ++i) 
        b[bitReverse(i, log2n)] = a[i];

	for (size_t s = 1; s <= log2n; ++s)
	{
		size_t m = 1 << s;
		size_t m2 = m >> 1;
		cx w(1, 0);
		cx wm = exp(-J * (PI / m2));
		for (size_t j = 0; j < m2; ++j)
		{
			for (size_t  k = j; k < n; k += m)
			{
				cx t = w * b[k + m2];
				cx u = b[k];
				b[k] = u + t;
				b[k + m2] = u - t;
			}
			w *= wm;
		}
	}
    return b;
}
int main()
{
    size_t n = 256, k= 1;
	vcx a(n); // { cx(0,0), cx(1,1), cx(3,3), cx(4,4),	cx(4,4), cx(3,3), cx(1,1), cx(0,0) };
    for (size_t i=0; i<n; i++) a[i] = sin(k*i*2.0*PI/(n-1));
	vcx b = fft(a);
    cout << PI << "\n";
	for (auto x : b) cout << x << "\n";
}