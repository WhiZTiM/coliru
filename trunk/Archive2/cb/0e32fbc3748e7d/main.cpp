
constexpr auto pass(int n) -> decltype(n)
{
	return n;
}
 
template <int> struct bar {};
 
int main() 
{
	bar<5> t1; //ok
    bar<pass(5)> t2; //also ok 
	return 0;
}