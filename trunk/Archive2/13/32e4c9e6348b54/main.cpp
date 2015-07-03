template<typename T>
struct PrintType;

int main()
{
	PrintType<decltype(throw "error")> a; 
}