#include <cmath>
#include <array>
#include <iostream>
#include <random>

double mag(const std::array<double, 3>& u)
{
    return std::sqrt(u[0]*u[0] + u[1]*u[1] + u[2]*u[2]);
}

double dot(const std::array<double, 3>& u, const std::array<double, 3>& v)
{
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

std::array<double, 3> cross(const std::array<double, 3>& u, const std::array<double, 3>& v)
{
    std::array<double, 3> r;
    r[0] = u[1]*v[2] - u[2]*v[1];
    r[1] = u[2]*v[0] - u[0]*v[2];
    r[2] = u[0]*v[1] - u[1]*v[0];

    return r;
}

int main(int, char*[])
{
    // use random numbers to be sure compiler isn't being sneaky
    std::random_device rd;
    std::mt19937 gen(rd());
    // try to keep the spread between these numbers small but larger than maybe ~0.01-1.0
    std::uniform_real_distribution<> dis(0.0, 0.01);
    // this does the trick but I really feel like I've seen worse without the inputs
    // being so badly conditioned
    // std::uniform_real_distribution<> dis(0.0, 0.001);

    // try to keep the array components small but larger than ~1.0
    std::array<double, 3> u = {1E5 + dis(gen), 1E5 + dis(gen), 1E5 + dis(gen)};
    std::array<double, 3> v = {1E5 + dis(gen), 1E5 + dis(gen), 1E5 + dis(gen)};

    const auto mag_u = mag(u);
    const auto mag_v = mag(v);
    const auto w = cross(u, v);
    const auto mag_w = mag(w);
    const auto d = dot(u, v);

    std::cout << "mag_u^2: " << mag_u*mag_u << std::endl;
    std::cout << "d: " << d << std::endl;

    // rad calculated from dot product is probably a more accurate comparison point
    // because it doesn't involve subtraction
    const auto rad_d = std::acos(d/(mag_u*mag_v));
    const auto rad_c = std::asin(mag(w)/(mag_u*mag_v));

    std::cout << "rad_d: " << rad_d << std::endl;
    std::cout << "rad_c: " << rad_c << std::endl;
}