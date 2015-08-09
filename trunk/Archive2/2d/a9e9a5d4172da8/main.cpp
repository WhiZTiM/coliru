#include<cstdio>
int i=0;
void f(int b)
{
    std::printf("i=%d\tb=%d\n\n",i,b);
}
template<typename T>
T my_ipp(T &i)
{
	const auto temp(i);
	++i;
	return temp;
}
int main()
{
	i=0;
	f(i++);
	i=0;
	f(i);
	i=0;
	f(my_ipp(i));
}