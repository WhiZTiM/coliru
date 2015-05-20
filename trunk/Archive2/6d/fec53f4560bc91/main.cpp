#include <iostream>
#include <string>
#include <regex>
#include <functional>

#include <execinfo.h>

#include <cxxabi.h>

template <typename ...Args>
struct void_t
{
    using type = void;	
};

template <typename WrappedType>
class DebugWrapper
{
private:
	WrappedType VALUE;
	std::string NAME;
	mutable std::string CALLER;

public:
	DebugWrapper( WrappedType wrappedValue, const std::string& myName ):
		VALUE( wrappedValue ),
		NAME( myName )
	{
		updateCaller();
	}

	static std::string GetDemangledName(const std::string& str)
	{
		int status;
		char* buff = abi::__cxa_demangle(str.data(), 0, 0, &status);

		auto result = str;

		if( buff )
			result = std::string(buff);

		free(buff);

		return result;
	}

	static std::string GetMangledSymbol(const std::string& str)
	{
		static const std::regex regex(R"((\([a-zA-Z0-9_+]*\)))");

		std::smatch matches;
		std::regex_search( str, matches, regex );

		if( ! matches.empty() )
		{
			auto symbolName = matches[1].str().substr(1);
			auto pos = symbolName.find_first_of('+');

			if( pos == std::string::npos)
				return symbolName;

			symbolName.erase( pos );

			return symbolName;
		}

		return {};
	}

	void updateCaller() const
	{
		CALLER.clear();

		void* array[50] = { nullptr };
		char** strings = nullptr;

		size_t size = backtrace(array, 50);
		strings = backtrace_symbols(array, size);

		CALLER = GetDemangledName(GetMangledSymbol(strings[1]));

		if( CALLER == ")" )
			CALLER.clear();

        free(strings);
	}

	const DebugWrapper* operator->( ) const
	{
		updateCaller();
		return this;
	}

	DebugWrapper* operator->( )
	{
		updateCaller();
		return this;
	}

	operator DebugWrapper*(){ return nullptr; }
	static void operator delete(void* ptr, std::size_t size){}
	static void operator delete[](void* ptr, std::size_t size){}

#define WRAP_CONST_FUNCTION(name, enterLogging, exitLogging) 												\
		template <typename ...Args>																			\
		auto name(Args&&... args) const -> decltype(std::declval<WrappedType>().name(args...))				\
		{																									\
			updateCaller();																					\
																											\
			struct dummy																					\
			{																								\
				const char* const FUNCTION = nullptr;														\
				const std::string& CALLER;																	\
				const WrappedType& VALUE;																	\
																											\
				dummy(	const char* const input, 															\
						const std::string& caller,															\
						const WrappedType& value):															\
					FUNCTION(input), CALLER(caller), VALUE(value)						                 	\
				{																							\
					enterLogging;																			\
				}																							\
																											\
				~dummy()																					\
				{																							\
					exitLogging;																			\
				}																							\
			}dummy(#name, CALLER, VALUE);	                                                                \
																											\
			return VALUE.name(args...);																		\
		}

#define WRAP_COPY_BY_VALUE(logging)	\
	operator WrappedType() const 	\
	{								\
		updateCaller();				\
									\
		logging;					\
		return VALUE;				\
	}

#define WRAP_REF_ACCESS(logging)	\
	operator WrappedType()			\
	{								\
		updateCaller();				\
									\
		logging;					\
		return VALUE;				\
	}

#define WRAP_PTR_ACCESS(logging)									\
	operator typename std::remove_reference<WrappedType>::type*()	\
	{																\
		updateCaller();												\
																	\
		logging;													\
		return &VALUE;												\
	}

	WRAP_COPY_BY_VALUE( std::cout << "Copied " << NAME << " called by: " << CALLER << std::endl )
	WRAP_REF_ACCESS( std::cout << "RefAcccess " << NAME << " called by: " << CALLER << std::endl )
	WRAP_PTR_ACCESS( std::cout << "PtrAcccess " << NAME << " called by: " << CALLER << std::endl )


	WRAP_CONST_FUNCTION(getId,
						std::cout << "Entering: " << FUNCTION << " called by: " << CALLER << " id: " << VALUE.getId() << std::endl
						,
	 					std::cout << "Exitting: " << FUNCTION << " called by: " << CALLER << std::endl
	 					)

#undef WRAP_CONST_FUNCTION
#undef WRAP_COPY_BY_VALUE
#undef WRAP_REF_ACCESS
};

template <typename WrappedType>
bool operator!=(const DebugWrapper<WrappedType>&, std::nullptr_t)
{
	return true;
}

template <typename WrappedType>
bool operator==(const DebugWrapper<WrappedType>&, std::nullptr_t)
{
	return false;
}

class testCls
{
    public:
    int getId() const
    {
        return 42;
    }
};

int main()
{
    testCls t;
    DebugWrapper<testCls&> wrapped(t, "t");
    wrapped.getId();
}