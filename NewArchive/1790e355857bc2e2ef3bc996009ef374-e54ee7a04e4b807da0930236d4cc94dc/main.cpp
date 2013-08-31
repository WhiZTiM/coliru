#include <limits>       // std::numeric_limits;
#include <stddef.h>     // ptrdiff_t, size_t
#include <type_traits>  // std::is_same, std::enable_if
#include <utility>      // std::declval

namespace cppx {
    using std::declval;
    using std::enable_if;
    using std::false_type;
    using std::is_same;
    using std::true_type;
    using std::numeric_limits;

    template< class Type >
    class Has_accessible_sizefunc_member_
    {
    private:
        template< class U >
        static auto the_type_for( U& u ) -> decltype( u.size() );

        static auto the_type_for( ... ) -> void;

    public:
        typedef decltype( the_type_for( declval<Type&>() ) ) Result;
        enum{ yes = numeric_limits< Result >::is_integer && !is_same<Result, bool>::value };
    };
}  // namespace cppx

struct NotAtAll
{};

struct Yes
{
    ptrdiff_t size() const { return 0; }
};

struct BoolResult
{
    bool size() const { return false; }
};

struct Ambiguous: Yes, BoolResult {};

struct Inaccessible
{
private:
    ptrdiff_t size() const { return 666; }
};

#include <iostream>
#include <vector>
using namespace std;
int main( int argc, char* argv[] )
{
    using namespace cppx;
    cout << "Vector: " << Has_accessible_sizefunc_member_<vector<int>>::yes << endl;
    cout << "Array: " << Has_accessible_sizefunc_member_<int[42]>::yes << endl;
    cout << "NotAtAll: " << Has_accessible_sizefunc_member_<NotAtAll>::yes << endl;
    cout << "Yes: " << Has_accessible_sizefunc_member_<Yes>::yes << endl;
    cout << "Ambiguous: " << Has_accessible_sizefunc_member_<Ambiguous>::yes << endl;
    cout << "BoolResult: " << Has_accessible_sizefunc_member_<BoolResult>::yes << endl;
#ifdef CHECK
    cout << "Inaccessible: " << Has_accessible_sizefunc_member_<Inaccessible>::yes << endl;
#endif
}
