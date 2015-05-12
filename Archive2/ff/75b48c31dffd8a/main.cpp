#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>

#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/as_vector.hpp>

namespace bg_to_fusion {
    using namespace boost;

    struct bg_point_tag;
    struct example_struct_iterator_tag;

    template<typename Point, int Pos>
    struct point_iterator
        : fusion::iterator_base<point_iterator<Point, Pos> >
    {
        BOOST_STATIC_ASSERT(Pos >=0 && Pos <geometry::traits::dimension<typename remove_cv<Point>::type>::value);

        typedef Point point_type;
        typedef mpl::int_<Pos> index;
        //typedef fusion::random_access_traversal_tag category;
        typedef fusion::forward_traversal_tag category;

        point_iterator(Point& p) : point_(p) {}
        Point& point_;
    };
}

namespace boost { namespace fusion {

    // tag dispatch
    namespace traits {

        template <typename T, size_t dims, typename cs>
        struct tag_of<geometry::model::point<T, dims, cs> > {
            typedef bg_to_fusion::bg_point_tag type;
        };

        template <typename Point, int Pos>
        struct tag_of<bg_to_fusion::point_iterator<Point, Pos> > {
            typedef bg_to_fusion::example_struct_iterator_tag type;
        };

    }

    namespace extension {

        //////////////////////////////////////////////////////
        // Point extension implementations
        template<>
        struct is_sequence_impl<bg_to_fusion::bg_point_tag>
        {
            template<typename T>
                struct apply : mpl::true_ {};
        };

        template <>
        struct size_impl<bg_to_fusion::bg_point_tag> {
            template <typename Point>
            struct apply : mpl::integral_c<size_t, geometry::traits::dimension<typename remove_cv<Point>::type>::value> { };
        };

        // begin
        template<>
        struct begin_impl<bg_to_fusion::bg_point_tag>
        {
            template<typename Point> 
            struct apply 
            {
                typedef typename bg_to_fusion::point_iterator<Point, 0> type;

                static type
                call(Point& p) 
                {
                    return type(p);
                }
            };
        };

        // end
        template<>
        struct end_impl<bg_to_fusion::bg_point_tag>
        {
            template<typename Point> struct apply {
                typedef typename bg_to_fusion::point_iterator<Point, geometry::traits::dimension<Point>::value> type;

                static type call(Point& p) {
                    return type(p);
                }
            };
        };

        ////////////////////////
        // Iterator extension implementations

        // value_of
        template <>
        struct value_of_impl<bg_to_fusion::example_struct_iterator_tag> {
            template<typename Iterator> struct apply;

            template<typename Point, int Pos> 
            struct apply<bg_to_fusion::point_iterator<Point, Pos> > {
                typedef typename geometry::traits::coordinate_type<typename remove_cv<Point>::type>::type type;
            };
        };

        // deref
        template<>
        struct deref_impl<bg_to_fusion::example_struct_iterator_tag>
        {
            template<typename Iterator>
            struct apply;

            template<typename Point, int Pos>
            struct apply<bg_to_fusion::point_iterator<Point, Pos> >
            {
                typedef typename geometry::traits::coordinate_type<typename remove_cv<Point>::type>::type coordinate_type;

                //typedef typename mpl::if_<is_const<Point>, coordinate_type const&, coordinate_type&>::type type;
                typedef coordinate_type type;

                static type
                call(bg_to_fusion::point_iterator<Point, Pos> const& it) {
                    return it.point_.template get<Pos>();
                }
            };
        };

        // next
        template<>
            struct next_impl<bg_to_fusion::example_struct_iterator_tag> {
                template<typename Iterator> struct apply
                {
                    typedef typename Iterator::point_type point_type;
                    typedef typename Iterator::index    index;
                    typedef typename bg_to_fusion::point_iterator<point_type, index::value + 1> type;

                    static type
                        call(Iterator const& i) {
                            return type(i.point_);
                        }
                };
            };
    }

} }

#include <iostream>

namespace bg  = boost::geometry;
namespace fus = boost::fusion;

int main() {
    bg::model::point<double, 7, bg::cs::cartesian> p1;
    // set some nice values
    p1.set<0>(7);  p1.set<1>(14); p1.set<2>(21); p1.set<3>(28);
    p1.set<4>(35); p1.set<5>(42); p1.set<6>(49);

    fus::for_each(fus::as_vector(p1), [](double x) { std::cout << x << ' '; });
}
