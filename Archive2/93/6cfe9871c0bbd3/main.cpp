template<class... Args> class StaticDelegate {
public:
    StaticDelegate(void (*function)(Args...));
    void operator()(Args... args);

private:
    void (*function)(Args...);
};

template<class... Args> StaticDelegate<Args...>::StaticDelegate(void (*function)(Args...)) : function(function) {}

template<class... Args> void StaticDelegate<Args...>::operator()(Args... args) {
    function(args...);
}