#include <string>
#include <chrono>
#include <iostream>
#include <cassert>

std::chrono::duration<double> append(std::size_t size) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::string str;
  str.reserve(size);
  for (int i = 0; i < size; ++i) str.append("a");
  assert(str.size() == size);

  end = std::chrono::system_clock::now();
  return end - start;
};

std::chrono::duration<double> push_back(std::size_t size) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::string str;
  str.reserve(size);
  for (int i = 0; i < size; ++i) str.push_back('a');
  assert(str.size() == size);

  end = std::chrono::system_clock::now();
  return end - start;
};

std::chrono::duration<double> plus(std::size_t size) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::string str;
  str.reserve(size);
  for (int i = 0; i < size; ++i) str += 'a';
  assert(str.size() == size);

  end = std::chrono::system_clock::now();
  return end - start;
};

std::chrono::duration<double> plus_string(std::size_t size) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::string str;
  str.reserve(size);
  for (int i = 0; i < size; ++i) str += "a";
  assert(str.size() == size);

  end = std::chrono::system_clock::now();
  return end - start;
};

void test(std::size_t size) {
  std::cerr << std::endl;
  std::cerr << "Tests with size " << size << std::endl;
  std::cerr << "append()" << std::endl;
  std::cerr << "elapsed time: " << append(size).count() << "s" << std::endl;
  std::cerr << "push_back()" << std::endl;
  std::cerr << "elapsed time: " << push_back(size).count() << "s" << std::endl;
  std::cerr << "plus()" << std::endl;
  std::cerr << "elapsed time: " << plus(size).count() << "s" << std::endl;
  std::cerr << "plus_string()" << std::endl;
  std::cerr << "elapsed time: " << plus_string(size).count() << "s" << std::endl;
};

int main() {
  test(10000);
  test(100000);
  test(1000000);
};