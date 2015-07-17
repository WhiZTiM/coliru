// Multi grid in C++11
/* C++11
- std::array provides a statically-sized array : more efficient thant std::vector, similar to C-style array. Great to use with Blas, Lapack routines
- variadic template parameters for NDIM
- constexpr to compute meta_product of NDIM at compile time 
- unordered map fast access : average O(1) worst O(N)
*/

#include <array>
#include <iostream>
#include <unordered_map>
#include <utility>

#include <algorithm>

// std::hash specialization for std::array
namespace std {
    template<typename T, size_t N>
    struct hash<array<T, N> > {
        using argument_type = array<T, N> ;
        using result_type = size_t;
        result_type operator()(const argument_type& a) const {
            hash<T> hasher;
            result_type h = 0;
            for (result_type i = 0; i < N; ++i) {
                h = h * 31 + hasher(a[i]);
            }
            return h;
        }
    };
}

// pretty-print for std::array
template<class T, size_t N> 
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "{";
    for (auto && el : arr) { os << el << ";"; }
    return os << "\b}";
}

template<typename T>
constexpr T meta_prod(T x) { return x; }

template<typename T, typename... Ts>
constexpr T meta_prod(T x, Ts... xs) { return x * meta_prod(xs...); }

template<size_t DIM, typename T, size_t... NDIM>
class MultiGrid {
public:
    static_assert(sizeof...(NDIM) == DIM or sizeof...(NDIM) == 1, 
        "Variadic template arguments in Multigrid do not match dimension size !");

    using ArrayValues     = std::array<T,meta_prod(NDIM...)>;
    using ArrayCoord      = std::array<size_t,DIM>;
    using MapIndexToCoord = std::array<ArrayCoord,meta_prod(NDIM...)>;
    using MapCoordToIndex = std::unordered_map<ArrayCoord,size_t>;

    using value_type      = typename ArrayValues::value_type;      // T
    using reference       = typename ArrayValues::reference;       // T&
    using const_reference = typename ArrayValues::const_reference; // const T&
    using size_type       = typename ArrayValues::size_type;       // size_t
    using iterator        = typename ArrayValues::iterator;        // random access iterator
    using const_iterator  = typename ArrayValues::const_iterator;
    

    MultiGrid() : MultiGrid(ArrayValues{}) {}
    MultiGrid(const ArrayValues& values) 
        : map_idx_to_coord_(std::move(fill_map_idx_to_coord()))
        , map_coord_to_idx_(std::move(fill_map_coord_to_idx())) 
        , values_(values)
        {}
    
    iterator       begin()       { return values_.begin();  }
    const_iterator begin() const { return values_.cbegin(); }
    iterator       end()         { return values_.end();    }
    const_iterator end()   const { return values_.cend();   }

    reference       operator[] (size_type idx)       { return values_[idx]; };
    const_reference operator[] (size_type idx) const { 
        return const_cast<reference>(static_cast<const MultiGrid&>(*this)[idx]); 
    };

    reference       operator[] (const ArrayCoord& coord) { 
        return values_[map_coord_to_idx_[coord]]; 
    };

    const_reference operator[] (const ArrayCoord& coord) const { 
        return const_cast<reference>(static_cast<const MultiGrid&>(*this)[coord]); 
    };

    const ArrayCoord& get_coord_from_index(size_type idx) const {
        return map_idx_to_coord_[idx];
    }

    size_type get_index_from_coord(const ArrayCoord& coord) /* const */ {
        return map_coord_to_idx_[coord];
    }

private:
    MapIndexToCoord  fill_map_idx_to_coord() const {
        MapIndexToCoord coord;
        std::array<size_t,DIM> size_per_dim{{NDIM...}};
        for (size_t j = 0; j < meta_prod(NDIM...); j ++) {
            size_t a = j, b = meta_prod(NDIM...), r = 0;
            for(size_t i = 0; i <= DIM - 2; i ++) {
                b /= size_per_dim[DIM - i - 1];
                coord[j][DIM-i-1] = a / b;
                r = a % b;
                a = r;
            }
            coord[j][0] = r;
        }
        return coord;
    }
    MapCoordToIndex fill_map_coord_to_idx() const {
        MapCoordToIndex mapping(meta_prod(NDIM...));
        for(size_t i = 0; i < meta_prod(NDIM...); i ++) {
            mapping.emplace(map_idx_to_coord_[i],i);
        }
        return mapping;
    }
    friend std::ostream & operator<<(std::ostream &os, const MultiGrid& that) {
        os << "Values : {";
        for (auto&& v : that.values_)  { os << v << ";"; }
        os << "\b}\nMapping index to coord :\n";
        static size_t count{0};
        for (auto&& m : that.map_idx_to_coord_) { os << count ++ << ":" << m << "\t"; }
        os << "\nMapping coord to index :\n";
        for (auto && m : that.map_coord_to_idx_) { os << m.first << "->" << m.second << "\t"; }
        return os << "\n";
    }

private:
    MapIndexToCoord map_idx_to_coord_;    // O(1) access flat index -> dim coordinates
    MapCoordToIndex map_coord_to_idx_;    // O(1) acess dim coordinates -> flat index (worst case : O(N))
    ArrayValues     values_;              // same behaviour as declaring  `float values_[meta_prod(NDIM)];`
};

int main() {
    // Create a 4D grid with 3x2x3x5 vertices
    MultiGrid<4,float,3,2,3,5> grid;
    // grid behaves like a STL container and we can fill values with std::generate
    std::generate(grid.begin(), grid.end(), []() {static float n{0.0f}; return n+=0.5f;} );
    std::cout << grid << std::endl;

    // get coordinates from index
    std::cout << "get_coord_from_index(43) = " << grid.get_coord_from_index(43) << std::endl;
    // and vice versa
    std::cout << "get_index_from_coord({{2,0,2,3}}) = " << grid.get_index_from_coord(std::array<size_t,4>{{2,0,2,3}}) << std::endl;
    // print value at specific coordinates
    std::cout << "Grid[{{2,0,2,3}}] = " << grid[{{2,0,2,3}}] << std::endl;
    // print value at specific index
    std::cout << "Grid[42] = " << grid[42] << std::endl;
}
