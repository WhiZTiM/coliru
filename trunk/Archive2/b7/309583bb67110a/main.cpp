#include <stdint.h>
#include <iostream>
#include <iomanip>
 
//lacking <type_traits> in C++03...
template<typename T, T Value>
struct integral_constant
{
    static const T value = Value;
};
 
template<typename A, typename B>
struct is_same : integral_constant<bool, false> {};
 
template<typename T>
struct is_same<T,T> : integral_constant<bool, true> {};
 
namespace static_rational
{
    template<int64_t P_, int64_t Q_>
    struct rational
	{
		static const int64_t P = P_;
		static const int64_t Q = Q_;
	};
 
    /* find greatest common divisor of two integers */
	template<int64_t U, int64_t V, bool Finished = false>
	struct gcd : gcd<V, U % V, U % V == 0> {};
 
	template<int64_t U, int64_t V>
	struct gcd<U, V, true> : integral_constant<int64_t, U>{};
 
	template<int64_t X>
	struct abs : integral_constant<int64_t, (X < 0) ? -X : X> {};
 
	template<int64_t X>
	struct sign : integral_constant<int64_t, (X < 0) ? -1 : 1> {};
 
    /* find the "smallest" representation for a rational using the greates common divisor of P and Q */
	template<typename Rational>
	struct rational_reduce
	{
	private:
		static const int64_t p_abs = abs<Rational::P>::value;
		static const int64_t q_abs = abs<Rational::Q>::value;
 
		static const int64_t pq_gcd = gcd<p_abs, q_abs>::value;
 
		static const int64_t p_sign = sign<Rational::P>::value;
		static const int64_t q_sign = sign<Rational::Q>::value;
 
		//store sign only in P so rational_equal is easy to implement
		static const int64_t np_sign = p_sign == q_sign ? 1 : -1;
		static const int64_t nq_sign = 1;
	public:
		typedef rational<np_sign * p_abs / pq_gcd, nq_sign * q_abs / pq_gcd> result;
	};
 
	template<typename R1, typename R2>
	struct rational_equal : is_same<typename rational_reduce<R1>::result, typename rational_reduce<R2>::result> {};
 
	template<typename R1, typename R2>
	struct rational_mul : rational_reduce< rational<R1::P * R2::P, R1::Q * R2::Q> > {};
 
	template<typename R1, typename R2>
	struct rational_div : rational_reduce< rational<R1::P * R2::Q, R1::Q * R2::P> > {};
 
	template<typename R1, typename R2>
	struct rational_add : rational_reduce< rational<R1::P * R2::Q + R2::P * R1::Q, R1::Q * R2::Q> > {};
    
	template<typename R1, typename R2>
	struct rational_sub : rational_reduce< rational<R1::P * R2::Q - R2::P * R1::Q, R1::Q * R2::Q> > {};
 
	template<int64_t P, int64_t Q>
	std::ostream& operator<<(std::ostream& os, const rational<P, Q>&)
	{
		return os << (P >= 0 ? " " : "") << P << " : " << (Q >= 0 ? " " : "") << Q;
	}
 
}
 
int main()
{
	using namespace static_rational;
    
	{
		typedef rational_mul< rational<1, 2>, rational<2, 4> >::result R;
 
		std::cout << R() << "\n";
 
		typedef rational_sub< rational<1, 3>, rational<4, 2> >::result result;
 
		std::cout << result() << "\n";
	}
 
	{
		typedef rational<-1, -2> R1;
		typedef rational< 4,  8> R2;
 
		typedef rational_reduce<R1>::result rR1;
		typedef rational_reduce<R2>::result rR2;
 
		std::cout <<  rR1() << "\n" << rR2() << "\n";
 
		const bool eq = rational_equal<R1, R2 >::value;
 
		std::cout << R1() << " == " << R2() << " ? " << std::boolalpha << eq << "\n";
	}
}