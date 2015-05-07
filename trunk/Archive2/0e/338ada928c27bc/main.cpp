#include <memory>
#include <vector>

struct SillyMap
{
  SillyMap &operator += (const SillyMap &rhs) &&;
  SillyMap &operator += (SillyMap rhs) &;
  
  std::vector<int> m_keys;
  std::vector<double> m_values;
};

SillyMap operator + (SillyMap lhs, const SillyMap &rhs);

/*
 * Definitions
 */

SillyMap &SillyMap::operator += (const SillyMap &rhs) &&
{
  m_keys.insert (m_keys.end (), rhs.m_keys.begin (), rhs.m_keys.end ());
  m_values.insert (m_values.end (), rhs.m_values.begin (), rhs.m_values.end ());
  return *this;
}

SillyMap &SillyMap::operator += (SillyMap rhs) &
{
  // Assuming addition is commuative. Otherwise we have to do something slightly more painful.
  return *this = std::move (rhs) + *this;
}

SillyMap operator + (SillyMap lhs, const SillyMap &rhs)
{
  std::move (lhs) += rhs;
  return lhs;
}

int main () { }