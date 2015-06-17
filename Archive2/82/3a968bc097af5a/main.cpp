#include <iostream>
#include <tuple>
#include <array>
#include <chrono> 

typedef std::chrono::high_resolution_clock clk;
typedef std::chrono::milliseconds ms;

int main() {
    clk c;
    
    auto t1 = c.now();
    
    std::array<
      std::array<
        std::array<std::tuple<int, int>,
        50>,
      50>,
    50> mat3;
    
    for (size_t i = 0; i < 50; ++i) {
      for (size_t j = 0; j < 50; ++j) {
        for (size_t k = 0; k < 50; ++k) {
          mat3[i][j][k] = std::make_tuple(i*50*50+j*50+k, 10*(i*50*50+j*50+k));
        }
      }
    }
    
    for (size_t i = 0; i < 50; ++i) {
      for (size_t j = 0; j < 50; ++j) {
        for (size_t k = 0; k < 50; ++k) {
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