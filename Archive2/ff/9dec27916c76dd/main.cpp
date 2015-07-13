

namespace RPC {



struct Server
{
    template<typename Command, typename Function>
    void registerAsyncCommand(Function&& func)
    {
        do_register_async<Command>(
            GetTypeName(Identity<Command>()), // ADL-lookup
            func,
            Detail::ArgumentTypeTag<typename Command::argument_type>(),
            Detail::ResultTypeTag<typename Command::result_type>());
    }  
    
private:
    template<int ...>
    struct Sequence { };

    template<int N, int ...S>
    struct GenerateSequence : GenerateSequence<N - 1, N - 1, S...> { };

    template<int ...S>
    struct GenerateSequence<0, S...> { typedef Sequence<S...> type; };
    
    template<typename F, typename Callback, typename Tuple, int ...Indices>
    static void do_explode_with_callback(F&& f, ClientSession& session, Callback&& callback, Tuple&& tuple, Sequence<Indices...>)
    {
        f(session, std::forward<Callback>(callback), std::get<Indices>(tuple)...);
    }
    
    template<typename F, typename Callback, typename ...Args>
    static void explode_with_callback(F&& f, ClientSession& session, Callback&& callback, std::tuple<Args...>&& tup)
    {
        typedef typename GenerateSequence<sizeof...(Args)>::type Sequence;
        do_explode_with_callback(f, session, std::forward<Callback>(callback), tup, Sequence{});
    }
    
    static std::future<RecursiveAttribute> pack_future(std::future<void>& fut)
    {
        try
        {
            fut.get();
            return MakeReadyFuture(Pack(RecursiveAttribute()));
        }
        catch (...)
        {
            return MakeExceptionalFuture<RecursiveAttribute>(std::current_exception());
        }
    }
    
    template<typename R>
    static std::future<RecursiveAttribute> pack_future(std::future<R>& fut)
    {
        try
        {
            return MakeReadyFuture(Pack(fut.get()));
        }
        catch (...)
        {
            return MakeExceptionalFuture<RecursiveAttribute>(std::current_exception());
        }
    }  
    
    template<typename C, typename F, typename R>
    void do_register_async(const std::string & name, F&& handler, Detail::ArgumentTypeIsVoid<false>, Detail::ResultTypeTag<R>)
    {
        typedef typename std::decay<typename C::argument_type>::type CleanArgType;
    
        registerCommandImpl(
            name,
            [handler](ClientSession& session, const RecursiveAttribute& arg, std::function<void(std::future<RecursiveAttribute>)> callback) {
                explode_with_callback(
                    handler,
                    session,
                    [callback](std::future<R> fut) { callback(pack_future(fut)); },
                    Extract<CleanArgType>(arg)
                );
            }
        );
    }
};


} // namespace RPC

