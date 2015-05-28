#include <iostream>
#include <sstream>
#include <algorithm>

struct word_inserter_impl {
    word_inserter_impl(int words, std::string& str, char delim) : str_(str), delim_(delim), words_(words)
    { }

    friend std::istream& operator>>(std::istream& is, const word_inserter_impl& wi) {
        std::istream::sentry ok(is);
        
        if (ok) {
            std::istreambuf_iterator<char> it(is), end;
            while (it != end && wi.words_) {
                if (*it == wi.delim_) {
                    --wi.words_;
                }
                
                if (wi.words_) {
                    wi.str_ += *it++;
                } else {
                    return is;
                }
            }
        }
        return is;
    }
private:
    std::string& str_;
    char delim_;
    mutable int words_;
};

word_inserter_impl word_inserter(int words, std::string& str, char delim = ' ') {
    return word_inserter_impl(words, str, delim);
}

struct Record {
    int id;
    std::string name;
    int age;
};

std::stringstream ifs("1 joe biden 55");

int main() {
    Record actRecord;
    while (ifs >> actRecord.id >> word_inserter(2, actRecord.name) 
           >> actRecord.age) {
        std::cout << actRecord.id << " " << actRecord.name << " " << actRecord.age << '\n';
    }
}