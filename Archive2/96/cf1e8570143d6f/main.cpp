#include <iostream>
#include <array>
#include <vector>
#include <type_traits>
 
#include <algorithm> // just for std::generate in main()
 
// meta functions
template<typename T>
constexpr T meta_prod(T x) { return x; }
 
template<typename T, typename... Ts>
constexpr T meta_prod(T x, Ts... xs) { return x * meta_prod(xs...); }


namespace detail {
    template <typename Iter, size_t D0>
    size_t flatten(Iter first, Iter, std::index_sequence<D0> ) {
        return *first;
    }

    template <typename Iter, size_t D0, size_t... DIMS>
    size_t flatten(Iter first, Iter last, std::index_sequence<D0, DIMS...> ) {
        return *first * meta_prod(DIMS...) + 
               flatten(std::next(first), last, std::index_sequence<DIMS...>{} );
    }
}    

// pretty-print for std::array
template<class T, size_t N> 
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "{";
    for (auto && el : arr) { os << el << ";"; }
    return os << "\b}";
}
 

template<typename T, size_t... DIMS>
class MultiGrid {
public:
    static constexpr size_t NUM_DIMS = sizeof...(DIMS);
    static_assert(NUM_DIMS > 0, "Grid dimensions problem...");
 
    using ArrayValues     = std::array<T,meta_prod(DIMS...)>;
    using ArrayCoord      = std::array<size_t,NUM_DIMS>;
    using MapIndexToCoord = std::array<ArrayCoord,meta_prod(DIMS...)>;
 
    using value_type      = typename ArrayValues::value_type;      // T
    using reference       = typename ArrayValues::reference;       // T&
    using const_reference = typename ArrayValues::const_reference; // const T&
    using size_type       = typename ArrayValues::size_type;       // size_t
    using iterator        = typename ArrayValues::iterator;        // random access iterator
    using const_iterator  = typename ArrayValues::const_iterator;
 
    MultiGrid() : MultiGrid(ArrayValues{}) {} // default constructor use delegating constructor
    MultiGrid(const ArrayValues& values) 
        : map_idx_to_coord_(fill_map_idx_to_coord())
        , values_(values)
        {}
 
    iterator       begin()        { return values_.begin();  }
    const_iterator begin()  const { return values_.begin();  }
    const_iterator cbegin() const { return values_.cbegin(); }
    iterator       end()          { return values_.end();    }
    const_iterator end()    const { return values_.end();    }
    const_iterator cend()   const { return values_.cend();   }
 
    reference       operator[] (size_type idx)       { return values_[idx]; };
    const_reference operator[] (size_type idx) const { return values_[idx]; };
 
    reference operator[] (const ArrayCoord& coord) { 
        return values_[detail::flatten(
            coord.begin(), coord.end(), std::index_sequence<DIMS...>{})];
    }
    const_reference operator[] (const ArrayCoord& coord) const { 
        return const_cast<reference>(static_cast<const MultiGrid&>(*this)[coord]); 
    };
 
    auto get_coord_from_index(size_type idx) const {
        return map_idx_to_coord_.at(idx);
    }
 
    size_type get_index_from_coord(const ArrayCoord& coord) const {
        return detail::flatten(
            coord.begin(), coord.end(), std::index_sequence<DIMS...>{});
    }
 
private:
    auto  fill_map_idx_to_coord() const {
        MapIndexToCoord coord;
        std::array<size_t,NUM_DIMS> size_per_dim{{DIMS...}};
        for (size_t j = 0; j < meta_prod(DIMS...); j ++) {
            size_t a = j, b = meta_prod(DIMS...), r = 0;
            for(size_t i = 0; i <= NUM_DIMS - 2; i ++) {
                b /= size_per_dim[NUM_DIMS - i - 1];
                coord[j][NUM_DIMS-i-1] = a / b;
                r = a % b;
                a = r;
            }
            coord[j][0] = r;
        }
        return coord;
    }
    friend auto &operator<<(std::ostream &os, const MultiGrid& that) {
        os << "Values : {";
        for (auto&& v : that.values_)  { os << v << ";"; }
        os << "\b}\nMapping index to coord :\n";
        static size_t count{0};
        for (auto&& m : that.map_idx_to_coord_) { os << count ++ << ":" << m << "\t"; }
        return os << "\n";
    }
 
private:
    MapIndexToCoord map_idx_to_coord_;    // O(1) access flat index -> dim coordinates
    ArrayValues     values_;              // same behaviour as declaring  `float values_[meta_prod(DIMS)];`
};
 
int main() {
    // Create a 4D grid with 3x2x3x5 vertices
    MultiGrid<float,3,2,3,5> grid;
    // grid behaves like a STL container and we can fill values with std::generate
    std::generate(grid.begin(), grid.end(), [](){ static float n{0.0f}; return n+=0.5f; } );
    std::cout << grid << std::endl;
 
    // get coordinates from index
    std::cout << "get_coord_from_index(43) = " << grid.get_coord_from_index(43) << std::endl;
    // and vice versa
    std::cout << "get_index_from_coord({{2,0,2,3}}) = " << grid.get_index_from_coord({{2,0,2,3}}) << std::endl;
    // print value at specific coordinates
    std::cout << "Grid[{{2,0,2,3}}] = " << grid[{{2,0,2,3}}] << std::endl;
    // print value at specific index
    std::cout << "Grid[42] = " << grid[42] << "\n\n";
 
    MultiGrid<float, 2, 2> little_grid;
    std::cout << little_grid << std::endl;

    std::cout << "sizeof(MultiGrid<5,int,2,2,2,2,2>) = " << sizeof(MultiGrid<int,2,2,2,2,2>) << std::endl;
}
