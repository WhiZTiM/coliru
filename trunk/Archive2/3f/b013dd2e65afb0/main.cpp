
#include <cstdint>
#include <type_traits>
#include <tuple>
#include <string>

namespace hSDK
{
    using string8 = std::string;
	using string = string8;
	using char_t = string::value_type;

	struct Impl;

	struct tuple_unpack final
	{
		template<int...> struct seq {};
		template<int N, int... S> struct gens : gens<N-1, N-1, S...> {};
		template<int... S> struct gens<0, S...>
		{
			using type = seq<S...>;
		};
	};

	enum struct ACE
	{
		Action,
		Condition,
		Expression
	};
	using ACE_ID_t = std::uint16_t;
	enum struct ExpressionType
	{
		None,
		Integer,
		Float,
		String
	};
}

#include <functional>
#include <map>

namespace hSDK
{
	struct Extension
	{
		virtual ~Extension() = 0;

		using string = hSDK::string;

	private:
		template<typename T, T...>
		struct ignore final
		{
			static constexpr bool value = true;
		};
		template<typename Fr, typename To>
		struct implicit_cast final
		{
			Fr const &f;
			implicit_cast(Fr const &from)
			: f(from)
			{
			}
			operator To() const
			{
				return static_cast<To>(f);
			}
		};

		template<typename T, typename = void>
		struct Enforce32bit final
		{
			using type = T;
			static ExpressionType constexpr ExpT = ExpressionType::None;
		};
		template<typename T>
		struct Enforce32bit
		<
			T, typename std::enable_if
			<
				std::is_same<decltype(T::ExpT), ExpressionType>::value,
				void
			>::type
		> final
		{
			using type = T;
			using fr32 = T;
			static ExpressionType constexpr ExpT = T::ExpT;
		};
		template<typename T>
		struct Enforce32bit
		<
			T, typename std::enable_if
			<
				sizeof(T) == 4
				&& !std::is_floating_point<T>::value
				&& !std::is_integral<T>::value
				&& !std::is_same<T, char_t *>::value
				&& std::is_pod<T>::value
				&& !std::is_reference<T>::value,
				void
			>::type
		> final
		{
			struct reinterpret_to32 final
			{
				T t;
				reinterpret_to32(T const &from)
				: t(from)
				{
				}
				operator std::int32_t() const
				{
					return reinterpret_cast<std::int32_t>(t);
				}
			};
			struct reinterpret_fr32 final
			{
				std::int32_t i;
				reinterpret_fr32(std::int32_t i32)
				: i(i32)
				{
				}
				operator T() const
				{
					return reinterpret_cast<T>(i);
				}
			};
			using type = T;
			using to32 = reinterpret_to32;
			using fr32 = reinterpret_fr32;
			static ExpressionType constexpr ExpT = ExpressionType::None;
		};
		template<typename T>
		struct Enforce32bit<string, T> final
		{
			struct implicit_to32 final
			{
				string const s;
				implicit_to32(string const &str)
				: s(str)
				{
				}
				operator std::int32_t() const
				{
					return reinterpret_cast<std::int32_t>(CopyString(s));
				}
			};
			struct implicit_fr32 final
			{
				string const s;
				implicit_fr32(std::int32_t i32)
				: s(reinterpret_cast<char_t const *>(i32))
				{
				}
				operator string() const
				{
					return s;
				}
			};
			using type = string;
			using to32 = implicit_to32;
			using fr32 = implicit_fr32;
			static ExpressionType constexpr ExpT = ExpressionType::String;
		};
		template<typename T>
		struct Enforce32bit
		<
			T, typename std::enable_if
			<
				std::is_integral<T>::value,
				void
			>::type
		> final
		{
			using type = T;
			using to32 = implicit_cast<T, std::int32_t>;
			using fr32 = implicit_cast<std::int32_t, T>;
			static ExpressionType constexpr ExpT = ExpressionType::Integer;
		};
		template<typename T>
		struct Enforce32bit
		<
			T, typename std::enable_if
			<
				std::is_floating_point<T>::value,
				void
			>::type
		> final
		{
			struct implicit_to32 final
			{
				float f;
				implicit_to32(T t)
				: f(static_cast<float>(t))
				{
				}
				operator std::int32_t()
				{
					return *reinterpret_cast<std::int32_t *>(&f);
				}
			};
			struct implicit_fr32 final
			{
				float f;
				implicit_fr32(std::int32_t i)
				: f(*reinterpret_cast<float *>(&i))
				{
				}
				operator T()
				{
					return static_cast<T>(f);
				}
			};
			using type = T;
			using to32 = implicit_to32;
			using fr32 = implicit_fr32;
			static ExpressionType constexpr ExpT = ExpressionType::Float;
		};
		template<typename R, typename = void>
		struct safe_return final
		{
			std::function<R()> f;
			safe_return(std::function<R()> func)
			: f(func)
			{
			}
			operator std::int32_t()
			{
				return typename Enforce32bit<R>::to32(f());
			}
		};
		template<typename R>
		struct safe_return<void, R> final
		{
			std::function<void()> f;
			safe_return(std::function<void()> func)
			: f(func)
			{
			}
			operator std::int32_t()
			{
				return f(), 0;
			}
		};

		template<typename Base, typename Derived>
		using base_check = typename std::enable_if
		<
			std::is_base_of<Base, Derived>::value,
			Derived
		>::type;

		template<typename ExtT, typename R, typename... Args>
		using ExtMFP_helper = R (ExtT::*)(Args...);

	public:
		template<typename ExtT, typename R, typename... Args>
		using ExtMFP = ExtMFP_helper
		<
			base_check<Extension, ExtT>,
			typename std::conditional<std::is_void<R>::value, std::common_type<R>, Enforce32bit<R>>::type::type,
			typename Enforce32bit<Args>::type...
		>;

		template<ACE CallT, ACE = CallT>
		struct Forwarder_t_helper final
		{
			using type = std::function
			<
				std::int32_t(Extension &ext, std::int32_t param1, std::int32_t param2)
			>;
		};
		template<ACE CallT>
		using Forwarder_t = typename Forwarder_t_helper<CallT>::type;
		template<ACE CallT>
		struct ExtMF
		: Forwarder_t<CallT>
		{
			template<typename ExtT, typename R, typename... Args>
			ExtMF(R(ExtT::*mfp)(Args...))
			: Forwarder_t<CallT>
			(
				translator<ExtT, caller<ExtT, R, Args...>, std::int32_t, std::int32_t>
				(
					caller<ExtT, R, Args...>
					(
						verify<ExtT, R, Args...>(mfp)
					)
				)
			)
			{
			}
			ExtMF(ExtMF const &) = default;
			ExtMF(ExtMF &&) = default;
			ExtMF &operator=(ExtMF const &) = default;
			ExtMF &operator=(ExtMF &&) = default;

		private:
			template<typename ExtT, typename R, typename... Args>
			static auto verify(R(ExtT::*mfp)(Args...))
			-> typename std::enable_if
			<
				(CallT == ACE::Action) == (std::is_void<R>::value),
				ExtMFP<ExtT, R, Args...>
			>::type
			{
				return mfp;
			}
			template<typename ExtT, typename func, typename... Args>
			struct translator final
			{
				func f;
				translator(func fun)
				: f(fun)
				{
				}
				std::int32_t operator()(Extension &ext, Args... args)
				{
					return f(*static_cast<ExtT *>(&ext), args...);
				}
			};

			template<typename ExtT, typename R, typename... Args>
			struct caller final
			{
				static std::size_t constexpr I = sizeof...(Args);
				ExtMFP<ExtT, R, Args...> mfp;
				caller(ExtMFP<ExtT, R, Args...> mf)
				: mfp(mf)
				{
				}

				template<std::size_t, ExpressionType ExpT>
				struct GetParam final
				{
					std::int32_t p;
					GetParam()
					: p(0)
					{
					}
					operator std::int32_t()
					{
						return p;
					}
				};
				template<ExpressionType ExpT>
				struct GetParam<0, ExpT> final
				{
					std::int32_t p;
					GetParam()
					: p(0)
					{
					}
					operator std::int32_t()
					{
						return p;
					}
				};


				template<std::size_t J>
				auto tuple_gen()
				{
					return std::tuple<>{};
				}
				template<std::size_t J, typename First, typename... Rest>
				auto tuple_gen()
				{
					return std::tuple_cat
					(
						std::make_tuple<typename Enforce32bit<First>::fr32>
						(static_cast<typename Enforce32bit<First>::fr32>(GetParam<J, Enforce32bit<First>::ExpT>())),
						tuple_gen<J+1, Rest...>()
					);
				}

				template<int... S>
				auto call(ExtT &ext, tuple_unpack::seq<S...>)
				-> typename std::enable_if
				<
					!std::is_same<R, void>::value && ignore<int, S...>::value,
					Enforce32bit<R>
				>::type::to32
				{
					auto params = tuple_gen<0, Args...>();
					return (ext.*mfp)(std::get<S>(params)...);
				}
				template<int... S>
				auto call(ExtT &ext, tuple_unpack::seq<S...>)
				-> typename std::enable_if
				<
					std::is_same<R, void>::value && ignore<int, S...>::value,
					std::int32_t
				>::type
				{
					auto params = tuple_gen<0, Args...>();
					return (ext.*mfp)(std::get<S>(params)...), 0;
				}

				std::int32_t operator()(ExtT &ext, std::int32_t)
				{
					return (*this)(ext, 0, 0);
				}
				std::int32_t operator()(ExtT &ext, std::int32_t, std::int32_t)
				{
					return call(ext, typename tuple_unpack::gens<I>::type());
				}
			};
			template<typename ExtT, typename R>
			struct caller<ExtT, R> final
			{
				ExtMFP<ExtT, R> mfp;
				caller(ExtMFP<ExtT, R> mf)
				: mfp(mf)
				{
				}

				std::int32_t operator()(ExtT &ext, std::int32_t)
				{
					return safe_return<R>([&]()->R { return (ext.*mfp)(); });
				}
				std::int32_t operator()(ExtT &ext, std::int32_t, std::int32_t)
				{
					return safe_return<R>([&]()->R { return (ext.*mfp)(); });
				}
			};
			template<typename ExtT, typename R, typename Arg1>
			struct caller<ExtT, R, Arg1> final
			{
				ExtMFP<ExtT, R, Arg1> mfp;
				caller(ExtMFP<ExtT, R, Arg1> mf)
				: mfp(mf)
				{
				}

				std::int32_t operator()(ExtT &ext, std::int32_t)
				{
					std::int32_t param1 = 0;
					return safe_return<R>([&]() -> R
					{
						return (ext.*mfp)
						(
							typename Enforce32bit<Arg1>::fr32(param1)
						);
					});
				}
				std::int32_t operator()(ExtT &ext, std::int32_t param1, std::int32_t)
				{
					return safe_return<R>([&]() -> R
					{
						return (ext.*mfp)
						(
							typename Enforce32bit<Arg1>::fr32(param1)
						);
					});
				}
			};
			template<typename ExtT, typename R, typename Arg1, typename Arg2>
			struct caller<ExtT, R, Arg1, Arg2> final
			{
				ExtMFP<ExtT, R, Arg1, Arg2> mfp;
				caller(ExtMFP<ExtT, R, Arg1, Arg2> mf)
				: mfp(mf)
				{
				}

				std::int32_t operator()(ExtT &ext, std::int32_t param1, std::int32_t param2)
				{
					return safe_return<R>([&]() -> R
					{
						return (ext.*mfp)
						(
							typename Enforce32bit<Arg1>::fr32(param1),
							typename Enforce32bit<Arg2>::fr32(param2)
						);
					});
				}
				std::int32_t operator()(ExtT &ext, std::int32_t)
				{
					std::int32_t param1 = 0;
					std::int32_t param2 = 0;
					return safe_return<R>([&]() -> R
					{
						return (ext.*mfp)
						(
							typename Enforce32bit<Arg1>::fr32(param1),
							typename Enforce32bit<Arg2>::fr32(param2)
						);
					});
				}
			};
		};

		using ActionMF = ExtMF<ACE::Action>;
		using ConditionMF = ExtMF<ACE::Condition>;
		using ExpressionMF = ExtMF<ACE::Expression>;
		using ACE_ID_t = ::hSDK::ACE_ID_t;
		using Actions_t = std::map<ACE_ID_t, ActionMF>;
		using Conditions_t = std::map<ACE_ID_t, ConditionMF>;
		using Expressions_t = std::map<ACE_ID_t, ExpressionMF>;
	protected:
		Extension()
		{
		}

		void registerActions(Actions_t a)
		{
			a.insert(std::begin(actions), std::end(actions));
			actions.swap(a);
		}

	private:
		Actions_t actions;

		static string::const_pointer CopyString(string const &s) { return nullptr; }

		Extension(Extension const &) = delete;
		Extension(Extension &&) = delete;
		Extension &operator=(Extension const &) = delete;
		Extension &operator=(Extension &&) = delete;

		friend struct ::hSDK::Impl;
	};
	inline Extension::~Extension() = default;
}

struct TestExtension
: hSDK::Extension
{
	void A0(){}

	TestExtension()
	{
		registerActions({{7, &TestExtension::A0}});
	}
};

#include <iostream>

int main()
{
	TestExtension te;
	std::cout << "Success" << std::endl;
}
