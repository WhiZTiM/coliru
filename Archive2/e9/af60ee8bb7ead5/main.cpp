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
	boost::split(result, input, boost::is_any_of(delimiter), boost::algorithm::token_compress_on);
}

namespace bsq = boost::spirit::qi;
template <typename Iterator>
struct ValueList : bsq::grammar<Iterator, std::vector<std::string>()>
{
	ValueList(const std::string& sep, bool isCaseSensitive) : ValueList::base_type(query)
	{
		if (isCaseSensitive)
		{
			query = value >> *(sep >> value);
			value = *(bsq::char_ - sep);
		}
		else
		{
			auto separator = bsq::no_case[sep];
			query = value >> *(separator >> value);
			value = *(bsq::char_ - separator);
		}
	}
	bsq::rule<Iterator, std::vector<std::string>()> query;
	bsq::rule<Iterator, std::string()> value;
};

void spirit(std::vector<std::string>& result, const std::string& input, const std::string& delimiter)
{
	result.clear();
	ValueList<std::string::const_iterator> parser(delimiter, false);
	auto itBeg = input.begin();
	auto itEnd = input.end();
	if (!(bsq::parse(itBeg, itEnd, parser, result) && (itBeg == itEnd)))
		result.push_back(input);
}

int main(int argc, char* argv[])
{
	std::string input = "2309|ioperwkl|2039i|rjjdsf|klsdjf230o|kx23904iep2|xp,39,4p2|xlmq2i3219||";
	std::string separator = "|";
	std::vector<std::string> result;
	size_t iterations = 1000000;
	auto start = std::chrono::high_resolution_clock::now();
	size_t count = 0;
	for (auto i = 0U; i < iterations; i++)
	{
		original(result, input, separator);
		count += result.size();
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << count << " splits in " << ms << "ms." << std::endl;

	count = 0;
	start = std::chrono::high_resolution_clock::now();
	for (auto i = 0U; i < iterations; i++)
	{
		possible(result, input, separator);
		count += result.size();
	}
	end = std::chrono::high_resolution_clock::now();
	ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << count << " splits in " << ms << "ms." << std::endl;

	count = 0;
	start = std::chrono::high_resolution_clock::now();
	for (auto i = 0U; i < iterations; i++)
	{
		spirit(result, input, separator);
		count += result.size();
	}
	end = std::chrono::high_resolution_clock::now();
	ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << count << " splits in " << ms << "ms." << std::endl;
	return 0;
}

