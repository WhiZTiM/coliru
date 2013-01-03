/**
 * Problem 12
 * ----------
 * The sequence of triangle numbers is generated by adding the natural numbers.
 * So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The
 * first ten terms would be:
 *   1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 *
 * Let us list the factors of the first seven triangle numbers:
 *   1: 1
 *   3: 1,3
 *   6: 1,2,3,6
 *   10: 1,2,5,10
 *   15: 1,3,5,15
 *   21: 1,3,7,21
 *   28: 1,2,4,7,14,28
 *
 * We can see that 28 is the first triangle number to have over five divisors.
 *
 * What is the value of the first triangle number to have over five hundred
 * divisors?
 */


#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>



typedef std::map<unsigned, unsigned> Map;
Map get_prime_factors(unsigned n);


template<typename T>
std::ostream& operator<<(std::ostream & os, const std::vector<T> & vec)
{
    os << "{ ";
    for (const auto & v : vec)
    {
        os << v << " ";
    }
    return os << "}";
}

template<typename T>
std::ostream& operator<<(std::ostream & os, const std::map<T, T> & vec)
{
    unsigned c = 0;
    for (const auto & p : vec)
    {
        if (c++)
        {
            os << '*';
        }
        for (unsigned i = 0; i < p.second; ++i)
        {
            if (i != 0)
            {
                os << '*';
            }
            os << p.first;
        }
    }
    return os;
}


bool is_prime(unsigned n, const std::vector<unsigned> & preceding)
{
    // precondition: "preceding" contains all primes < sqrt(n)

    for (auto p : preceding)
    {
        if ((p * p) > n)
        {
            return true;
        }

        if (n % p == 0)
        {
            return false;
        }
    }
    return true;
}


unsigned next_prime(std::vector<unsigned> & preceding)
{
    if (preceding.empty())
    {
        preceding.push_back(2);
        return preceding.back();
    }

    if (preceding.back() == 2)
    {
        preceding.push_back(3);
        return preceding.back();
    }

    for (unsigned n = preceding.back() + 2; ; n += 2)
    {
        if (is_prime(n, preceding))
        {
            preceding.push_back(n);
            return preceding.back();
        }
    }
}


unsigned num_divisors(unsigned n)
{
    unsigned result = 1;
    for (auto pair : get_prime_factors(n))
    {
        result *= (pair.second + 1);
    }
    return result;
}


unsigned triangle(unsigned n)
{
    return n % 2 == 0 ? (n/2) * (n+1) : ((n+1)/2) * n;
}



Map operator+(Map lhs, const Map & rhs)
{
    for (auto p : rhs)
    {
        lhs[p.first] += p.second;
    }
    return lhs;
}


Map get_prime_factors(unsigned n)
{
    std::map<unsigned, unsigned> result;
    static std::vector<unsigned> pre = []{
        std::vector<unsigned> result;
        for (int i = 0; i < 15000; ++i)
        {
            next_prime(result);
        }
        return result;
    }();

    if (n >= pre.size()) throw "n exceeds precalculated";

    for (unsigned i = 0; i < pre.size(); ++i)
    {
        auto p = pre[i];
        while (n % p == 0)
        {
            result[p]++;
            n /= p;
        }
        if (p > n)
        {
            return result;
        }
    }
    return result;
}


Map get_prime_factors_of_tr(unsigned n)
{
    if (n%2 ==0)
    {
        return get_prime_factors(n/2) + get_prime_factors(n + 1);
    }
    else
    {
        return get_prime_factors(n) + get_prime_factors((n + 1)/2);
    }
}


unsigned get_divisors_count_of_tr(unsigned n)
{
    unsigned result = 1;
    for (auto pair : get_prime_factors_of_tr(n))
    {
        result *= pair.second + 1;
    }
    return result;
}


class Stopwatch
{
public:
    typedef std::chrono::high_resolution_clock Clock;

    //! Constructor starts the stopwatch
    Stopwatch() : mStart(Clock::now())
    {
    }

    //! Returns elapsed number of seconds in decimal form.
    double elapsed()
    {
        return 1.0 * (Clock::now() - mStart).count() / Clock::period::den;
    }

    Clock::time_point mStart;
};


int main()
{
    Stopwatch sw;
    for (unsigned i = 2; ; ++i)
    {
        auto div = get_divisors_count_of_tr(i);
        if (div > 500)
        {
            std::cout << i << " " << triangle(i) << std::endl;
            break;
        }
    }
    std::cout << (1000 * sw.elapsed()) << "ms" << std::endl;
}
