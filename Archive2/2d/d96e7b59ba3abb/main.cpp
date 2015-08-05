#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>


using Nanoseconds = std::chrono::nanoseconds;


static constexpr double C = 0.4;
static constexpr double beta = 0.2;
double w_max = 3000;
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
    std::cout << "k=" << k << " k3=" << (k * k * k) << '\n';

    auto num_iterations = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        auto t = 0.5 * std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
        auto cwnd = W(t);
        //auto new_cwnd = W(t + RTT);
        //auto diff = ((new_cwnd - cwnd) / cwnd);
        //cwnd += diff;
        std::cout << " cwnd=" << cwnd
                  //<< " new_cwnd=" << new_cwnd
                  //<< " diff=" << diff
                  << '\n';
        if (cwnd >= 2 * w_max) break;
        if (num_iterations++ >= 50000) break;
    }
}


int main()
{
    a();
}
