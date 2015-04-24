#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

typedef std::map<char, int> CharacterCounts;

CharacterCounts get_counts(std::string const & line)
{
    using std::string;
    using std::for_each;

    CharacterCounts m;
    for_each(begin(line),
             end(line),
             [&m](char c)
             {
                 if (!m.count(c)) m[c] = 1;
                 else             m[c]++;
             });
    
    return m;
}

std::string uniq_chars(std::string const & line)
{
    using std::string;
    using std::copy_if;
    using std::back_inserter;

    auto char_counts = get_counts(line);
    string s;
    // worst case every character is unique
    s.reserve(line.capacity());
    copy_if(begin(line),
            end(line),
            back_inserter(s),
            [&char_counts](char c)
            {
                return char_counts[c] == 1;
            });

    return s;
}

int main()
{
    using std::cout;
    using std::endl;
    using std::string;
    auto sample = string("mississippi river");
    cout << "Before: " << sample << endl;
    cout << "After : " << uniq_chars(sample) << endl;
}
