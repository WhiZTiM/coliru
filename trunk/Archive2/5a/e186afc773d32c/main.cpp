template<typename T>
struct Test
{
    struct Context
	{
		template<int id, bool = true>
		struct table
		{
		};

		enum { index = 0 };

		template<bool u>
		struct table<index, u> : public table<index-1, u>
		{
			int value;
		};
	};
};

int main()
{
	Test<double>::Context::table<0> t;
	t.value = 42;
	(void)t;
}
