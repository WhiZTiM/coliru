#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

typedef std::bitset<32> active_mask_t;

class Scoreboard {
public:
    bool checkCollision(unsigned wid) const;
    typedef std::map<unsigned,active_mask_t> reg_entry;
    std::vector< reg_entry > reg_table;
};

bool Scoreboard::checkCollision( unsigned wid ) const
{
    active_mask_t mask;
    mask.reset();
    mask.set(1);
    int i = 1;
	if(reg_table[wid].find(i) != reg_table[wid].end()) {
			active_mask_t common;
			common = mask & reg_table[wid][i];
			if(common.any()) return true;
	}
	return false;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    Scoreboard s;
    active_mask_t t;
    t.reset();
    s.reg_table[0][1] = t;
    bool ret = s.checkCollision(0);
    if(ret) std::cout<<"true";
    else std::cout<<"false";
}
