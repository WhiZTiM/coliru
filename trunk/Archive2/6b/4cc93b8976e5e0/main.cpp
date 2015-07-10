#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

class Date
{
    public:
    bool operator < (const Date & tmp) const
    {
        if (this->m_month < tmp.m_month)
        {
            return true;
        }
        else
        {
            if(this->m_month == tmp.m_month)
            {
                return this->m_date < tmp.m_date ? true : false;
            }
        }
        return false;
    }
    
    const std::string & getMonth() const { return m_month; }
    const short & getDate() const { return m_date; }
    Date(const std::string & month, const short & date) : m_month(month), m_date(date)  {}
    private:
    std::string m_month;
    short m_date;
};
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

//using namespace std::rel_ops;

int main()
{
   Date a(std::string("A"), 15);
   Date b(std::string("A"), 16);
   std::set<Date> qwe;
   qwe.insert(b);
   qwe.insert(a);
//   std::cout<< (b<a ? "1" : "0");
   std::for_each(qwe.cbegin(), qwe.cend(), [] (const Date & tmp)
   {
       std::cout<<tmp.getMonth()<<tmp.getDate();
   }
   );
//    std::cout << words << std::endl;
}
