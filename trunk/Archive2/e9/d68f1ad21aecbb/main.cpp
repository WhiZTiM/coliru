#include <iostream>
#include <tuple>
#include <chrono> 

typedef std::chrono::high_resolution_clock clk;
typedef std::chrono::milliseconds ms;

int main() {
    clk c;
    
    auto t1 = c.now();
    
    std::tuple<int,int> mat3[25][25][25];
    
    for (size_t i = 0; i < 25; ++i) {
      for (size_t j = 0; j < 25; ++j) {
        for (size_t k = 0; k < 25; ++k) {
          mat3[i][j][k] = std::make_tuple(i*25*25+j*25+k, 10*(i*25*25+j*25+k));
        }
      }
    }
    
    for (size_t i = 0; i < 25; ++i) {
      for (size_t j = 0; j < 25; ++j) {
        for (size_t k = 0; k < 25; ++k) {
          std::cout << '(' << std::get<0>(mat3[i][j][k]) << ','
          << std::get<1>(mat3[i][j][k]) << ')' << '\n';
        }
      }
    }
      
    auto t2 = c.now();
    
    ms time_span = std::chrono::duration_cast<ms>(t2 - t1);
    std::cout << "In milliseconds: " << time_span.count() << std::endl;
    return 0;
}