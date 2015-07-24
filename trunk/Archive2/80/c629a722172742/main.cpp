#include <iostream>
#include <regex>
#include <string>
#include <vector>

class Matcher {
    public:
    
    template<typename Iter> Matcher(Iter b, Iter e) {
        std::string pattern;
        int caps = 1;
        for (Iter p = b; p != e; ++p) {
            std::regex alternative(*p);
            capture_to_index_.push_back(caps);
            caps += 1 + alternative.mark_count();
            pattern += "|(";
            pattern += *p;
            pattern += ')';
        }
        pattern_regex_ = pattern.c_str() + 1; /* Ignore leading | */
    }
    int match(const std::string needle) {
        std::smatch results;
        if (std::regex_match(needle, results, pattern_regex_))
            for (size_t i = 0; i < capture_to_index_.size(); ++i)
                if (results[capture_to_index_[i]].matched)
                    return i;
        return -1;
    }
    
    private:
        std::regex pattern_regex_;
        std::vector<int> capture_to_index_;
};

int main(int argc, char** argv) {
    Matcher m(argv + 2, argv + argc);
    std::cout << m.match(argv[1]);
    return 0;
}