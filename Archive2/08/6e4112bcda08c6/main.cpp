#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void test1(){
     std::cout << "bits per bool: " << std::numeric_limits<int>::digits << '\n';
  std::cout << " N\tN^2\tN^3\n";
  for (int i{1}; i != 21; ++i)
  {
     // write the loop body here
      std::cout << std::setw(2) << i << "\t" 
                << std::setw(3) << i*i << "\t" 
                << std::setw(4) << i*i*i<<'\n';
  }
    
}

void test2(){
   using namespace std;

  int day{14};
  int month{3};
  int year{2006};
  int dollars{42};
  int cents{7};
  // Print date in USA order. Later in the book, you will learn how to
  // handle internationalization.
  cout << "Date: " << setfill('0') << setw(2) << month
                            << '/' << setw(2) << day
                            << '/' << setw(2) << year << '\n';
  cout << "Pay to the order of: CASH\n";
  cout << "The amount of $" << setfill('*') << setw(8) << dollars << '.'
                            << setfill('0') << setw(2) << cents << '\n';   
}
void test3(){
  std::cout << '|' << std::setfill('*') << std::setw(6) <<  1234 << '|' << '\n';
  std::cout << '|' << std::left <<         std::setw(6) <<  1234 << '|' << '\n';
  std::cout << '|' <<                 std::setw(6) << -1234 << '|' << '\n';
  std::cout << '|' << std::right <<        std::setw(6) << -1234 << '|' << '\n';   
}

void test4(){
    using namespace std;
 cout.fill('0');
  cout.width(6);
  cout << 42 << '\n';
  cout.setf(ios_base::left, ios_base::adjustfield);
  cout.width(6);
  cout << 42 << '\n';
  cout << 42 << '\n';
  cout.fill('-');
  cout.width(4);
  cout << -42 << '\n';   
    
}

void exer1(){
    std::cout<<std::setw(4)  <<std::right<<'*'<< '|';
    //initial top frame
     for(int i{1}; i<11;++i)
        std::cout<< std::setw(4) << std::right << (i );
     //line
        std::cout <<'\n' <<std::setfill('-')<< std::right <<std::setw(5)<< '+';
        std::cout<<std::setfill('-')<<std::setw(31)<<' '<<std::endl;
    
    for(int i{0}; i<11;++i){
         std::cout<< std::setfill(' ') <<std::right<<std::setw(4)<<i << '|';
         for(int x{0}; x<11;++x){
           //td::cout<< std::setw(3) << 
         }
          std::cout<<std::endl;
    }
                
}
int main()
{
 /*
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
*/

  // Note that "digits" means binary digits, i.e., bits.
    //test1();
    //test2();
    //test4();
    exer1();
}
