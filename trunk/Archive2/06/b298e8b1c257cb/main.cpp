#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>

template <typename BigInt, typename Backend = typename BigInt::backend_type>
void write_binary(std::ostream& os, BigInt const& number) {
    static_assert(boost::is_pod<typename Backend::local_limb_type>::value, "not allowed");

    os.write(
            reinterpret_cast<char const*>(number.backend().limbs()), 
            number.backend().size()*sizeof(typename Backend::local_limb_type)
        );
}

int main()
{
    using uint128_t = boost::multiprecision::uint128_t;

    std::ofstream ofs("binary.dat", std::ios::binary);
    write_binary(ofs, uint128_t(42));
}
