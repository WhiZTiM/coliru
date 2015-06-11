#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>

#if 1
    #define log(x) std::cout << x << std::endl;
#else
    #define log(x)
#endif

template<typename type>
std::vector<type> operator+(const std::vector<type> l, const std::vector<type> r){
    std::vector<type> ans;
    std::transform(l.begin(), l.end(), r.begin(), std::back_inserter(ans), std::plus<type>());
    return ans;
};
template<typename type>
std::vector<type> operator*(const std::vector<type> l, const std::vector<type> r){
    std::vector<type> ans;
    std::transform(l.begin(), l.end(), r.begin(), std::back_inserter(ans), std::multiplies<type>());
    return ans;
};
template<typename type>
std::vector<type> operator-(const std::vector<type> l, const std::vector<type> r){
    std::vector<type> ans;
    std::transform(l.begin(), l.end(), r.begin(), std::back_inserter(ans), std::minus<type>());
    return ans;
};
template<typename type>
std::vector<type> operator/(const std::vector<type> l, const std::vector<type> r){
    std::vector<type> ans;
    std::transform(l.begin(), l.end(), r.begin(), std::back_inserter(ans), std::divides<type>());
    return ans;
};

template<class type> struct point{

    point(std::initializer_list<type> coords) : coordinates(coords) {}
    //template<typename a = type, typename... b> point(a coordinate, b... coordinates){
    //    this->coordinates = {coordinate, coordinates...};
    //};

	point(point const &) = default;

	std::vector<type> coordinates;

    template<typename a = type> point(std::vector<a> const &coordinates){
        this->coordinates = coordinates;
    };
    friend point<type> operator+(const point<type>& l, const point<type>& r){
        point<type> ans(l.coordinates + r.coordinates);
        return ans;
    };
    friend point<type> operator*(const point<type>& l, const point<type>& r){
        point<type> ans(l.coordinates * r.coordinates);
        return ans;
    };
    friend point<type> operator-(const point<type>& l, const point<type>& r){
        point<type> ans(l.coordinates - r.coordinates);
        return ans;
    };
    friend point<type> operator/(const point<type>& l, const point<type>& r){
        point<type> ans(l.coordinates / r.coordinates);
        return ans;
    };

	template <class T>
	point &operator=(point<T> const &other) {
		coordinates.resize(other.coordinates.size());
		std::copy(other.coordinates.begin(), other.coordinates.end(), coordinates);
		return *this;
	}

    friend std::ostream& operator<<(std::ostream& stream, const point& p){
        switch(p.coordinates.size()){
        case 1:
            std::cout << "(" << p.coordinates[0] << ")";
            break;
        default:    
            std::cout << "("; 
            for(int i = 0; i < p.coordinates.size(); ++i){
                if(i == (p.coordinates.size() - 1))
                    std::cout << p.coordinates[i];
                else
                    std::cout << p.coordinates[i] << ", ";
            }
            std::cout << ")";
            break;
        }
		return stream;
    }
};
int main(){
	point<int> a({ 2,5,5,4,3 });
	point<int> b({ 3,5,3,5,7 });
    point<int> c(a/b);
    log(c);
    return 0;
}
