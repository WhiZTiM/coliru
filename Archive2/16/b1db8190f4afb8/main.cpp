#include <thread>
#include <atomic>
#include <iostream>
#include <boost/python.hpp>

/// @brief RAII class used to lock and unlock the GIL.
class gil_lock
{
public:
  gil_lock()  { state_ = PyGILState_Ensure(); }
  ~gil_lock() { PyGILState_Release(state_);   }
private:
  PyGILState_STATE state_;
};

struct foo
{
  foo() : running(false) {}
  ~foo() { stop(); }

  void start()
  {
    namespace python = boost::python;
    running = true;
    thread = std::thread([this]
      {
        while (running)
        {
          {
            gil_lock lock;
            std::cout << python::len(messages) << std::endl;
            messages.append(python::len(messages));
          } // Release GIL.
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
      });
  }

  void stop()
  {
    if (running)
    {
      running = false;
      thread.join();
    }
  }

  std::thread thread;
  boost::python::list messages;
  std::atomic<bool> running;
};

BOOST_PYTHON_MODULE(example)
{
  // Force the GIL to be created and initialized.  The current caller will
  // own the GIL.
  PyEval_InitThreads();

  namespace python = boost::python;
  python::class_<foo, boost::noncopyable>("Foo", python::init<>())
    .def("start", &foo::start)
    .def("stop", &foo::stop)
    ;
}