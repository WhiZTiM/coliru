#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


template<typename T>
struct Data
{
    Data(std::initializer_list<T> list) : vec_(list), size_(vec_.size()) {}
    
    using size_type = typename std::vector<T>::size_type;
    
    void resize(size_type size)
    {
        if (size < vec_.size())
        {
            size_ = size;
        }
        else if (size > vec_.size())
        {
            vec_.resize(size);
            size_ = size;
        }
    }
    
    auto size() const{ return size_; }
    auto capacity() const { return vec_.size(); }
    
    decltype(auto) operator[](std::size_t i) const { return vec_[i]; }        
    decltype(auto) operator[](std::size_t i) { return vec_[i]; }    
    
    auto end() const { return vec_.end(); }        
    auto end() { return vec_.end(); }
    
    auto begin() const { return vec_.begin(); }    
    auto begin() { return vec_.begin(); }    
    
    std::vector<T> vec_;
    size_type size_ = 0;
};


using Index = Data<int>::size_type;


template<typename T>
std::ostream& operator<<(std::ostream& os, const Data<T>& data)
{
    for (auto& t : data)
    {
        os << std::setw(2) << std::setfill(' ') << std::right << t << " ";
    }
    return os;
}

Index get_left(Index i)
{
    return 2*i + 1;
}

Index get_right(Index i)
{
    return get_left(i) + 1;
}

Index get_parent(Index i)
{
    return (i-1)/2;    
}


template<typename T>
void max_heapify(Data<T>& data, Index idx)
{
    auto max = idx;
    
    for (;;)
    {        
        auto left = get_left(idx);
        if (left < data.size() && data[left] > data[max])
        {
            max = left;
        }
        
        auto right = get_right(idx);
        if (right < data.size() && data[right] > data[max])
        {
            max = right;
        }
        
        if (max != idx)
        {
            std::swap(data[max], data[idx]);
            idx = max;
        }
        else
        {
            break;
        }
    }
}

template<typename T>
int index_of_first_leaf(Data<T>& data)
{
    return data.size() / 2;
}

template<typename T>
void build_max_heap(Data<T>& data)
{
    for (auto i = index_of_first_leaf(data) - 1; i >= 0; --i)
    {
        max_heapify(data, i);
    } 
}

template<typename T>
void heap_sort(Data<T>& data)
{
    build_max_heap(data);
    for (int i = data.size() - 1; i >= 1; --i)
    {
        std::swap(data[0], data[i]);
        data.resize(data.size() - 1);
        max_heapify(data, 0);
    }    
}

void test(Data<int>&& d)
{
    std::cout << "before heap_sort: " << d << " size=" << d.size() << " capacity=" << d.capacity() << "\n";
    heap_sort(d);
    auto is_sorted = std::is_sorted(d.begin(), d.end());
    std::cout << "after  heap_sort: " << d << " size=" << std::setw(2) << std::setfill(' ') << std::left << d.size() << " capacity=" << d.capacity() << " verification=" << (is_sorted ? "OK" : "FAILED") << '\n' << std::endl;
    assert(std::is_sorted(d.begin(), d.end()));
}   

void test_shuffled(Data<int>&& d)
{
    std::random_shuffle(d.begin(), d.end());
    test(std::move(d));
}    

int main()
{
    std::srand(std::time(0));
    for (auto i = 0; i != 10; ++i)
    {
        test_shuffled({10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40});
    }
}
