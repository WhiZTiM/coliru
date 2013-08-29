#include "Poco/Stopwatch.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <tuple>



template<typename T, template<typename> class HookPolicy>
struct Proxy : HookPolicy<T>
{
public:
    Proxy(T * p) : HookPolicy<T>(p), ptr(p)  { }
    
    const T * operator->() const { return ptr; }
    T * operator->() { return ptr; }
    
    const T * get() const { return ptr; }    
    T * get() { return ptr; }
    
    const T & ref() const { return *this->ptr; }    
    T & ref() { return *this->ptr; }
    
private:
    T * ptr;
};


template<typename T, template<typename> class HookPolicy>
class Protected
{    
public:
    template<typename ...Args>
    explicit Protected(Args && ...inArgs) :
        mObject(std::forward<Args>(inArgs)...)
    {
    }
    
    Proxy<T, HookPolicy> operator->()
    {
        return lock();
    }
    
    Proxy<const T, HookPolicy> operator->() const
    {
        return lock();
    }
    
    Proxy<T, HookPolicy> lock()
    {
        return Proxy<T, HookPolicy>(&mObject);
    }
    
    Proxy<const T, HookPolicy> lock() const
    {
        return Proxy<const T, HookPolicy>(&mObject);
    }
    
private:
    friend std::ostream& operator<<(std::ostream & os, const Protected<T, HookPolicy> & prot)
    {
        auto lock = prot.lock();
        return os << lock.ref() << std::endl;
    }
    
    T mObject;
};


template<typename T>
struct Policy
{
    Policy(T * p) : ptr(p) {}
    
    const T * get_ptr() const { return ptr; }    
    T * get_ptr() { return ptr; }
    
private:
    T * ptr;
};


template<typename T>
struct InspectPolicy : Policy<T>
{
    InspectPolicy(T * p) : Policy<T>(p)
    {
        std::cout << "Inspect before: " << *this->get_ptr() << std::endl;
    }
    
    ~InspectPolicy()
    {
        std::cout << "Inspect after: " << *this->get_ptr() << std::endl;
    }
};


template<typename T>
struct MutexLockPolicy : Policy<T>
{
    MutexLockPolicy(T * p) : Policy<T>(p), data(new Data)
    {
    }
    
    struct Data
    {
        Data() : mtx(), lock(mtx) {}
        std::mutex mtx; // TODO: must have larger scope! (it's pointless now)
        std::unique_lock<std::mutex> lock;
    };
    std::shared_ptr<Data> data;
};



template<typename T>
struct TimerPolicy : Policy<T>
{
    TimerPolicy(T * p) : Policy<T>(p), stopwatch(new Poco::Stopwatch)
    {
        stopwatch->start();
    }
    
    ~TimerPolicy()
    {
        std::cout << "Elapsed: " << stopwatch->elapsed() << " us" << std::endl;
    }
    
    std::shared_ptr<Poco::Stopwatch> stopwatch;
};


template<template<typename> class ...Args>
struct PolicyGroup
{
    template<typename T>
    struct Rebind : Args<T>...
    {
        Rebind(T * p) : Args<T>(p)...
        {
        }
    };
};


int main()
{
    // Chain a number of "hooks"
    Protected<std::string, PolicyGroup<TimerPolicy, MutexLockPolicy, InspectPolicy>::Rebind> s("test");
    
    std::cout << "\n1" << std::endl;
    {
        auto scoped = s.lock();
        scoped->push_back('d');
        scoped->push_back('e');
        scoped->push_back('f');
        std::cout << "I am inside the scope." << std::endl;
    }    
    
    std::cout << "\n2" << std::endl;
    std::cout << s << std::endl;
    
    std::cout << "\n3" << std::endl;
    s->clear();
}
