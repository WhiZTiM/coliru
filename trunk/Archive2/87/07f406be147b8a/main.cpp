struct foo
{
    int test(int) { return 0; }
};
 
constexpr auto pass(int (foo::* f)(int)) -> decltype(f)
{
	return f;
}
 
template <int(foo::* F)(int)> struct bar {};
 
int main() 
{
	bar<&foo::test> t1; //ok
    //this doesn't compile:
    //bar<pass(&foo::test)> t2; 
	return 0;
}