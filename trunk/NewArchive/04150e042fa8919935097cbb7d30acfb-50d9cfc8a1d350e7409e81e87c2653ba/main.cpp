#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <list>



namespace tesla {
    
    template<typename T, size_t first, size_t... rest>
    struct multi_array {
        enum { dims = sizeof...(rest) };
        typedef std::array< typename multi_array<T, rest...>::type, first > type;
    };
    
    template<typename T, size_t first>
    struct multi_array<T,first>{
        enum { dims = 1 };
        typedef std::array<T,first> type;
    };
    
    template<class T, class U>
    struct is_same {
        enum { value = false };
    };
     
    template<class T>
    struct is_same<T, T> {
        enum { value = true };  
    };
    
    template<class T>
    struct is_integer {
        enum {value = is_same<T,int>::value };  
    };
    
    template<class T>
    struct is_bool {
        enum {value = is_same<T,bool>::value };  
    };
    
    template<class T>
    struct is_class {
        enum { value = false };
    };
     
    template<class T>
    struct is_class<int T::*> {
        enum { value = true };  
    };
    
};

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, std::array<T, N> arr) {

    os << "{";
    for(int i = 0; i < N - 1; i++)
        os << arr[i] << ", ";
    os << arr[N - 1];
    os << "}";
    return os;
}







template<typename T, size_t N>
void init(std::array<T,N>& arr) {
    for(int i = 0; i < arr.size(); i++)
        for(int j = 0; j < arr[i].size(); j++)
            for(int k = 0; k < arr[i][j].size(); k++)
                arr[i][j][k] = i + j + k;
}



int main()
{
    
using tesla::multi_array;
using std::endl;
using std::cout;
    
    multi_array<int,2,3,4>::type arr1;
    multi_array<int,3,4>::type arr2 = {};
        
    init(arr1);
    arr2[0] = arr1[0][0];
    arr1[1][2][0] = 9;
    std::cout << arr2 << std::endl;
    std::cout << arr1 << std::endl;
    
    // std::cout <<  arr1.dims << std::endl;
    
    std::cout << tesla::is_same<int*,int>::value;
    std::cout << tesla::is_bool<bool>::value;
    std::cout << tesla::is_class<bool>::value;
        
}


