#include <functional>
#include <algorithm>
#include <cctype>
#include <list>
#include <iterator>
#include <iostream>
#include <string>

template <typename T, typename Comparer = std::greater<T>>
class LinkedList
{
    private:
        std::list<T> m_list;

    public:
        void insert(const T& data)
        {
            Comparer comp;
            typename std::list<T>::iterator it = m_list.begin();
            while (it != m_list.end())
            {
                if (comp(data, *it))
                    ++it;
                else
                {
                    m_list.insert(it,data);
                    return;
                }
            }
            m_list.push_back(data);
        }

        // use this for demonstration purposes only
        void displayMe()
        {
            std::copy(m_list.begin(), m_list.end(), std::ostream_iterator<T>(std::cout, "\n"));
        }
};

struct MyComparerForStrings
{
    bool operator()(const std::string& s1, const std::string& s2) 
    { 
        std::string str1Cpy(s1);
        std::string str2Cpy(s2);
        std::transform(str1Cpy.begin(), str1Cpy.end(), str1Cpy.begin(), ::tolower);
        std::transform(str2Cpy.begin(), str2Cpy.end(), str2Cpy.begin(), ::tolower);
        return (str1Cpy > str2Cpy);
    }
};

using namespace std;

int main()
{
    LinkedList<std::string,  MyComparerForStrings> sList;
    sList.insert("abc");
    sList.insert("zzz");
    sList.insert("joe");
    sList.insert("BOB");
    sList.displayMe();
    cout << "\n";
    LinkedList<int> intList;
    intList.insert(10);
    intList.insert(1);
    intList.insert(3);
    intList.displayMe();
}