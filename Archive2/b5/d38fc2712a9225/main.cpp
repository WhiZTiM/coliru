#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <initializer_list>

void fix_order(std::vector<std::vector<std::string>>& data, const std::vector<std::string>& correct) {

  std::size_t width = data[0].size();
  std::vector<int> order_idx(width);

  for (std::size_t i = 0; i < width; i++) {
    std::string tmp(data[0].at(i));
    auto pos = std::find(correct.begin(), correct.end(), tmp);
    order_idx[i] = std::distance(correct.begin(), pos);
  }

  for (std::size_t i = 0; i < data.size(); i++) {
    if (!data[i].empty()) {
      std::vector<std::string> q(width);

      for (unsigned int j = 0; j < width; j++) {
        int new_pos = order_idx[j];
        q[new_pos] = data[i].at(j);
      }
      std::swap(data[i], q);
    }
  }
}

void printvv(std::vector<std::vector<std::string>> x) {
  for (std::size_t i = 0; i < x.size(); i++) {
    for (auto elem : x[i]) {
      std::cout <<
        "\t" << elem;
    }
    std::cout <<
      "" << std::endl;
  }
}

int main(int argc, char** argv)
{
  std::size_t rows;
  if (argc < 2) {
    rows = 10;
  } else {
    rows = (std::size_t)std::stoi(argv[1]);
  }

  std::vector<std::vector<std::string>> data;
  data.emplace_back(std::initializer_list<std::string>{"second", "fourth", "first", "third"});
  for (std::size_t i = 1; i < rows; i++) {
    data.emplace_back(std::initializer_list<std::string>{"2nd", "4th", "1st", "3rd"});
  }

  std::vector<std::string> correct = {"first", "second", "third", "fourth"};
  std::cout <<
    "\nBefore:" << std::endl;
  printvv(data);

  fix_order(data, correct);
  std::cout <<
    "\nAfter:" << std::endl;
  printvv(data);

  return 0;
}
