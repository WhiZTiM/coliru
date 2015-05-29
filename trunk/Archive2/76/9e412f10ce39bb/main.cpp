#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
  vector<vector<unsigned> > sbp;
  vector<vector<unsigned> > sp;
  vector<vector<unsigned> >::iterator itSP = sp.begin();
  for (vector<vector<unsigned> >::iterator itSbp = sbp.begin(), lSbp = sbp.end(); itSbp != lSbp;)
  {
    if (std::lexicographical_compare(((*itSbp)).begin(), ((*itSbp)).end(), (*itSP).begin(), (*itSP).end()))
    {
      itSbp++;
    }
    else{
      if ((*itSbp) == (*itSP))
      {
        cout << (*itSbp) << "\n";
        itSbp++;
      }
      else{
        itSP++;
      }
    }
  }
}