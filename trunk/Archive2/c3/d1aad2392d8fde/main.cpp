    namespace Test
    {
        struct A {};
        void foo( A _a ) {}
    }


    int main( int, char** )
    {
        foo( Test::A() ); // 1. why foo doesn't require Test:: ?
    	Test::foo( A() ); // 2. why A() requires Test:: considering above line?

    	return 0;
    }