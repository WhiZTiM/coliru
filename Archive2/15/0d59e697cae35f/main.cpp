#include <ctime>
#include <iostream>

using namespace std;

int main()
{
  time_t curr = time(nullptr);
  tm prts = *localtime(&curr);

  cout << "Date : "         << prts.tm_mday <<endl
       << "Week Day : "     << prts.tm_wday <<endl
       << "Month : "        << prts.tm_mon + 1 <<endl
       << "Year : "         << prts.tm_year + 1900 <<endl;

  prts.tm_mday += 10;
  mktime(&prts);
  cout<<endl;

  cout << "After 7 days : " << endl;
  cout << "Date : "         << prts.tm_mday <<endl
       << "Week Day : "     << prts.tm_wday <<endl
       << "Month : "        << prts.tm_mon + 1 <<endl
       << "Year : "         << prts.tm_year + 1900 <<endl;

  return 0;
}
