#include <iostream>

struct dog
{
    static void make_sound()
	{
		std::cout << "woof woof\n";
	}
};

struct cat
{
	static void make_sound()
	{
		std::cout << "meow moew\n";
	}
};

template <typename R>
struct breeder
{
	void feed()
	{
		R::make_sound();
	}
};

int main()
{
    breeder<dog> dog_breeder;
    breeder<cat> cat_breeder;
    
    dog_breeder.feed();
    cat_breeder.feed();
}
