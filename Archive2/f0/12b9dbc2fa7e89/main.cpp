#include <iostream>
#include <boost/asio.hpp>

/// @brief Auxiliary function to create a shared unique ptr.
template<class T, class...Args >
std::shared_ptr<std::unique_ptr<T>> make_shared_unique(Args&&... args)
{
  return std::make_shared<std::unique_ptr<T>>(
      std::make_unique<T>(std::forward<Args>(args)...));
}

/// @brief Legacy function that cannot change.
void do_something(std::unique_ptr<std::string> data) {}

/// @brief Test compiling Boost.Asio usage.
void test_compile()
{
  boost::asio::io_service io_service;
  boost::asio::ip::tcp::socket socket(io_service);

  auto data = make_shared_unique<std::string>("abc");
  auto buffer = boost::asio::buffer(**data); // Note double defereference.

  boost::asio::async_write(socket, buffer,
    // Copy the shared_ptr so that the handler will be CopyConstructible.
    [data](
        const boost::system::error_code& error,
        size_t byte_transferred
    ) mutable
    {
      // Transfer ownership.
      do_something(std::move(*data));
    });
}

/// @brief Mockup for testing lifetime.
struct foo
{
  foo(bool& alive) : alive_(alive) { alive_ = true;  }
  ~foo()                           { alive_ = false; } 
  foo(const foo&&) = delete;  
  bool& alive_;
};

int main()
{
  // Case 1: not transferred.
  {
    bool alive = false;
    assert(!alive);
    {
      auto s_p = make_shared_unique<foo>(std::ref(alive));
      assert(alive);
    }
    assert(!alive);
  }
  
  // Case 2: transfer ownership.
  {
      bool alive = false;
      assert(!alive);
      auto s_p = make_shared_unique<foo>(std::ref(alive));
      assert(alive);
      auto u_p = std::move(*s_p); // Transfer ownership.
      s_p.reset();                // Destroy shared_ptr.
      assert(alive);              // foo should still be alive (managed by u_p).
      u_p.reset();                // Reset u_p, which should destroy foo.
      assert(!alive);             // Verify foo is destroyed.
  }
}