#include <iostream>
#include <string>
#include <vector>
#include <atomic>
#include <queue>
#include <limits>
#include <memory>
#include <mutex>
#include <condition_variable>

class UtlMessage
{
public:
    // message type
    using MessageType = enum {
        UNSPECIFIED = 0,
        OS_SHUTDOWN,           // Task shutdown request message
        OS_TIMER,              // Timer request messages
        OS_EVENT,              // Event notification messages
        USER_START = 128
    };

    // default constructor
    UtlMessage(const MessageType& rMessageType = UNSPECIFIED, const uint8_t messageSubType = 0)
        : mMessageType(rMessageType)
        , mMessageSubType(messageSubType)
    {}

    // copy constructor
    UtlMessage(const UtlMessage& rhs) = default;

    // move constructor
    UtlMessage(UtlMessage&& rhs)
        : mMessageType(std::move(rhs.mMessageType))
        , mMessageSubType(std::move(rhs.mMessageSubType))
    {}

    // non-throwing-swap idiom
    inline void swap(UtlMessage& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // no need to swap base members - as we are topmost class
        swap(mMessageType, rhs.mMessageType);
        swap(mMessageSubType, rhs.mMessageSubType);
    }
    
    

    // destructor
    virtual ~UtlMessage() = 0;

    // non-throwing copy-and-swap idiom unified assignment
    // Abstract Base Class - not possible
    // UtlMessage& operator=(UtlMessage rhs);

    // return the message type
    inline virtual MessageType getMessageType() const {
        return mMessageType;
    }

    // return the message subtype
    inline virtual uint8_t getMessageSubType() const {
        return mMessageSubType;
    }
protected:
    MessageType mMessageType;
    uint8_t     mMessageSubType;
};

inline UtlMessage::~UtlMessage() = default;

class DataLoadSessionMsg : public UtlMessage
{
public:
    DataLoadSessionMsg(
        const MessageType& rMessageType = UtlMessage::UNSPECIFIED,
        const uint8_t msgSubType = 0, 
        const std::string& rSessionHandle = std::string(),
        const int& rPercentComplete = -1,
        const std::string& rLoadPartNumber = std::string(),
        const std::string& rOptUserStr = std::string())
        : UtlMessage(rMessageType, msgSubType)
        , mSessionHandle(rSessionHandle)
        , mPercentComplete(rPercentComplete)
        , mLoadPartNumber(rLoadPartNumber)
        , mOptUserStr(rOptUserStr)
    {}

    // copy constructor
    DataLoadSessionMsg(const DataLoadSessionMsg& rhs) = default;

    // move constructor
    DataLoadSessionMsg(DataLoadSessionMsg&& rhs)
        : mSessionHandle(std::move(rhs.mSessionHandle))
        , mPercentComplete(std::move(rhs.mPercentComplete))
        , mLoadPartNumber(std::move(rhs.mLoadPartNumber))
        , mOptUserStr(std::move(rhs.mOptUserStr))
    {}

    // non-throwing copy-and-swap idiom unified assignment
    inline DataLoadSessionMsg& operator=(DataLoadSessionMsg rhs) {
        rhs.swap(*this);
        return *this;
    }

    // non-throwing-swap idiom
    inline void swap(DataLoadSessionMsg& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // swap base members
        UtlMessage::swap(rhs);
        // swap members here
        swap(mSessionHandle, rhs.mSessionHandle);
        swap(mPercentComplete, rhs.mPercentComplete);
        swap(mLoadPartNumber, rhs.mLoadPartNumber);
        swap(mOptUserStr, rhs.mOptUserStr);
    }

    // Destructor
    virtual ~DataLoadSessionMsg() = default;

    // SessionHandle getter
    inline std::string getSessionHandle() const {
        return mSessionHandle;
    }

    // PercentComplete getter
    inline int getPercentComplete() const {
        return mPercentComplete;
    }

    // PartNumber getter
    inline std::string getLoadPartNumber() const {
        return mLoadPartNumber;
    }

    // OptUserStr getter
    inline std::string getOptUserStr() const {
        return mOptUserStr;
    }
private:
    std::string mSessionHandle;
    int mPercentComplete;
    std::string mLoadPartNumber;
    std::string mOptUserStr;
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

   
   // accept lvalue-references to shared_ptr<U> if U is a base of T
    template<typename U>
    inline std::enable_if_t<std::is_base_of<T,U>::value> push(const std::shared_ptr<U>& ptr)
    {
        std::unique_lock<std::mutex> lock(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lock, [this]{
            return (data_queue.size() < capacity) || shutdownFlag; 
        });
        data_queue.emplace(ptr); // copy the pointer
        data_cond.notify_one();  
    }
    
    // accept rvalue-references to shared_ptr<U> if U is a base of T
    template<typename U>
    inline std::enable_if_t<std::is_base_of<T,U>::value> push(std::shared_ptr<U>&& ptr)
    {
        std::unique_lock<std::mutex> lock(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lock, [this]{
            return (data_queue.size() < capacity) || shutdownFlag; 
        });
        data_queue.emplace(std::move(ptr)); // move the pointer
        data_cond.notify_one();  
    }

    // perfect forwarding aware push - this works grea with non std::shared_ptr typest!  Thanks Alejandro
    template<typename U>
    inline std::enable_if_t<std::is_base_of<T, std::decay_t<U>>::value> push(U&& value) {
        std::unique_lock<std::mutex> lock(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lock, [this]{
            return (data_queue.size() < capacity) || shutdownFlag; 
        });
        data_queue.emplace(std::make_shared<
            std::decay_t<U>>(std::forward<U>(value)));
        data_cond.notify_one();
    }
    
    // wait for non empty lambda condition before returning shared pointer to value
    inline std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lock(mut);
        data_cond.wait(lock, [this]{
            return !data_queue.empty() || shutdownFlag;
        });
        if (!shutdownFlag) {
            auto res = std::move(data_queue.front());
            data_queue.pop();
            return res;
        }
        return nullptr;
    }

    // return value in specified reference and flag indicating whether value
    // successfully returned or not
    inline bool try_pop(std::shared_ptr<T>& rValue) {
        std::lock_guard<std::mutex> lock(mut);
        if (data_queue.empty()) {
            rValue.reset();
            return false;
        } else {
            rValue = data_queue.front();
            data_queue.pop();
            return true;
        }
    }

    // return shared pointer to value - which if set to nullptr,
    // indicates container was empty at the time of the call.
    inline std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock(mut);
        if (data_queue.empty()) {
            return std::shared_ptr<T>();
        } else {
            auto res = data_queue.front();
            data_queue.pop();
            return std::move(res);
        }
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
    UtlThreadSafeQueue<UtlMessage> dataLoadSessionQ(10);
    auto pDLSMessage = std::make_shared<DataLoadSessionMsg>(
        UtlMessage::USER_START, 3, "192.168.1.1", 0);
    dataLoadSessionQ.push(pDLSMessage); // will call push(const std::shared_ptr<U>&)
    while (!dataLoadSessionQ.empty()) {
        std::cout << dataLoadSessionQ.wait_and_pop()->getMessageType() << std::endl;   
    }
}
