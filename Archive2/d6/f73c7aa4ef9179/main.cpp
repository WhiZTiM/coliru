#include <boost/multiprecision/random.hpp>
#include <boost/random.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>

int main() {
    namespace mp = boost::multiprecision;

    boost::uniform_01<mp::cpp_dec_float_50> uf;
    boost::random::independent_bits_engine<boost::mt19937, 50L * 1000L / 301L, mp::number<mp::cpp_int::backend_type, mp::et_off> > gen;

    boost::random::seed_seq ss = { 12064, 3867, 13555, 28676, 4599, 5031, 13040 };
    gen.seed(ss);

    std::cout << std::setprecision(50);
    for (unsigned i = 0; i < 10; ++i) {
        std::cout << uf(gen) << std::endl;
    }
}
