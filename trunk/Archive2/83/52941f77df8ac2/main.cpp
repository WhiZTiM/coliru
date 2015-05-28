#include <iostream>
#include <sstream>
#include <algorithm>

template<class CharT>
struct word_inserter_impl {
    word_inserter_impl(int words, std::basic_string<CharT>& str, CharT delim)
        : str_(str)
        , delim_(delim)
        , words_(words)
    { }

    template<class charT>
    friend std::basic_istream<charT>&
    operator>>(std::basic_istream<charT>& is, const word_inserter_impl<charT>& wi) {
        typename std::basic_istream<charT>::sentry ok(is);
        
        if (ok) {
            std::istreambuf_iterator<charT> it(is), end;
            std::back_insert_iterator<std::string> dest(wi.str_);
            
            while (it != end && wi.words_) {
                if (*it == wi.delim_ && --wi.words_ == 0) {
                    break;
                }
                dest++ = *it++;
            }
        }
        return is;
    }
private:
    std::basic_string<CharT>& str_;
    CharT delim_;
    mutable int words_;
};

template<class CharT=char>
word_inserter_impl<CharT> word_inserter(int words, std::basic_string<CharT>& str, CharT delim = CharT(' ')) {
    return word_inserter_impl<CharT>(words, str, delim);
}

struct Record {
    int id;
    std::string name;
    int age;
};

std::stringstream ifs("1 joe biden 55 00000000");

int main() {
    Record actRecord;
    while (ifs >> actRecord.id >> word_inserter(2, actRecord.name) >> actRecord.age) {
        std::cout << actRecord.id << " " << actRecord.name << " " << actRecord.age << '\n';
    }
}