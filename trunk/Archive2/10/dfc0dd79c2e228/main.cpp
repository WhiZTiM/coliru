#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <type_traits>

using namespace std;

int main()
{
    vector<string> ar = {"mnciitbhu"};
    cout<<boolalpha;
    cout<<"First case : "<<endl;
    for(const auto& x : ar)
    {
        // Using std::remove_const and std::remove_reference
        // at the same time
        typedef typename std::remove_const<
            typename std::remove_reference<decltype(x)>::type>::type TT;
        cout<<std::is_same<std::string, TT>::value<<endl;
        cout<<std::is_same<const std::string, TT>::value<<endl;
        cout<<std::is_same<const std::string&, TT>::value<<endl;
    }
    cout<<endl;
    cout<<"Second case : "<<endl;
    for(const auto& x : ar)
    {
        // Same as above but the order of using std::remove_reference
        // and std::remove_const changed
        typedef typename std::remove_reference<
            typename std::remove_const<decltype(x)>::type>::type TT;
        cout<<std::is_same<std::string, TT>::value<<endl;
        cout<<std::is_same<const std::string, TT>::value<<endl;
        cout<<std::is_same<const std::string&, TT>::value<<endl;
    } 
    return 0;
}
