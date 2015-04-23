#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

struct requote {
    requote(std::istream& is) : _is(is.rdbuf()) {}

    friend std::ostream& operator<<(std::ostream& os, requote const& manip) {
        return manip.call(os);
    }

  private:
    std::ostream& call(std::ostream& os) const {
        boost::phoenix::function<copy_out> copy_out_({os});
        using namespace boost::spirit::qi;
        
        boost::spirit::istream_iterator f(_is >> std::noskipws), l;
        bool ok = phrase_parse(f,l,
                *('"' > *raw[long_double][copy_out_(_1)] > '"') [boost::phoenix::ref(os)<<'\n'],
                space
            );

        if (ok && f==l)
            return os;

        throw std::runtime_error("parse error at '" + std::string(f,l) + "'");
    }

    struct copy_out {
        mutable std::ostreambuf_iterator<char> out;

        //template <typename...> struct result { typedef void type; };
        template <typename R> void operator()(R const& r) const {
            *out++ = '"';
            out = std::copy(r.begin(), r.end(), out);
            *out++ = '"';
            *out++ = ' ';
        }
    };
    mutable std::istream _is;
};

#include <iostream>
int main() {
    std::cout << requote(std::cin);
}
