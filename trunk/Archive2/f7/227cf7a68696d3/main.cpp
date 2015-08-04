#include <iostream>
#include <chrono>
#include <cmath>


using Nanoseconds = std::chrono::nanoseconds;


static constexpr double C = 0.4;
static constexpr double beta = 0.2;
double w_max = 10000;
double RTT = 500 * 0.001;


static double pow3(double x)
{
    return x * x * x;
}


static double cubic_root(double x)
{
    return std::cbrt(x);
}


//static double to_double_seconds(Nanoseconds ns)
//{
//    return ns.count() / 1000000000.0;
//}


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
    auto cwnd = W(0);    
    for (auto i = 0; i != 5000; ++i)
    {
        auto t = (1.0 * i / 1000) + RTT;
        auto cwnd_next = W(t);
        auto cwnd_tcp = W_tcp(t);
        //std::cout << i << ' ' << cwnd << "/" << w_max << " next=" << cwnd_next << " " << (cwnd + ((cwnd_next - cwnd) / cwnd)) << std::endl;
        std::cout << "i=" << i << " " << "cwnd=" << (cwnd + ((cwnd_next - cwnd) / cwnd)) << " cwnd_tcp=" << cwnd_tcp << '\n';
    }
}


int main()
{
    a();
}