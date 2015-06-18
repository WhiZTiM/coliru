#include <iterator>
#include <utility>
#include <memory>
#include <vector>
#include <iostream>

      template<class T>
      struct input_iterator:
        std::iterator<
          std::input_iterator_tag, // category
          T, // value
          std::ptrdiff_t, // distance
          T*, // pointer
          T // reference
        >
      {
        struct erase {
          virtual void advance() = 0;
          virtual erase* clone() const = 0;
          virtual T get() const = 0;
          virtual bool equal(erase const& o) = 0;
          virtual ~erase() {}
        };
        std::unique_ptr<erase> pimpl;
        input_iterator(input_iterator&&)=default;
        input_iterator()=default;
        input_iterator& operator++() {
          pimpl->advance();
          return *this;
        }
        input_iterator operator++(int) {
          auto copy = *this;
          ++*this;
          return copy;
        }
        input_iterator(input_iterator const& o):
          pimpl(o.pimpl?o.pimpl->clone():nullptr)
        {}
        T operator*() const {
          return pimpl->get();
        }
        friend bool operator==( input_iterator const& lhs, input_iterator const& rhs ) {
          return lhs.pimpl->equal(*rhs.pimpl);
        }
        friend bool operator!=( input_iterator const& lhs, input_iterator const& rhs ) {
          return !(lhs==rhs);
        }
        template<class It>
        struct impl:erase{
          It it;
          impl(impl const&)=default;
          impl(It in):it(std::move(in)){}
          virtual void advance() override { ++it; }
          virtual erase* clone() const override { return new impl(*this); }
          virtual T get() const override { return *it; }
          virtual bool equal(erase const& o) override {
            return static_cast<impl const&>(o).it == it;
          }
        };

        template<
          class It,
          class=std::enable_if<
            std::is_convertible<
              typename std::iterator_traits<It>::reference,
              T
            >{}
          >
        >
        input_iterator(It it):pimpl( new impl<It>{it} ) {}
      }; // input_iterator

     template<class It>
     struct range {
       It b; It e;
       It begin() const { return b; }
       It end() const { return e; }

       range() = default;

       range(It start, It finish):b(std::move(start)),e(std::move(finish)) {};

       range(range&&)=default;
       range(range const&)=default;
       range& operator=(range&&)=default;
       range& operator=(range const&)=default;

       template<class R,
         class R_It=std::decay_t<decltype(std::begin(std::declval<R>()))>,
         class=std::enable_if< std::is_convertible<R_It, It>{} >
       >
       range( R&& r ):
         range(std::begin(r), std::end(r))
       {} // TODO: enable ADL begin lookup
     };

    template<class T>
    using sequence_of = range<input_iterator<T>>;

int main()
{
    std::vector<int> a = {1,2,3};
    sequence_of<int> s = a;
    for (auto x:s)
        std::cout << x << '\n';
}
