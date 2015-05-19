#include <cstdint>

template <typename T> struct DataContent {
    const std::uint_fast16_t bytes = sizeof(T); 
    T *ptr;  

    // more stuff would go here but has been commented out for debug
};

template <typename T> struct Data : DataContent<T> {
public: 
    uint_fast64_t N=0;

    inline Data()  {};
    inline ~Data() { delete this->ptr; };

// ****************** PROBLEM METHOD LIVES HERE *******************
    inline Data &operator= (const T &rhs) { 
        for (uint_fast32_t n=0; n<N; n++ ) this->ptr[n] = rhs; 
        return *this; 
    };
// ****************************************************************

    // more stuff would go here but has been commented out for debug    
};

template class Data<float>;
template class Data<Data<float>>;

int main(){}