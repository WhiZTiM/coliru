class X {
public:
    static void test();
private:
	char *ptr;
};

void X::test()
{
	auto v = [](){
		sizeof (*ptr);
	};
}

int main() {
    return 0;
}