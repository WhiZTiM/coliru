#include <string>
#include <iostream>

// Callbacks parameters
struct CbBase // base params 
{ 
    enum Type { subscribed, unsubscribed, out_of_sync, auth };
    int record;
};

// Channel specific callbacks
struct CbChannel : CbBase 
{
    std::string channel;
    std::string next;
};

// Auth specific callbacks
struct CbAuth: CbBase
{
    std::string reject_reason;
};

// SDK that calls user callbacks
class sdk_client
{
    // SDK helpers - for internal use only
    struct callee_base
    {
        virtual ~callee_base () {}

        virtual void operator() (CbBase const& cb) const = 0;
        virtual void operator() (CbChannel const& cb) const = 0;
        virtual void operator() (CbAuth const& cb) const = 0;
    };

    template <class UserCallback>
    struct callee: callee_base
    {
        callee (UserCallback const& u) : user_ (u) {}

        void operator() (CbBase const& cb) const { user_ (cb); }
        void operator() (CbChannel const& cb) const { user_ (cb); };
        void operator() (CbAuth const& cb) const { user_ (cb); }

        UserCallback user_;
    };

    // disallow copy ctor and assign
    sdk_client (sdk_client const&) = delete;
    void operator= (sdk_client const&) = delete;

public:
    sdk_client () {}

    // stores user callback
    template <typename UserCallback>
    void set_user_callback (UserCallback const& cb)
    {
        cb_ = new callee<UserCallback> (cb);
    }

    // call three types of callbacks - base, channel and auth
    void call_smth ()
    {
        std::cout << "sdk_client::call_smth: calling callback (CbBase)\n";
        (*cb_) (CbBase {}); // user's base callback should be calls
        std::cout << std::endl;

        std::cout << "sdk_client::call_smth: calling callback (CbChannel)\n";
        (*cb_) (CbChannel {}); // user's channel callback should be called
        std::cout << std::endl;

        std::cout << "sdk_client::call_smth: calling callback (CbAuth)\n";
        (*cb_) (CbAuth {}); // as auth callback is not defined, base callback should be called.
        std::cout << std::endl;
    }

    callee_base* cb_;
};

// Users callbacks class. Only Base and Channel callbacks defined. Auth is not defined.
struct user_callback
{
    void operator() (CbBase const& cb) const { std::cout << "called user_callback (CbBase)\n"; }
    void operator() (CbChannel const& cb) const { std::cout << "called user_callback (CbChannel)\n";  }
};

int main ()
{
    user_callback my_callback;

     sdk_client cl; // declare sdk object
     cl.set_user_callback (my_callback); // set user callbacks object
     cl.call_smth (); // call user callbacks
}