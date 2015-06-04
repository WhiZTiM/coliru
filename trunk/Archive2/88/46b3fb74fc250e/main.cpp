#include <vector>
#include <cstdint>
#include <iomanip>
#include <iostream>

std::vector<std::uint8_t> decompress(const std::vector<std::uint8_t>& com)
{
  std::vector<std::uint8_t> decom;
  decom.reserve(com.size()); // a conservative estimate of the required size
  
  for(auto it = begin(com); it != end(com); ++it)
  {
    if(*it == 0xff)
    {
      ++it;
      if(it != end(com))
      {
        std::uint8_t number_of_repeats = *it;
        if(number_of_repeats <= 2)
        {
          std::fill_n(std::back_inserter(decom), number_of_repeats, 0xff);
          continue;
        }
        else
        {
          ++it;
          if(it != end(com))
            std::fill_n(std::back_inserter(decom), number_of_repeats, *it);
          else
            throw 42; // handle error in some way
        }
      }
      else 
        throw 42; // handle error in some way
    }
    else
      decom.push_back(*it);
  }
  return decom;
}
int main()
{
  std::vector<std::uint8_t> com{0x01, 0x02, 0x03, 0xff, 0x05, 0x04, 0xff, 0x0a, 0x05, 0xff, 0x00, 0xff, 0x01, 0xff, 0x02, 0xff, 0x03, 0x06};
  
  
  for(const auto& value : com)
    std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned short>(value) << ' ';
  std::cout << '\n';
  auto result = decompress(com);
  
  for(const auto& value : result)
    std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned short>(value) << ' ';
}
  