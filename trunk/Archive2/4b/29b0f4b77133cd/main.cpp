    int main()
	{
		static_assert( alignof( int * ) == alignof( int * * ), "nope" );

		const int * * a = nullptr;
		const int * * * b = reinterpret_cast< const int * * * >( a );
		auto c = static_cast< const int * * * >( static_cast< void * >( a ) );
		return 0;
	}
