#define TRACE std::cout << __FILE__ << ":" << __LINE__ << ": " << __FUNCTION__ << std::endl;


template<typename C, typename F>
    void do_register_async(const std::string & name, F&& handler, Detail::ArgumentTypeIsVoid<false>, Detail::ResultTypeTag<void>)
    {
        typedef typename RemoveConstRef<typename C::argument_type>::type CleanArgType;

        registerCommandImpl(
            name,
            [handler](ClientSession& session, const RecursiveAttribute& arg, std::function<void(RecursiveAttribute)> callback) {            
                TRACE
                explode_with_callback(
                    handler,
                    session,
                    [handler, callback](std::future<void> fut) {                    
                        try {
                            TRACE
                            fut.get();
                            TRACE
                            callback(Pack(RecursiveAttribute()));
                            TRACE
                        } catch (...) {
                            TRACE
                            auto e = std::current_exception();
                            TRACE
                            callback(std::async(std::launch::deferred, [e]() -> std::string {
                                TRACE
                                std::rethrow_exception(e);
                            }));
                            TRACE
                        }
                        TRACE
                    },
                    Extract<CleanArgType>(arg)
                );
                TRACE
            }
        );
    }
    