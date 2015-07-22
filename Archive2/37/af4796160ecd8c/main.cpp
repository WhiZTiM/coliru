#include <iostream>
#include <iomanip>
#include <cstddef>

struct DataBlock {
    static constexpr std::size_t element_size = 8;
    void * data = nullptr;

    explicit DataBlock(size_t elements)
    {
        // required alignment
        static_assert(alignof(std::max_align_t) >= 8, "alignment error");
        // further sanity check on element overflow the alignment boundary
        static_assert(alignof(std::max_align_t) >= element_size, "element overflow");
        
        data = ::operator new(elements*element_size);
    }

    ~DataBlock()
    {
        ::operator delete(data);
    }

    DataBlock(DataBlock&) = delete; // no copy
    DataBlock& operator=(DataBlock&) = delete; // no assign
    // probably shouldn't move either
    DataBlock(DataBlock&&) = delete;
    DataBlock& operator=(DataBlock&&) = delete;

    template <class T>
    T& construct(std::size_t index)
    {
        T* t = new (get_location<T>(index)) T{};
        return *t;
    }

    template <class T>
    void destroy(std::size_t index)
    {
        T* t = get_location<T>(index);
        t->~T();
    }

    template <class T>
    T& get(std::size_t index)
    {
        T* t = get_location<T>(index);
        return *t;
    }

    template <class T>
    T* get_location(std::size_t index)
    {
        return reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(data) + index*element_size);
    }
};

void dump_memory(void* mem, std::size_t size)
{
    using namespace std;
    cout << "dump_memory" << endl;
    for (std::size_t i = 0; i < size; ++i) {
        // plan C-casts for the demo
        cout << setfill('0') << setw(2) << (unsigned int)(((unsigned char*)mem)[i]) << ' ';
    }
    cout << endl;
}

int main()
{
    using namespace std;
    cout << hex;

    constexpr int element_size = DataBlock::element_size;
    constexpr int block_count = 5;

    DataBlock block(block_count);

    dump_memory(block.data, block_count*element_size);

    int& i = block.construct<int>(2);
    i = 0x31323334;
    cout << block.get<int>(2) << endl;
    auto&& c = block.construct<char>(3);
    char text[] = "56789";
    // arrays can be awkward to work with, your mileage may vary
    // additional utility methods can be added as desired
    copy(begin(text), end(text), &c);
    cout << &block.get<char>(3) << endl;

    dump_memory(block.data, block_count*element_size);
}
