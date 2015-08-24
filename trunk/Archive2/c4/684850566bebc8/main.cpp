#include <vector>
#include <cstdio>

#define ARRAYTOJSON(x) arrayToJson<decltype(x)>(#x,x)

template<typename...>struct voider{using type = void;};
template<typename...Ts>using void_t = typename voider<Ts...>::type;

class A{
public:
    void test(){}
};

class B{
public:
    void test(){}
}; 


template <typename T, typename=void>
struct has_test : std::false_type{};
template <typename T>
struct has_test<T, void_t<decltype(std::declval<T>().test())>> : std::true_type{};

template <typename V>
inline void arrayToJson(const char* c, V& v) {
    arrayToJsonImpl(c,v,has_test<V>{});   
}

template <>
inline void arrayToJson(const char* c,int& v){
    printf("%s %d\n",c,v);
}

template<class V>
inline void arrayToJsonImpl(const char* c,V& v,std::false_type){
    typedef typename V::value_type E;
    for(typename std::vector<E>::iterator it=v.begin();it!=v.end();++it){
        arrayToJson(c,*it);
    }
}

template <typename V>
void arrayToJsonImpl(const char* c,V& v, std::true_type)
{
    (void)c;
    v.test();        
}

int main(){
    std::vector<int> v;
    v.push_back(5);
    ARRAYTOJSON(v);

    int i=0;
    ARRAYTOJSON(i);
    
    A a;
    B b;
    ARRAYTOJSON(a);
    ARRAYTOJSON(b);
    return 0;
}