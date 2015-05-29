#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
using namespace std;
typedef std::pair<std::vector<unsigned>, std::vector<unsigned> > vec_pair;

bool sortingFunc(const pair<unsigned, vec_pair>& a, const pair<unsigned, vec_pair>& b)
{
  size_t fsize = a.second.second.size(); // size of second vector
  size_t ssize = a.second.first.size();
  size_t fbsize = b.second.second.size();
  size_t sbsize = b.second.first.size();
  return std::tie(fsize, a.second.second, ssize , a.second.first)
    < std::tie(fbsize, b.second.second, sbsize, b.second.first);
}

int main()
{
  vector<pair<unsigned, pair<vector<unsigned>, vector<unsigned> > > > sbp;
  std::vector<unsigned> vec1 = { 21, 33, 65 };
  std::vector<unsigned> vec2 = { 21, 33, 65, 76 }; // A
  sbp.emplace_back(std::make_pair(55, std::make_pair(vec1, vec2)));
  std::vector<unsigned> vec3 = { 21, 33, 65, 136};
  std::vector<unsigned> vec4 = { 21, 33, 46 }; // B
  sbp.emplace_back(std::make_pair(11, std::make_pair(vec3, vec4)));
  std::sort(sbp.begin(), sbp.end(), sortingFunc); // Swaps because of A and B
}