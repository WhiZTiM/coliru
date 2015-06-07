template <typename type>
static void local_ptr_deletor(type* ptr){
    delete ptr;
}


template <typename type>
class dll_uptr{
    type* ptr;
    void (*deletor)(type*);

public:
    //  Rule of 5
    ~dll_uptr(){
        deletor(ptr);
    }

    dll_uptr(const dll_uptr&) = delete;
    void operator=(const dll_uptr&) = delete;

    dll_uptr(dll_uptr&& x)
        : ptr(x.ptr)
        , deletor(x.deletor)
    {
        x.ptr = nullptr;
    }
    void operator=(dll_uptr&& x){
        ptr = x.ptr;
        deletor = x.deletor;
        x.ptr = nullptr;
    }

public:
    dll_uptr() : ptr(nullptr) {}
    dll_uptr(type* ptr,void (*deletor)(type*) = &local_ptr_deletor)
        : ptr(ptr)
        , deletor(deletor)
    {}

    type* get() const{
        return ptr;
    }
    type* operator->() const{
        return ptr;
    }
};
