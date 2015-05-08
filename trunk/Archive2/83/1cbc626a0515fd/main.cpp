#include <iostream>
#include <string>
#include <vector>

template<class _Container>
auto inline size(_Container& _Cont) -> decltype(_Cont.size())
{
	return (_Cont.size());
}

template<class _Ty, size_t _Size>
auto inline size(_Ty (&_Array)[_Size])
{ 
	return (_Size);
}


int main()
{
    std::vector<int> a(5);
    int b[6];
    
    printf("vec= %d\n", (int)size(a));
    printf("arr= %d", (int)size(b));
}
