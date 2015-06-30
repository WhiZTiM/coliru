#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
  int id;
  int solved;
  int time;

  Item(int id, int solved, int time)
    : id(id), solved(solved), time(time)
  { }

  bool operator<(const Item& other) const {
    if(solved > other.solved) {
      return true;
    }
    if(solved == other.solved) {
      if(time < other.time) {
        return true;
      }
      if(time == other.time) {
        if(id < other.id)
          return true;
      }
    }

    return false;
  }
};

std::ostream& operator<<(std::ostream& o, const Item& obj) {
  o << "Team " << obj.id << " solved " <<
      obj.solved << " in " << obj.time << " time unit.";
  return o;
}

int main(void) {
  std::vector<Item> item = {
      // id  solve  time
    Item(2,  2,     400),
    Item(4,  4,     200),
    Item(5,  2,     400),
    Item(1,  2,     140),
    Item(3,  5,     400),
  };

  std::sort(item.begin(), item.end());

  std::vector<Item>::const_iterator it;

  for(auto i : item)
    std::cout << i << std::endl;

  return 0;
}