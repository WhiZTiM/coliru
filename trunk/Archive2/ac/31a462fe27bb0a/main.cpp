#include <iostream>
#include <string>
#include <vector>
#include <atomic>
#include <queue>
#include <limits>
#include <memory>
#include <mutex>
#include <condition_variable>

struct BaseMessage {
    BaseMessage(){}
};

struct DerivedMessage : public BaseMessage {
    DerivedMessage(const int value) : mValue(value) {}
    int mValue;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

template<typename T>
class UtlThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
    std::size_t capacity;
    std::atomic<bool> shutdownFlag;
public:
    explicit UtlThreadSafeQueue(const size_t& rCapacity =
        std::numeric_limits<std::size_t>::max())
        : mut()
        , data_queue()
        , data_cond()
        , capacity(rCapacity)
        , shutdownFlag(false)
    {}

    UtlThreadSafeQueue(UtlThreadSafeQueue const& rhs) {
        std::lock_guard<std::mutex> lock(rhs.mut);
        data_queue = rhs.data_queue;
    }

    virtual ~UtlThreadSafeQueue() = default;

    // move aware push
    inline void push(T&& value) {
        std::unique_lock<std::mutex> lock(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lock,[this]{return (data_queue.size() < capacity) || shutdownFlag;});
        data_queue.emplace(std::forward<T>(value));
        data_cond.notify_one();
    }

    // wait for non empty lambda condition before returning value
    inline void wait_and_pop(T& rValue) {
        std::unique_lock<std::mutex> lock(mut);
        data_cond.wait(lock,[this]{return !data_queue.empty();});
        // ideally should return an invalid value
        if (!shutdownFlag) {
            rValue = data_queue.front();
            data_queue.pop();
        }
    }

    // wait for non empty lambda condition before returning shared pointer to value
    inline std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lock(mut);
        data_cond.wait(lock,[this]{return !data_queue.empty() || shutdownFlag;});
        if (shutdownFlag) {
            std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
            data_queue.pop();
            return res;
        }
        return nullptr;
    }

    // return value in specified reference and flag indicating whether value
    // successfully returned or not
    inline bool try_pop(T& rValue) {
        std::lock_guard<std::mutex> lock(mut);
        if (data_queue.empty()) {
            return false;
        }
        rValue = data_queue.front();
        data_queue.pop();
        return true;
    }

    // return shared pointer to value - which if set to nullptr,
    // indicates container was empty at the time of the call.
    inline std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock(mut);
        if (data_queue.empty()) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }
    // thread safe method to check if the queue is empty
    // note that if it is empty
    inline bool empty() const {
        std::lock_guard<std::mutex> lock(mut);
        return data_queue.empty();
    }

    // shutdown support - wake up potentially sleeping queues
    inline void shutdown() {
        shutdownFlag = true;
        data_cond.notify_all();
    }
};

int main()
{
    UtlThreadSafeQueue<BaseMessage> dataLoadSessionQ;
    auto message = std::make_shared<DerivedMessage>(1);
    dataLoadSessionQ.push(message);    
}
