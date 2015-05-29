#include <thread>
#include <vector>

int main()
{
  std::vector<std::thread> v(5);
  
  std::vector<std::thread> vv = std::move(v);
}
