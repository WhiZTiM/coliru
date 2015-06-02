#include <boost/multiprecision/random.hpp>
#include <boost/random.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>

int main() {
    namespace mp = boost::multiprecision;

    boost::uniform_01<mp::cpp_dec_float_50> uf;
    boost::normal_distribution<mp::cpp_dec_float_50> n01(0.0, 1.0);

    boost::random::independent_bits_engine<boost::mt19937, 50L * 1000L / 301L, mp::number<mp::cpp_int::backend_type, mp::et_off> > gen;

    std::cout << std::setprecision(50);
    for (unsigned i = 0; i < 10; ++i) {
        std::cout << uf(gen) << std::endl;
        std::cout << n01(gen) << std::endl;
    }
    return 0;
}
