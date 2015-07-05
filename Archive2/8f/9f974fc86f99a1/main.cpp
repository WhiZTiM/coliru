#include <iostream>
#include <string>
#include <vector>
#include <math.h>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

//x : bit rate
//y : frame rate
// p: packet loss
int main()
{
    double p=0.7;
    double x=3.5;
    double y=30;
    double color = 1+(0.09136*log(y)+1.11132*log(0.93128+1.79391*x))*exp(-p/(-1.24607+0.01436*exp(y/33.775)+2.17023*exp(x/5.37876))) ;   
    double depth = 1+(0.08751*log(y)+1.05853*log(0.93067+1.79210*x))*exp(-p/(-0.46754+1.67570*exp(y/33.030)+0.39725*exp(x/4.45855)));
    double Q=0.13*color+0.87*depth;
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << Q << std::endl;
}
