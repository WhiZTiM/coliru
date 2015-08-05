#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>


using Nanoseconds = std::chrono::nanoseconds;


static constexpr double C = 0.4;
static constexpr double beta = 0.2;
double w_max = 10000;
double RTT = 20;


static double pow3(double x)
{
    return x * x * x;
}


static double cubic_root(double x)
{
    return std::cbrt(x);
}


double K()
{
    return cubic_root(w_max * beta / C);
}


double W(double t)
{
    return C * pow3(t - K()) + w_max;
}


double W_tcp(double t)
{
    return w_max*(1-beta) + 3*beta/(2-beta)* t/RTT;
}


void a()
{
    auto k = K();
    std::cout << "k=" << k << " k^3=" << (k * k * k) << '\n';
    
    for (auto t = 0; t != 100; ++t)
    {
        auto cwnd = W(t);
        std::cout << " t=" << t << " cwnd=" << cwnd << "/" << w_max << '\n';
        if (cwnd >= 4 * w_max) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}


int main()
{
    a();
}
