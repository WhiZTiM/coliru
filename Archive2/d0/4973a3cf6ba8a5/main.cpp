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
    BaseMessage() {}
    virtual ~BaseMessage() = default;    
    virtual std::string toString() const = 0;
};

struct IntegerMessage : BaseMessage {
    IntegerMessage(const int& rValue) 
        : BaseMessage()
        , mIntValue(rValue) 
    {}

    virtual ~IntegerMessage() = default;

    std::string toString() const {
        return std::to_string(mIntValue);
    };

    friend std::ostream& operator<<(
        std::ostream& os, const IntegerMessage& rhs) {
        os << "IntegerMessage - payload [" << rhs.mIntValue << "]" << std::endl;;
        return os;
    }    
    int mIntValue;
};

struct StringMessage : BaseMessage {
    StringMessage(const std::string& rValue) 
        : BaseMessage()
        , mStringValue(rValue) 
    {}
    
    virtual ~StringMessage() = default;

    std::string toString() const {
        return mStringValue;
    };
    
    friend std::ostream& operator<<(
        std::ostream& os, const StringMessage& rhs) {
        os << "StringMessage - payload [" << rhs.mStringValue << "]" << std::endl;;
        return os;
    }
    
    std::string mStringValue;
};

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

    // move aware push
    inline void push(std::shared_ptr<T>&& value) {
        std::unique_lock<std::mutex> lock(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lock,[this]{return (data_queue.size() < capacity) || shutdownFlag;});
        data_queue.emplace(std::move(value));
        data_cond.notify_one();
    }
    
    // wait for non empty lambda condition before returning shared pointer to value
    inline std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lock(mut);
        data_cond.wait(lock,[this]{return !data_queue.empty() || shutdownFlag;});
        if (!shutdownFlag) {
            auto res = data_queue.front();
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
        auto res = data_queue.front();
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
    dataLoadSessionQ.push(std::move(std::make_shared<IntegerMessage>(42)));
    dataLoadSessionQ.push(std::move(std::make_shared<StringMessage>("I am a string message")));
    auto msg1 = dataLoadSessionQ.wait_and_pop();
    auto msg2 = dataLoadSessionQ.wait_and_pop();
    std::cout << msg1->toString() << std::endl;
    std::cout << msg2->toString() << std::endl;
}
