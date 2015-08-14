#include <map>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <typeindex>
#include <vector>

// first of all we need a registy where we can fetch arguments of all types from
class argument_registry
{
public:
    // register a range of arguments of type T
	template <class T, class Iterator>
	void register_range(Iterator begin, Iterator end)
	{
		// enclose the range in a argument_range object and put it in our map
		m_registry.emplace(typeid(T), std::make_unique<argument_range<T, Iterator>>(begin, end));
	}

	template <class T>
	const T& get_argument(size_t idx) const
	{
		// check if we have a registered range for this type
		auto itr = m_registry.find(typeid(T));
		if (itr == m_registry.end())
		{
			throw std::invalid_argument("no arguments registered for this type");
		}
		
		// we are certain about the type, so downcast the argument_range object and query the argument
		auto range = static_cast<const argument_range_base1<T>*>(itr->second.get());
		return range->get(idx);
	}

private:
	// base class so we can delete the range objects properly
	struct argument_range_base0
	{
		virtual ~argument_range_base0(){};
	};

	// interface for querying arguments
	template <class T>
	struct argument_range_base1 : argument_range_base0
	{
		virtual const T& get(size_t idx) const = 0;
	};

	// implements get by queyring a registered range of arguments
	template <class T, class Iterator>
	struct argument_range : argument_range_base1<T>
	{
		argument_range(Iterator begin, Iterator end)
			: m_begin{ begin }, m_count{ size_t(std::distance(begin, end)) } {}

		const T& get(size_t idx) const override
		{
			if (idx >= m_count)
				throw std::invalid_argument("argument index out of bounds");

			auto it = m_begin;
			std::advance(it, idx);
			return *it;
		}

		Iterator m_begin;
		size_t m_count;
	};

	std::map<std::type_index, std::unique_ptr<argument_range_base0>> m_registry;
};

// an argument_index is a combination of type and index
typedef std::pair<std::type_index, size_t> argument_index;

// helper function for creating an argument_index
template <class T>
argument_index arg(size_t idx)
{
	return{ typeid(T), idx };
}

// helper trait for call function; called when there are unhandled arguments left
template <bool Done>
struct call_helper
{
	template <class FuncRet, class ArgTuple, size_t N, class F, class... ExpandedArgs>
	static FuncRet call(F func, const argument_registry& registry, const std::vector<argument_index>& args, ExpandedArgs&&... expanded_args)
	{
		// check if there are any arguments left in the passed vector
		if (N == args.size())
		{
			throw std::invalid_argument("not enough arguments");
		}

		// get the type of the Nth argument
		typedef typename std::tuple_element<N, ArgTuple>::type arg_type;

		// check if the type matches the argument_index from our vector
		if (std::type_index{ typeid(arg_type) } != args[N].first)
		{
			throw std::invalid_argument("argument of wrong type");
		}

		// query the argument from the registry
		auto& arg = registry.get_argument<arg_type>(args[N].second);

		// add the argument to the ExpandedArgs pack and continue the recursion with the next argument N + 1
		return call_helper<std::tuple_size<ArgTuple>::value == N + 1>::template call<FuncRet, ArgTuple, N + 1>(func, registry, args, std::forward<ExpandedArgs>(expanded_args)..., arg);
	}
};

// helper trait for call function; called when there are no arguments left
template <>
struct call_helper<true>
{
	template <class FuncRet, class ArgTuple, size_t N, class F, class... ExpandedArgs>
	static FuncRet call(F func, const argument_registry&, const std::vector<argument_index>& args, ExpandedArgs&&... expanded_args)
	{
		if (N != args.size())
		{
			// unexpected arguments in the vector
			throw std::invalid_argument("too many arguments");
		}

		// call the function with all the expanded arguments
		return func(std::forward<ExpandedArgs>(expanded_args)...);
	}
};

// call function can only work on "real", plain functions
// as you could never do dynamic overload resolution in C++
template <class Ret, class... Args>
Ret call(Ret(*func)(Args...), const argument_registry& registry, const std::vector<argument_index>& args)
{
	// put the argument types into a tuple for easier handling
	typedef std::tuple<Args...> arg_tuple;

	// start the call_helper recursion
	return call_helper<sizeof...(Args) == 0>::template call<Ret, arg_tuple, 0>(func, registry, args);
}

// example function
int foo(int i, const double& d, const char* str)
{
    printf("called foo with %d, %f, %s", i, d, str);
	// return something
	return 0;
}

int main()
{
	// prepare some arguments
	std::vector<int> ints = { 1, 2, 3 };
	std::vector<double> doubles = { 10., 20., 30. };
	std::vector<const char*> str = { "alpha", "bravo", "charlie" };

	// register them
	argument_registry registry;
	registry.register_range<int>(ints.begin(), ints.end());
	registry.register_range<double>(doubles.begin(), doubles.end());
	registry.register_range<const char*>(str.begin(), str.end());

	// call function foo with arguments from the registry
	return call(foo, registry, {arg<int>(2), arg<double>(0), arg<const char*>(1)});
}