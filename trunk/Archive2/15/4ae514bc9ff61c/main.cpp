#include <algorithm>
#include <iostream>

int main()
{
    const std::string m("C:\\MyFolderA\\MyFolderB\\MyFolderC");
    const std::string slash("\\");
    auto last_slash(std::find_end(std::cbegin(m), std::cend(m), std::cbegin(slash), std::cend(slash)));
    auto second_to_last_slash(std::find_end(std::cbegin(m), last_slash, std::cbegin(slash), std::cend(slash)));
    const std::string parent(++second_to_last_slash, last_slash);
    
    std::cout << parent;
}