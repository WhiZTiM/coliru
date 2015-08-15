#include <iostream>
#include <future>
 
using namespace std;
 
template <typename Fn, typename... Args>
auto do_async_with_log(ostream& os, Fn&& fn, Args&&... args)
     ->     future<decltype(fn(args...))>
{
  	os << "[TID=" << this_thread::get_id()
	     << "] Starting to invoke function..." << endl;
  	auto bound = bind(fn, forward<Args&&...>(args...));
  	return async([b=move(bound),&os]() {
    		auto result = b();
    		os << "[TID=" << this_thread::get_id()
    		   << "] ...invocation done, returning " << result << endl;
    		return result;
  	});
}