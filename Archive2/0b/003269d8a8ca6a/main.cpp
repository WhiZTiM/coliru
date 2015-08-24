#include <iostream>
#include <vector>
#include <algorithm>

bool goodParity(std::vector<int> tiles)
{
  bool parity = true;
  for (std::size_t n = 0; n < tiles.size() - 1; ++n)
  {
    std::size_t pos = std::find(tiles.begin(), tiles.end(), n) - tiles.begin();
    if (pos == n)
      continue;
    
    parity = !parity;
    std::swap(tiles[n], tiles[pos]);
  }
  
  return parity;
}

int main(int argc, char** argv)
{
    std::vector<int> blah = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 13};
    std::cerr << goodParity(blah) << std::endl;
    
    return 0;
}
