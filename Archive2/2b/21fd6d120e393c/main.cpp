#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/spirit/include/qi.hpp>

#include <vector>
#include <string>
#include <chrono>
#include <iostream>

void original(std::vector<std::string>& result, const std::string& input, const std::string& delimiter)
{
    result.clear();
    boost::char_separator<char> sep(delimiter.c_str());
    boost::tokenizer<boost::char_separator<char>, std::string::const_iterator, std::string> tok(input, sep);

	for (const auto& token : tok)
	{
		result.push_back(token);
	}
}

void possible(std::vector<std::string>& result, const std::string& input, const std::string& delimiter)
{
	result.clear();
	boost::split(result, input, boost::is_any_of(delimiter), boost::algorithm::token_compress_off);
}

namespace detail {
    std::string make_delim_charset(char const* delimiter) {
        std::string result = delimiter;
        std::sort(result.begin(), result.end(), [](char a, char b) { return (a!=b && a=='-') || (b!='-' && a<b); });
        result.erase(std::unique(result.begin(), result.end()), result.end());

        return result;
    }
}

namespace bsq = boost::spirit::qi;

void spirit_direct(std::vector<std::string>& result, const std::string& input, char const* delimiter)
{
	result.clear();

    auto const delim = detail::make_delim_charset(delimiter);

    using namespace bsq;
    if (!parse(input.begin(), input.end(), raw[*(char_ - char_(delim))] % char_(delim), result))
        result.push_back(input);
}

namespace detail {

    template <typename Sep> bsq::rule<std::string::const_iterator, std::vector<std::string>()>
        make_spirit_parser(Sep const& sep) 
        {
            using namespace bsq;
            return raw[*(char_ - sep)] % sep;
        }

    static const auto precompiled_pipes = make_spirit_parser('|');
}

void spirit(std::vector<std::string>& result, const std::string& input, char const* delimiter)
{
	result.clear();

    auto const delim = detail::make_delim_charset(delimiter);

	if (!bsq::parse(input.begin(), input.end(), detail::make_spirit_parser(bsq::char_(delimiter)), result))
        result.push_back(input);
}

void spirit_pipes(std::vector<std::string>& result, const std::string& input)
{
	result.clear();
	if (!bsq::parse(input.begin(), input.end(), detail::precompiled_pipes, result))
        result.push_back(input);
}

template <typename F> void bench(std::string const& caption, F approach) {
    size_t const iterations = 1000000;
    using namespace std::chrono;
    using C = high_resolution_clock;

    auto start = C::now();

    size_t count = 0;
    for (auto i = 0U; i < iterations; ++i) {
        count += approach();
    }

    auto us = duration_cast<std::chrono::microseconds>(C::now() - start).count();
    std::cout << count << " " << caption << " rate: " << (1.*us/iterations) << "μs\n";
}

int main()
{
    std::string const input = "2309|ioperwkl|2039i|rjjdsf|klsdjf-30o|kx23-04iep2|xp~39,4p2|xlmq2i3219||";
    auto separator = ",--|-~";

    std::vector<std::string> result;

    bench("original (boost::tokenizer)", [&] {
            original(result, input, separator);
            return result.size();
        });
    bench("possible (boost::split)", [&] {
            possible(result, input, separator);
            return result.size();
        });
    bench("spirit (dynamic version)", [&] {
            spirit(result, input, separator);
            return result.size();
        });
    bench("spirit (direct version, avoid type erasure)", [&] {
            spirit_direct(result, input, separator);
            return result.size();
        });

    std::cout << "\nnext step:\n";
    bench("spirit (precompiled sep)", [&] {
            spirit_pipes(result, input);
            return result.size();
        });
}
