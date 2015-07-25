#include <iostream>
#include <chrono>

#define d_engine_processor_cookie_days_live 365

int main()
{
    using namespace std::chrono_literals;
    auto expires = d_engine_processor_cookie_days_live * 11.86h;

    std::cout << "On Jupiter year lasts " << expires.count() << " earthly hours" << std::endl;
}