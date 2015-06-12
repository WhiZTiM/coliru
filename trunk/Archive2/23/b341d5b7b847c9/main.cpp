#include <iostream>
#include <string>
#include <set>
#include <boost/circular_buffer.hpp>

int main()
{
    static constexpr unsigned MAX_UNDO = 5;
    
    boost::circular_buffer<std::unique_ptr<int>> m_buffer{MAX_UNDO};
    
    m_buffer.push_back(std::make_unique<int>(10));
    m_buffer.push_back(std::make_unique<int>(20));
    m_buffer.push_back(std::make_unique<int>(30));
    m_buffer.push_back(std::make_unique<int>(40));
    m_buffer.push_back(std::make_unique<int>(50));
    m_buffer.push_back(std::make_unique<int>(60));
    
    std::for_each(m_buffer.begin(), m_buffer.end(), [](auto const& int_ptr) {
        std::cout << *int_ptr << '\n';
    });
}
