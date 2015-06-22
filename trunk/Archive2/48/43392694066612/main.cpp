#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Sun {};
class Rain {};
class CarboneDioxide {};
class WarmRain{};
class WarmCarboneDioxide{};
class WetCarboneDioxide{};
class Tree{};
class Alien{};
class EvilTree{};
class Axe{};
class Log{};
class Fire{};

// Stream
std::ostream& operator<<(std::ostream& os, Sun)               { os << "Sun" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, Rain)              { os << "Rain" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, CarboneDioxide)    { os << "CarboneDioxide" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, WarmRain)          { os << "WarmRain" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, WarmCarboneDioxide){ os << "WarmCarboneDioxide" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, WetCarboneDioxide) { os << "WetCarboneDioxide" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, Tree)              { os << "Tree" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, Alien)             { os << "Alien" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, EvilTree)          { os << "EvilTree" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, Axe)               { os << "Axe" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, Log)               { os << "Log" << "\n";   return os; }
std::ostream& operator<<(std::ostream& os, Fire)              { os << "Fire" << "\n";   return os; }

// Adding elements
//------------------------------------------------------
WarmRain operator+(Sun , Rain )
{
    return WarmRain();
}

WarmRain operator+(Rain, Sun )
{
    return WarmRain();
}
//------------------------------------------------------
WarmCarboneDioxide operator+(Sun , CarboneDioxide )
{
    return WarmCarboneDioxide();
}

WarmCarboneDioxide operator+(CarboneDioxide, Sun )
{
    return WarmCarboneDioxide();
}
//------------------------------------------------------
WetCarboneDioxide operator+(Rain , CarboneDioxide )
{
    return WetCarboneDioxide();
}

WetCarboneDioxide operator+(CarboneDioxide, Rain )
{
    return WetCarboneDioxide();
}

//------------------------------------------------------
Tree operator+(WetCarboneDioxide, Sun )
{
    return Tree();
}

Tree operator+(Sun, WetCarboneDioxide )
{
    return Tree();
}

//------------------------------------------------------
Tree operator+(WarmCarboneDioxide, Rain )
{
    return Tree();
}

Tree operator+(Rain, WarmCarboneDioxide )
{
    return Tree();
}
//------------------------------------------------------
Tree operator+(WarmRain , CarboneDioxide )
{
    return Tree();
}

Tree operator+(CarboneDioxide, WarmRain )
{
    return Tree();
}

//------------------------------------------------------
EvilTree operator+(Tree , Alien )
{
    return EvilTree();
}

EvilTree operator+(Alien, Tree )
{
    return EvilTree();
}

//------------------------------------------------------
Log operator+(EvilTree , Axe )
{
    return Log();
}

Log operator+(Axe, EvilTree )
{
    return Log();
}

//------------------------------------------------------
CarboneDioxide operator+(Log , Fire )
{
    return CarboneDioxide();
}

CarboneDioxide operator+(Fire, Log )
{
    return CarboneDioxide();
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    Sun sun;
    Rain rain;
    CarboneDioxide co2;
    Tree tree;
    Alien alien;
    Axe axe;
    Log log;
    Fire fire;
    std::cout << rain+sun;
    std::cout << rain+co2;
    std::cout << co2+sun;
    std::cout << rain+co2+sun;
    std::cout << tree+alien;
    std::cout << (tree+alien)+axe;
    std::cout << log+fire;
}
