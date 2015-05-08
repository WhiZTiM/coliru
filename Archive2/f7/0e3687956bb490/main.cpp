#include <boost/asio.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/signals2.hpp>
#include <iostream>
#include <boost/thread.hpp>

struct Task {
    virtual ~Task() = default;
    virtual int  Execute()           const = 0;
    virtual bool IsShutdownRequest() const { return false; }
};

struct TimeSeriesTask : Task {
    TimeSeriesTask(int id) : _id(id) {}
    virtual int  Execute()           const { return _id;   }

  private:
    int _id;
};

struct ShutdownTask : Task {
    virtual int  Execute()           const { return 0;    }
    virtual bool IsShutdownRequest() const { return true; }
};

class Manager {
  public:
    Manager() : _shutdown(true)
    { }

    void Start() {
        boost::lock_guard<boost::mutex> lk(_stateMutex);
        if (_shutdown) {
            _shutdown = false;
            _workerThread = boost::thread(&Manager::workerMain, this);
        }
    }

    void workerMain() {
        while(!_shutdown) {
            queue.consume_one([this](std::shared_ptr<Task> task) {
                if (task->IsShutdownRequest()) {
                    _shutdown = true;
                } else {
                    int result = task->Execute();
                    processResult(result);
                }
            });
        };
    }

    void processResult(unsigned int x) {
        int result = x - 1;
        std::cout << "Processing result = " << result << " on thread " << boost::this_thread::get_id() << std::endl;
    }

    void QueueData(int x) {
       if (x > 0)
            queue.push(std::make_shared<TimeSeriesTask>(x));
        else
            queue.push(std::make_shared<ShutdownTask>());
    }

    void Cleanup() {
        if (_workerThread.joinable())
            _workerThread.join();
    }

  private:
    boost::mutex _stateMutex;
    boost::atomic_bool _shutdown;
    boost::lockfree::spsc_queue<std::shared_ptr<Task>, boost::lockfree::capacity<1024> > queue;
    boost::thread _workerThread;
};

int main()
{
    Manager mgr;
    mgr.Start();

    mgr.QueueData(1);
    mgr.QueueData(2);
    mgr.QueueData(3);

    mgr.QueueData(-1);
    mgr.Cleanup();
}
