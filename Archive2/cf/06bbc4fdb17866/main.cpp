#include <iostream>
#include <string>
#include <iterator>




namespace wtf {
/*

template <typename T>
struct is_transparent : std::false_type{};

template <typename T, typename = typename T::is_transparent>
struct is_transparent<T> : std::true_type {};
*/
}

namespace wtf {
template<class T>
struct Void {
  typedef void type;
};

template<class T, class U = void>
struct is_transparent {
    enum { value = 0 };
};

template<class T>
struct is_transparent<T, typename Void<typename T::is_transparent>::type > {
    enum { value = 1 };
};
}

namespace wtf{
template <typename Iterator>
std::reverse_iterator<Iterator> make_reverse_iterator(Iterator iter) {
    return std::reverse_iterator<Iterator>(iter);
}
}

#define NOEXCEPT noexcept
#define NOEXCEPT_IF(x) noexcept(x)


#include <vector>
#include <utility>
#include <algorithm>
#include <functional>


template <typename Key, typename T, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<std::pair<Key, T>>>
class flatmap {

public:
    using mapped_type = T;
    using key_type = Key;
    using value_type = std::pair<key_type, mapped_type>;
    using key_compare = Comparator;
    using allocator_type = Allocator;
    using size_type = typename std::vector<value_type, allocator_type>::size_type;
    using difference_type = typename std::vector<value_type, allocator_type>::size_type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
    using iterator = typename std::vector<value_type, allocator_type>::iterator;
    using const_iterator = typename std::vector<value_type, allocator_type>::const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    flatmap() {}
    template <typename InputIterator>
    flatmap(InputIterator first, InputIterator last)
        : data{first, last} {
        std::sort(begin(), end(),
                  [=](const value_type& lhs, const value_type& rhs) { return cmp(lhs.first, rhs.first); });
        std::unique(begin(), end(), [=](const value_type& lhs, const value_type& rhs) {
            return !cmp(lhs.first, rhs.first) && !cmp(rhs.first, lhs.first);
        });
    }
    flatmap(std::initializer_list<value_type> elems) : flatmap(std::begin(elems), std::end(elems)) {}

    iterator find(const Key& key) {
        auto it = lower_bound(key);
        if (it != end() && !cmp(key, it->first)) {
            return it;
        }
        return end();
    }
    const_iterator find(const Key& key) const {
        auto it = lower_bound(key);
        if (it != end() && !cmp(key, it->first)) {
            return it;
        }
        return end();
    }

    template <typename K, typename = typename std::enable_if<wtf::is_transparent<Comparator>::value, void>::type*>
    iterator find(const K& x){
        return begin();   
    }


    T& at(const Key& key){
        auto it = lower_bound(key);
        if (it == end() || cmp(key, it->first)){
            throw std::out_of_range("Given key was not found in the flatmap.\n");
        } else {
            return it->second;
        }
    }
    
    const T& at(const Key& key) const {
        auto it = lower_bound(key);
        if (it == end() || cmp(key, it->first)){
            throw std::out_of_range("Given key was not found in the flatmap.\n");
        } else {
            return it->second;
        }
    }

    T& operator[](const Key& key) {
        auto it = lower_bound(key);
        if (it != end() && !cmp(key, it->first)) {
            return it->second;
        } else {
            return insert(it, {key, mapped_type{}})->second;
        }
    }

    std::pair<iterator, bool> insert(const value_type& value) {
        auto it = lower_bound(value.first);
        if (it == end() || cmp(value.first, it->first)) {
            return {data.insert(it, value), true};
        }
        return {it, false};
    }
    iterator insert(iterator hint, const value_type& value) {
        return data.insert(hint, value);
    }
    iterator insert(const_iterator hint, const value_type& value) {
        return data.insert(hint, value);
    }

    iterator lower_bound(const Key& key) {
        return std::lower_bound(begin(), end(), key,
                                [&](const value_type& lhs, const Key& k) { return cmp(lhs.first, k); });
    }
    const_iterator lower_bound(const Key& key) const {
        return std::lower_bound(begin(), end(), key,
                                [&](const value_type& lhs, const Key& k) { return cmp(lhs.first, k); });
    }
    iterator upper_bound(const Key& key) {
        return std::upper_bound(begin(), end(), key,
                                [&](const value_type& lhs, const Key& k) { return cmp(lhs.first, k); });
    }
    const_iterator upper_bound(const Key& key) const {
        return std::upper_bound(begin(), end(), key,
                                [&](const value_type& lhs, const Key& k) { return cmp(lhs.first, k); });
    }
    // ToDo: This can potentially be optimized by calling the standard lower, upper bound and passing them results,
    //      thus shortening their potential search.
    std::pair<iterator, iterator> equal_range(const Key& key) {
        return {lower_bound(key), upper_bound(key)};
    }
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
        return {lower_bound(key), upper_bound(key)};
    }

    iterator erase(const_iterator it){
        return data.erase(it);
    }
    iterator erase(const_iterator first, const_iterator last){
        return data.erase(first, last);
    }
    //FixMe: Either use !cmp && !cmp instead of equality, or spaceship... figure it out later
    size_type erase(const key_type& key){
        return std::distance(data.erase(std::remove_if(begin(), end(), [&](const value_type& el){ return key == el.first; }), end()), end());
    }


    iterator begin() {
        return std::begin(data);
    }
    const_iterator begin() const {
        return std::begin(data);
    }
    const_iterator cbegin() const {
        return std::cbegin(data);
    }
    std::reverse_iterator<iterator> rbegin() {
        return wtf::make_reverse_iterator(std::begin(data));
    }
    std::reverse_iterator<const_iterator> rbegin() const {
        return wtf::make_reverse_iterator(std::begin(data));
    }
    std::reverse_iterator<const_iterator> crbegin() const {
        return wtf::make_reverse_iterator(std::cbegin(data));
    }
    iterator end() {
        return std::end(data);
    }
    const_iterator end() const {
        return std::end(data);
    }
    const_iterator cend() const {
        return std::cend(data);
    }
    std::reverse_iterator<iterator> rend() {
        return wtf::make_reverse_iterator(std::end(data));
    }
    std::reverse_iterator<const_iterator> rend() const {
        return wtf::make_reverse_iterator(std::end(data));
    }
    std::reverse_iterator<const_iterator> crend() const {
        return wtf::make_reverse_iterator(std::end(data));
    }

    void clear() NOEXCEPT {
        data.clear();
    }

    bool empty() const {
        return data.empty();
    }

    size_type size() const {
        return data.size();
    }

    size_type max_size() const {
        return data.max_size();
    }

    void reserve(size_type new_reserve) {
        data.reserve(new_reserve);
    }

    size_type capacity() const {
        return data.capacity();
    }

    void shrink_to_fit() {
        data.shrink_to_fit();
    }

    size_type count(const Key& key) const {
        return find(key) != end();
    }

    friend void swap(flatmap < Key, T, Comparator, Allocator>& lhs, flatmap<Key, T, Comparator, Allocator>& rhs) {
		using std::swap;
        std::cout << "swapper\n";
		swap(lhs.data, rhs.data);
		swap(lhs.cmp, rhs.cmp);
	}
    
/*    value_type* data(){
        return data.data();
    }
    
    const value_type* data() const {
        return data.data();
    }*/


private:
    std::vector<value_type, allocator_type> data;
    Comparator cmp;
};




int main(){
    using std::swap;


   flatmap<std::string, int> fm, fm2;
   swap(fm, fm2);
//   fm.insert(std::make_pair(1, 2));
//   fm.insert(std::make_pair(2, 4));
//   fm.insert(std::make_pair(3, 6));
   fm.crend(); fm.rend(); fm.cend(); fm.end(); fm.begin(); fm.cbegin(); fm.rbegin(); fm.crbegin();
   fm.insert(std::make_pair("oxygen", -1));
   fm.insert(std::make_pair("carbon", 0));
   fm.insert(std::make_pair("nitrogen", 1));
   fm["hydrogen"] = 22;
   fm["monoxide"] = 3;
   fm["dihydrogen monoxide"] = 12345;
    std::cout << "Map listing:\n";
    for (const auto& el : fm){
        std::cout << el.first << "   " << el.second << '\n';
    }

    try{
        fm.at("hydrogen");
        std::cout << "Success\n";
    } catch (std::out_of_range& ex){
        std::cerr << "error\n";
    }
    
    try{
        fm.at("aslkdj");
        std::cerr << "error\n";
    } catch (std::out_of_range& ex){
        std::cout << "Success\n";
    }
   auto it = fm.find("oxygen");
   if (it == end(fm)) std::cerr << "FAILED!" << std::endl;
   else std::cerr << "PASSED" << std::endl;
   fm.erase(it);
   fm.erase("Map listing");
}