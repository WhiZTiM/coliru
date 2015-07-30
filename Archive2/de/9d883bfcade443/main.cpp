#include <array>
#include <cstddef>
#include <cstring>
#include <iostream>

namespace my
{

  namespace detail
  {

    template <typename CharT>
    constexpr auto
    strlen_c(const CharT *const string) noexcept
    {
      auto count = static_cast<std::size_t>(0);
      for (auto s = string; *s; ++s)
        ++count;
      return count;
    }

    template <std::size_t N, std::size_t M, typename CharT>
    struct truncation_helper
    {
      template <typename... CharTs>
      static constexpr auto
      help(const CharT *const string, const std::size_t length, const CharTs... chars) noexcept
      {
        static_assert(sizeof...(chars) == M, "wrong instantiation");
        const auto c = (length > M) ? string[M] : static_cast<CharT>(0);
        return truncation_helper<N, M + 1, CharT>::help(string, length, chars..., c);
      }
    };

    template <std::size_t N, typename CharT>
    struct truncation_helper<N, N, CharT>
    {
      template <typename... CharTs>
      static constexpr auto
      help(const CharT *, const std::size_t, const CharTs... chars) noexcept
      {
        static_assert(sizeof...(chars) == N, "wrong instantiation");
        
#ifdef WORK
        return std::array<CharT, N + 1>{{ chars..., static_cast<CharT>(0) }};
#else
        std::array<CharT, N + 1> result{{ chars..., static_cast<CharT>(0) }};
        return result;
#endif
      }
    };

  }  // namespace detail

  template <std::size_t N, typename CharT>
  constexpr auto
  truncate(const CharT *const string) noexcept
  {
    const auto length = detail::strlen_c(string);
    return detail::truncation_helper<N, 0, CharT>::help(string, length);
  }

}  // namespace my

#ifndef SOMETEXT
#  define SOMETEXT "example"
#endif

namespace /* anonymous */
{
  constexpr auto limit = static_cast<std::size_t>(8);
  /*constexpr*/ auto text = my::truncate<limit>(SOMETEXT);
}

int
main()
{
  std::printf("text = \"%s\"\n", text.data());
  std::printf("len(text) = %lu <= %lu\n", std::strlen(text.data()), limit);
  //std::printf("text = \"%s\"\n", my::truncate<4>(SOMETEXT).data());
}
