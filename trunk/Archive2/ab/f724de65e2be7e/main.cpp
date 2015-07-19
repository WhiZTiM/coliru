#if TEST_METHOD == 1

#include <string>
#include <vector>
#include <ostream>
#include <boost/iterator/iterator_facade.hpp>

/**
 * Defines a non-mutable view over a tokenized std::string. Individual tokens
 * are known by offset and length, and all operations are intended to avoid
 * actually extracting and copying the individual token characters unless a
 * conversion to std::string is explicitly requested.
 * 
 * This provides for extremely cheap tokenization.
 */
struct string_tokens_view
{
    struct range_bounds_t
	{
		std::string::size_type start, end;
	};
	
	struct range_t
	{
		const std::string& str;
		range_bounds_t bounds;
	
		friend std::ostream& operator<<(std::ostream& os, const range_t& range);
		bool operator==(const std::string& comp) const;
		operator std::string() const;
	};
	
	struct const_iterator : boost::iterator_facade<
		const_iterator,
		range_t,
		boost::random_access_traversal_tag,
		range_t
	>
	{
		explicit const_iterator(const string_tokens_view& _view)
    		: view(&_view)
			, base_it(_view.ranges.begin())
		{}
		
		const_iterator(const string_tokens_view& _view, std::vector<range_bounds_t>::const_iterator _base_it)
			: view(&_view)
			, base_it(_base_it)
		{}
		
	private:
		friend class boost::iterator_core_access;
		
		void increment() { base_it++; }
		void decrement() { base_it--; }
		
		bool equal(const const_iterator& other) const
		{
			return base_it == other.base_it;
		}
		
		range_t dereference() const
		{
			range_t r = { view->str, *base_it };
			return r;
		}
		
		const string_tokens_view* view;
		std::vector<range_bounds_t>::const_iterator base_it;
	};
	
	/**
	 * Tokenises the given string, by splitting on the given delimiter.
	 * 
	 * The string referred to by %str *must* exist for as long as this object does.
	 * 
	 * @param	skip_empty	Iff true, would-be empty tokens (i.e. where no text has been found between consecutive delimiters) are not added to the result.
	 */
	explicit string_tokens_view(const std::string& str, const char delimiter = ' ', bool skip_empty = true);
	
	size_t size() const;
	range_t operator[](const size_t i) const;
	range_t at(const size_t i) const;
	const_iterator begin() const;
	const_iterator end() const;
	
private:
	const std::string& str;
	std::vector<range_bounds_t> ranges;
};

string_tokens_view::string_tokens_view(const std::string& str, const char delimiter, bool skip_empty)
    : str(str)
{
	size_t a = 0, b = 0;
    
    // Pick out token ranges
	while ((b = str.find(delimiter, a)) != std::string::npos) {
		if (b > a || !skip_empty) {
			range_bounds_t r = { a, b };
			ranges.push_back(r);
		}
		
		a = b+1;
	}
    
    // Add any trailing token with no delimiter on its right side
    if (a != str.length() || !skip_empty) {
        range_bounds_t r = { a, str.length() };
        ranges.push_back(r);
    }
}

size_t string_tokens_view::size() const
{
	return ranges.size();
}

string_tokens_view::range_t string_tokens_view::operator[](size_t i) const
{
	range_t result = { str, ranges[i] };
	return result;
}

string_tokens_view::range_t string_tokens_view::at(size_t i) const
{
	range_t result = { str, ranges.at(i) };
	return result;
}

string_tokens_view::const_iterator string_tokens_view::begin() const
{
	return const_iterator(*this, ranges.begin());
}

string_tokens_view::const_iterator string_tokens_view::end() const
{
	return const_iterator(*this, ranges.end());
}

std::ostream& operator<<(std::ostream& os, const string_tokens_view::range_t& range)
{
	os.write(range.str.data() + range.bounds.start, range.bounds.end - range.bounds.start);
	return os;
}

bool string_tokens_view::range_t::operator==(const std::string& comp) const
{
	if (comp.size() != bounds.end - bounds.start)
		return false;
	
	return str.compare(bounds.start, bounds.end - bounds.start, comp) == 0;
}

string_tokens_view::range_t::operator std::string() const
{
	return std::string(str.data() + bounds.start, bounds.end);
}

#else

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> tokenize(const std::string& str, const char delimiter, bool skip_empty)
{
    std::vector<std::string> tokens;
	
	std::stringstream ss(str);
	std::string tmp;
	while (std::getline(ss, tmp, delimiter)) {
		if (!tmp.empty() || !skip_empty)
			tokens.push_back(tmp);
	}
	
	// Represent an empty trailing token; getline ate it up
	if (!skip_empty && !str.empty() && *str.rbegin() == delimiter)
		tokens.push_back("");
	
	return tokens;
}

#endif




#include <iostream>

void test(const char delimiter, const size_t expected_num_tokens, const bool skip_empty, const std::string& input)
{
#if TEST_METHOD == 1
    string_tokens_view v(input, delimiter, skip_empty);
#else
    std::vector<std::string> v = tokenize(input, delimiter, skip_empty);
#endif
}

int main()
{
    for (size_t i = 0; i < TEST_COUNT; i++) {
        test('|', 5, false, "a|b|c|d|e");
        test('|', 6, false, "a|b|c|d|e|");
        test('|', 7, false, "a|b|c|d|e||");
        test('|', 6, false, "a|b|c||d|e");
        test('|', 7, false, "a|b|c||d|e|");
        test('|', 8, false, "a|b|c||d|e||");
        test('|', 8, false, "|a|b|c||d|e|");
        test('|', 9, false, "|a|b|c||d|e||");
        test('|', 9, false, "|a|b|c||d|e|f|");
        
        test('|', 5, true , "a|b|c|d|e");
        test('|', 5, true , "a|b|c|d|e|");
        test('|', 5, true , "a|b|c|d|e||");
        test('|', 5, true , "a|b|c||d|e");
        test('|', 5, true , "a|b|c||d|e|");
        test('|', 5, true , "a|b|c||d|e||");
        test('|', 5, true , "|a|b|c||d|e|");
        test('|', 5, true , "|a|b|c||d|e||");
        test('|', 6, true , "|a|b|c||d|e|f|");
    }
}
