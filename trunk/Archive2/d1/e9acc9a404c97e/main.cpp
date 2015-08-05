#include <iostream>
#include <cmath>

static constexpr double C = 0.4;
static constexpr double beta = 0.2;

double pow3(double x)
{
    return x * x * x;
}

double calculate_window(double t, double k, double w_max)
{
    return C * pow3(t - k) + w_max;
}

int main()
{
    double w_max = 20000;
    auto k = std::cbrt(w_max * beta / C);
    
    std::cout << "k=" << k << std::endl;
    
    for (auto t = 0; t != 50; ++t)
    {
        int cwnd = calculate_window(t, k, w_max);
        std::cout << " t=" << t << " cwnd=" << cwnd << '\n';
    }
}


//  30000 +-+----+-----+------+------+------+-----+------+------+-----+----+-+
//        +      +     +      +      +      +     +      +      +     +      +
//        |                                                   "data"    A   A|
//  28000 +-+                                                              +-+
//        |                                                               A  |
//  26000 +-+                                                            A +-+
//        |                                                             A    |
//        |                                                          AA      |
//  24000 +-+                                                       A      +-+
//        |                                                       A          |
//        |                                                     AA           |
//  22000 +-+                                                AA            +-+
//        |                                              AA A                |
//        |                                   A AAA AAA A                    |
//  20000 +-+          A AAA AAA AAA AAA AA AA                             +-+
//        |        A AA                                                      |
//  18000 +-+    AA                                                        +-+
//        |   AA                                                             |
//        +A A   +     +      +      +      +     +      +      +     +      +
//  16000 A-+----+-----+------+------+------+-----+------+------+-----+----+-+
//        0      5     10     15     20     25    30     35     40    45     50
