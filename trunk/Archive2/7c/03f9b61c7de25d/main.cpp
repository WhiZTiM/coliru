#include <range/v3/all.hpp>
#include <functional>
#include <iostream>
#include <vector>

namespace ranges
{
    inline namespace v3
    {
        /// \addtogroup group-actions
        /// @{
        namespace action
        {
            struct random_shuffle_fn
            {
            private:
                friend action_access;
                
                static auto bind(random_shuffle_fn random_shuffle)
                RANGES_DECLTYPE_AUTO_RETURN
                (
                    std::bind(random_shuffle, std::placeholders::_1)
                )
                
                template<typename Gen>
                static auto bind(random_shuffle_fn random_shuffle, Gen && rand)
                RANGES_DECLTYPE_AUTO_RETURN
                (
                    std::bind(random_shuffle, std::placeholders::_1, bind_forward<Gen>(rand))
                )
            public:
                struct ConceptImpl
                {
                    template<typename Rng,
                        typename I = range_iterator_t<Rng>>
                    auto requires_(Rng&&) -> decltype(
                        concepts::valid_expr(
                            concepts::model_of<concepts::RandomAccessRange, Rng>(),
                            concepts::is_true(Permutable<I>())
                        ));
                };

                template<typename Rng>
                using Concept = concepts::models<ConceptImpl, Rng>;

                template<typename Rng,
                    CONCEPT_REQUIRES_(Concept<Rng>())>
                Rng operator()(Rng && rng) const
                {
                    ranges::random_shuffle(rng);
                    return std::forward<Rng>(rng);
                }

                template<typename Rng, typename Gen,
                    CONCEPT_REQUIRES_(Concept<Rng>())>
                Rng operator()(Rng && rng, Gen && rand) const
                {
                    ranges::random_shuffle(rng, std::forward<Gen>(rand));
                    return std::forward<Rng>(rng);
                }
                
                #ifndef RANGES_DOXYGEN_INVOKED
                template<typename Rng,
                    CONCEPT_REQUIRES_(!Concept<Rng>())>
                void operator()(Rng &&) const
                {
                    CONCEPT_ASSERT_MSG(RandomAccessRange<Rng>(),
                        "The object on which action::random_shuffle operates must be a model of the "
                        "RandomAccessRange concept.");
                    using I = range_iterator_t<Rng>;
                    CONCEPT_ASSERT_MSG(Permutable<I>(),
                        "The iterator type of the range passed to action::random_shuffle must allow its "
                        "elements to be permuted; that is, the values must be movable and the "
                        "iterator must be mutable.");
                }
            #endif
            };

            /// \ingroup group-actions
            /// \relates sort_fn
            /// \sa `action`
            namespace
            {
                constexpr auto&& random_shuffle = static_const<action<random_shuffle_fn>>::value;
            }
        }
        /// @}
    }
}

int main() 
{
    using namespace ranges;

    auto const N = 10;
    std::vector<int> v; 
    v.reserve(N);
    
    v |= action::push_back(view::iota(0, N)) | action::random_shuffle; 
    copy(v, ostream_iterator<>(std::cout, ","));
}
