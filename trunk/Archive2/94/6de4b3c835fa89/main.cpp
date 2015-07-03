#include <mutex>
#include <vector>
#include <iostream>

template <typename MUTEX, typename RESOURCE>
class LockedResource
{
    using mutex_t    = MUTEX;
    using resource_t = RESOURCE;

    mutex_t    m_mutex;
    resource_t m_resource;

public:
        template <typename ... ARGS>
        LockedResource(ARGS &&... args) :
                m_resource(std::forward<ARGS>(args) ...)
        {}

    class Handler
    {
        std::unique_lock<mutex_t> m_lock;      // unique lock
        resource_t                &m_resource; // Ref to resource

        friend class LockedResource;

        Handler(mutex_t &a_mutex, resource_t &a_resource) :
            m_lock(a_mutex),       // mutex automatically locked
            m_resource(a_resource)
        { std::cout << "Resource locked\n"; }

    public:
        Handler(Handler &&a_handler) :
            m_lock(std::move(a_handler.m_lock)),
            m_resource(a_handler.m_resource)
        { std::cout << "Moved\n"; }

        ~Handler() // mutex automatically unlocked
        { std::cout << "Resource unlocked\n"; }

        RESOURCE *operator->()
        { return &m_resource; }
    };

    Handler get()
    { return {m_mutex, m_resource}; }
};

template <typename T> using Resource = LockedResource<std::mutex, T>;

LockedResource<std::mutex, std::vector<int>> locked_vector{10, 10};

int main()
{
/*1*/  auto vec = locked_vector.get(); // vec = Resource<vector>::Handler
/*2*/  std::cout << locked_vector.get()->size() << '\n';
/*3*/  std::cout << vec->size() << '\n';
    return 0;
}
