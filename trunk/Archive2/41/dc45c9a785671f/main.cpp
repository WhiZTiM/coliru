#include <iostream>
#include <memory>
#include <atomic>
#include <thread>
#include <chrono>
#include <list>

std::atomic<int> CondInPop1(0), CondToDelete(0), CondInPop0(0), CondInPopNot0(0), CondInPopNot1(0);

template<typename T>
class TLockFreeStack {
private:
    struct TNode {
        T Data;
        TNode *Next;

        TNode(const T &data)
            : Data(data)
        {}
    };

    std::atomic<TNode*> Head;
    std::atomic<size_t> InPop;
    std::atomic<TNode*> Pending;

    void DoDelete(TNode *node) {
        for (; node;) {
            TNode *t = node;
            node = node->Next;
            delete t;
        }
    }

    void DeleteNode(TNode *node) {
        if (InPop == 1) {
            ++CondInPop1;
            TNode *toDelete = Pending.exchange(nullptr);
            if (toDelete) {
                ++CondToDelete;
                if (--InPop == 0) {
                    ++CondInPop0;
                    DoDelete(toDelete);
                }
                else {
                    ++CondInPopNot0;
                    TNode *last = toDelete;
                    while (last->Next)
                        last = last->Next;
                    last->Next = Pending;
                    while (!Pending.compare_exchange_weak(last->Next, toDelete))
                        ;
                }
            }
            else {
                --InPop;
            }
            delete node;
        }
        else {
            ++CondInPopNot1;
            node->Next = Pending;
            while (!Pending.compare_exchange_weak(node->Next, node))
                ;
            --InPop;
        }
    }

public:
    TLockFreeStack()
        : Head(nullptr)
        , InPop(0)
        , Pending(nullptr)
    {}

    void Push(const T &data) {
        TNode *node = new TNode(data);
        node->Next = Head.load();
        while (!Head.compare_exchange_weak(node->Next, node))
            ;
    }

    bool Pop(T &result) {
        ++InPop;
        TNode *head = Head;
        while (head && !Head.compare_exchange_weak(head, head->Next))
            ;
        if (head) {
            result = std::move(head->Data);
            DeleteNode(head);
            return true;
        }
        else {
            --InPop;
            return false;
        }
    }

    T Pop() {
        T result; 
        return Pop(result) ? result : T();
    }
};
using namespace std;
int main() {
    std::cout << std::thread::hardware_concurrency() << std::endl;
    TLockFreeStack<int> s;
    std::list<thread> threads;
    const size_t THREADS = 10  ;
    const size_t PUSHS = 100000;
    const size_t READERS = 2;
    for (size_t i = 0; i < READERS; ++i) {
        threads.push_back(
            thread([&]() {
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            long long sum = 0;
            for (size_t i = 0; i < THREADS * PUSHS; ++i) {
                int t;
                if (s.Pop(t)) {
                    sum += t;
                }
                else {
                    std::this_thread::yield();
                }
            }
            std::cout << sum << " " << (static_cast<long long>(PUSHS)* (PUSHS - 1) / 2 * THREADS) << std::endl;
        }));
    }
    for (size_t t = 0; t < THREADS; ++t) {
        threads.push_back(thread([&]() {
            for (int i = 0; i < PUSHS; ++i) {
                s.Push(i);
            }
        }));
    }
    while (!threads.empty()) {
        threads.front().join();
        threads.pop_front();
    }
    std::cout << CondInPop1 << " " << CondToDelete << " " << CondInPop0 << " "
        << CondInPopNot0 << " " << CondInPopNot1 << std::endl;

    return 0;
}

