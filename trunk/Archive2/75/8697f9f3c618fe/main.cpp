#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <mutex>
#include <sstream>
#include <iostream>
#include <type_traits>
#include <condition_variable>
#include <boost/optional.hpp>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

/**
 * Represents the szPriorityLevel field in the
 * ModuleNamesTable<p>
 *
 * the szPriority Field contains a channel, priority character
 * [A-Z] (from highest priority to -lowest priority)
 * and an optional sequence number.
 */
class PriorityLevel {
public:
    /**
     *
     * @param rChannel [in] channel number
     * @param priorityChar
     *                 [in] priority character - upper case
     *                 ASCII char [A-Z] where A represents the
     *                 highest priority
     * @param rSequenceNum
     *                 [in] optional sequence number [1-N] -
     *                 which when present is used to schedule
     *                 usage with the thread pool.  If this is
     *                 present it represents a lower priority level
     *                 compared to just a channel and priority
     *                 character.
     */
    explicit PriorityLevel(
        const int32_t& rChannel = 0,
        const char priorityChar = 'Z',
        const boost::optional<int32_t>& rSequenceNum =
        boost::optional<int32_t>())
        : mChannel(rChannel)
        , mPriorityChar(priorityChar & ~(1 << 5))
        , mSequenceNum(rSequenceNum)
    {}

    // copy constructor
    PriorityLevel(const PriorityLevel& rhs)
        : mChannel(rhs.mChannel)
        , mPriorityChar(rhs.mPriorityChar)
        , mSequenceNum(rhs.mSequenceNum)
    {}

    // move constructor
    PriorityLevel(PriorityLevel&& rhs)
        : mChannel(std::move(rhs.mChannel))
        , mPriorityChar(std::move(rhs.mPriorityChar))
        , mSequenceNum(std::move(rhs.mSequenceNum)) {
        // reset optionals - not really necessary
        rhs.mSequenceNum = boost::none;
    }

    // non-throwing-swap idiom
    inline void swap(PriorityLevel& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // no need to swap base members - as we are topmost class
        swap(mChannel, rhs.mChannel);
        swap(mPriorityChar, rhs.mPriorityChar);
        swap(mSequenceNum, rhs.mSequenceNum);
    }

    // non-throwing copy-and-swap idiom unified assignment
    PriorityLevel& operator=(PriorityLevel rhs) {
        rhs.swap(*this);
        return *this;
    }

    /**
     * comparator that orders the elements in the
     * priority_queue<p>
     * Implemented via a lexicographical comparison using
     * std::tuple<T...> as a helper. Tuple comparison works as
     * follows: compares the first elements, if they are equivalent,
     * compares the second elements, if those are equivalent,
     * compares the third elements, and so on. All comparison
     * operators are short - circuited; they do not access tuple
     * elements beyond what is necessary to determine the result of
     * the comparison. note that the presence of the sequence number
     * assigns a lower priority (bigger value 1) contribution to the
     * lexicographical nature of the comparison<p>
     * Note: presence of sequence number => lower priority
     *
     * @param rhs    [in] PriorityLevel to compare against
     *
     * @return 'true' if this has lower priority than rhs
     */
    inline bool operator<(const PriorityLevel& rhs) const {
        // presence of sequence number => lower priority
        const auto seqNum = mSequenceNum ? /*mSequenceNum.get()*/0 : 1;
        const auto rhsSeqNum = rhs.mSequenceNum ? /*rhs.mSequenceNum.get()*/0 : 1;
        const auto prtyChar = 'Z' - mPriorityChar;
        const auto rhsPrtyChar = 'Z' - rhs.mPriorityChar;
        // use lhs > rhs to fix priority inversion
        return std::tie(mChannel, prtyChar, seqNum) >
            std::tie(rhs.mChannel, rhsPrtyChar, rhsSeqNum);
    }

    // operator>=() is opposite to operator<()
    inline bool operator>=(const PriorityLevel& rhs) const {
        return !(operator<(rhs));
    }

    /**
     * operator>() implemented so that it now works with std::sort()
     * preserving the strict weak ordering mathematical rules<p>
     * Note: presence of sequence number => lower priority
     *
     * @param rhs    [in] PriorityLevel to compare to
     *
     * @return 'true' if this has higher priority than rhs
     */
    inline bool operator>(const PriorityLevel& rhs) const {
        // presence of sequence number => lower priority
        auto seqNum = mSequenceNum ? /*mSequenceNum.get()*/ 0 : 1;
        auto rhsSeqNum = rhs.mSequenceNum ? /*rhs.mSequenceNum.get()*/ 0 : 1;
        const auto prtyChar = 'Z' - mPriorityChar;
        const auto rhsPrtyChar = 'Z' - rhs.mPriorityChar;
        // use lhs > rhs to fix priority inversion
        return std::tie(mChannel, prtyChar, seqNum) <
            std::tie(rhs.mChannel, rhsPrtyChar, rhsSeqNum);
    }

    /**
     * operator<=() is opposite to operator>()
     *
     * @param rhs    [in] PriorityLevel to compare to
     *
     * @return true if this <= rhs
     */
    inline bool operator<=(const PriorityLevel& rhs) const {
        return !(operator>(rhs));
    }

    /**
     * Stream insert operator<p>
     *
     * @param os     [in,out] output stream
     * @param rhs    [in] PriorityLevel to send to the output
     *               stream.
     *
     * @return a reference to the updated stream
     */
    inline friend std::ostream& operator<<(
        std::ostream& os, const PriorityLevel& rhs) {
        os << rhs.getPriorityStr();
        return os;
    }

    // channel getter
    inline int32_t getChannel() const {
        return mChannel;
    }

    // string representation of the priority string
    inline std::string getPriorityStr() const {
        std::stringstream ss;
        ss << mChannel << mPriorityChar;
        if (mSequenceNum) {
            ss << mSequenceNum.get();
        }
        return ss.str();
    }

    // channel number - top level order field
    int32_t mChannel;
    // single upper case character A=>'highest priority'
    char mPriorityChar;
    // optional field - when present indicates start order
    boost::optional<int32_t> mSequenceNum;
};

template<typename T>
struct ptr_less {
    bool operator()(
        const T& lhs, const T& rhs) {
        return *lhs < *rhs;
    }
};

//template<typename T, typename Cont = std::queue<std::shared_ptr<T>>>
template<typename T, typename Cont = std::priority_queue<std::shared_ptr<T>, std::vector<std::shared_ptr<T>>, ptr_less<std::shared_ptr<T>>>>
class UtlThreadSafeQueue {
private:
    mutable std::mutex mut;
    Cont data_queue;
    std::condition_variable data_cond;
    std::size_t capacity;
    std::atomic<bool> shutdownFlag;
public:
    // default constructor
    explicit UtlThreadSafeQueue(const size_t& rCapacity =
        std::numeric_limits<std::size_t>::max())
        : mut()
        , data_queue()
        , data_cond()
        , capacity(rCapacity)
        , shutdownFlag(false)
    {}

    // copy constructor
    UtlThreadSafeQueue(const UtlThreadSafeQueue& rhs)
        : mut()
        , data_queue()
        , data_cond()
        , capacity(rhs.capacity)
        , shutdownFlag(rhs.shutdownFlag)
    {
        std::lock_guard<std::mutex> lock(rhs.mut);
        data_queue = rhs.data_queue;
    }

    // move constructor
    UtlThreadSafeQueue(UtlThreadSafeQueue&& rhs)
        : mut(std::move(rhs.mut))
        , data_queue(std::move(rhs.data_queue))
        , data_cond(std::move(rhs.data_cond))
        , capacity(std::move(rhs.capacity))
        , shutdownFlag(std::move(rhs.shutdownFlag))
    {}

    // non-throwing copy-and-swap idiom unified assignment
    inline UtlThreadSafeQueue& operator=(UtlThreadSafeQueue rhs) {
        rhs.swap(*this);
        return *this;
    }

    // non-throwing copy-and-swap idiom
    inline void swap(UtlThreadSafeQueue& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // swap base members
        // ... no base members
        // swap members here
        swap(mut, rhs.mut);
        swap(data_queue, rhs.data_queue);
        swap(data_cond, rhs.data_cond);
        swap(capacity, rhs.capacity);
        swap(shutdownFlag, rhs.shutdownFlag);
    }

    // virtual destructor
    virtual ~UtlThreadSafeQueue() = default;

    // accept lvalue-references to shared_ptr<U> if U is a derived from T
    template<typename U>
    inline std::enable_if_t<std::is_base_of<T, U>::value> push(const std::shared_ptr<U>& ptr)
    {
        std::unique_lock<std::mutex> lock(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lock, [this]{
            return (data_queue.size() < capacity) || shutdownFlag;
        });
        if (!shutdownFlag) {
            data_queue.emplace(ptr); // copy the pointer
        }
        data_cond.notify_one();
    }

    // accept rvalue-references to shared_ptr<U> if U is a derived from T
    template<typename U>
    inline std::enable_if_t<std::is_base_of<T, U>::value> push(std::shared_ptr<U>&& ptr)
    {
        std::unique_lock<std::mutex> lock(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lock, [this]{
            return (data_queue.size() < capacity) || shutdownFlag;
        });
        if (!shutdownFlag) {
            data_queue.emplace(std::move(ptr)); // move the pointer
        }
        data_cond.notify_one();
    }

    // perfect forwarding aware push - this works great with non std::shared_ptr types!
    template<typename U>
    inline std::enable_if_t<std::is_base_of<T, std::decay_t<U>>::value> push(U&& value) {
        std::unique_lock<std::mutex> lock(mut);
        // only add the value on the stack if there is room
        data_cond.wait(lock, [this]{
            return (data_queue.size() < capacity) || shutdownFlag;
        });
        data_queue.emplace(std::make_shared<
            std::decay_t<U>> (std::forward<U>(value)));
        data_cond.notify_one();
    }

    // wait for non empty lambda condition before returning shared pointer to value
    inline std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lock(mut);
        data_cond.wait(lock, [this]{
            return !data_queue.empty() || shutdownFlag;
        });
        if (!shutdownFlag) {
            auto res = std::move(data_queue./*front*/top());
            data_queue.pop();
            return std::move(res);
        }
        return nullptr;
    }

    // return value in specified reference indicating whether
    // value successfully returned or not
    inline bool try_pop(std::shared_ptr<T>& rValue) {
        std::lock_guard<std::mutex> lock(mut);
        if (data_queue.empty()) {
            rValue.reset();
            return false;
        } else {
            rValue = std::move(data_queue./*front*/top());
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
            auto res = std::move(data_queue./*front*/top());
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
    std::priority_queue<PriorityLevel> priorityQ;        
    std::vector<PriorityLevel>  testPriorites = {
        PriorityLevel(2, 'A', 1),
        PriorityLevel(1, 'A'),
        PriorityLevel(1, 'B', 1),
        PriorityLevel(2, 'A'),
        PriorityLevel(1, 'B', 3),
        PriorityLevel(2, 'A', 1),
        PriorityLevel(1, 'B', 2),
        PriorityLevel(2, 'A', 1),
        PriorityLevel(5, 'A'),
        PriorityLevel(5, 'A', 1),
        PriorityLevel(5, 'A', 2),
        PriorityLevel(5, 'A', 3),
        PriorityLevel(5, 'B'),
        PriorityLevel(5, 'B', 1)
    };

    UtlThreadSafeQueue<PriorityLevel> priorityIPCQueue;    
    
    UtlThreadSafeQueue<PriorityLevel, std::queue<std::shared_ptr<PriorityLevel>>> priorityIPCQueue1;
    const auto& broken =  priorityIPCQueue1.wait_and_pop();


    std::cout << "unordered priorities" << std::endl;
    std::cout << "====================" << std::endl;
    for (const auto& next : testPriorites) {
        std::cout << next << std::endl;
        priorityIPCQueue.push(next);
    }
    std::cout << std::endl;

    std::cout << "priority IPC queue" << std::endl;
    std::cout << "==================" << std::endl;
    
    // kick off 3 parallel threads to work on the shared job queue
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 3; i++) {
        auto fut = std::async(std::launch::async, [](UtlThreadSafeQueue<PriorityLevel>& rJobQueue) {
            while (!rJobQueue.empty()) {
                const auto& pNext =  rJobQueue.wait_and_pop();
                if (pNext) {
                    std::cout << "threadID[" << std::this_thread::get_id() << "]" << *pNext << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }
        }, std::ref(priorityIPCQueue));
        futures.push_back(std::move(fut));
        // now taht the threads were launched asynchronously
        // let them do their work - sleep sufficiently here before collecting the results
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    
    std::for_each(futures.begin(), futures.end(), [](std::future<void>& fut) {
        // this kicks off the threads
        std::cout << "here" << std::endl;
        fut.wait();
    });
}
