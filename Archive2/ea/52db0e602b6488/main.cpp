#include <iostream>
#include <string>

std::string
replace_str(std::string &s, const std::string &old, const std::string &_new)
{
    if (old.empty())
        return s;
    /* old is longer than s, then there is no point in checking */
    if (old.size() > s.size()) 
        return s;
    /* _new is empty, so clear s */
    if (_new.empty()) {
        s.clear();
        return s;
    }

    auto it = s.begin();
    const std::string::size_type sz = old.size();
    while (it != s.end()) {
        const std::string::difference_type d = s.cend() - it - 1;
        if (d < sz)
            return s;
        if (*it == *old.cbegin()) {
            const std::string::difference_type r = it - s.cbegin();
            const std::string comp = s.substr(r, r + sz);
            if (comp == old) {
                it = s.erase(it, it + sz);
                it = s.insert(it, _new.begin(), _new.end());
                it += sz;
            }
        } 
        else
            ++it;
    }
    return s;
}

int
main(void)
{
    return 0;
}