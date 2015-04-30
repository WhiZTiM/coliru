#include <atomic>
#include <thread>
#include <iostream>

int main() {
  uint32_t cnt = 0;
  for (int i=0; i<1000; i++) {
    std::atomic<bool> loop(true);
    std::thread th([&]{while(loop) cnt++;});
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    loop = false;
    th.join();
    cnt = ((cnt << 7) + (cnt >> 7)) ^ cnt;
  }
  
  std::cout << cnt << std::endl;

  return 0;
}
