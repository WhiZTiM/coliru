#pragma once


template<typename T>
T sum(T a, T b)
{
    return a + b;
}


extern template int sum(int, int);
extern template long sum(long, long);
extern template long sum(double, double);

