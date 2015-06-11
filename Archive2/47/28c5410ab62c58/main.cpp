
#include <iostream>
#include <array>
#include <algorithm>


typedef unsigned long * const SCR_LONG_PTR;

template <class T, std::size_t kMaxCount>
class fixed_vector {
    public:
        fixed_vector() : count_(0) {}
        
        std::size_t count() const {
            return count_;
        }
        
        void push_back(T const &element) {
            elements_[count_++] = element;
        }
        
        void erase
        
    private:
        std::array<T, kMaxCount> elements_;
        std::size_t count_;
};

class SignalDefinition {
    public:
        SignalDefinition(int value) :
            value_(value)
        { }
        
        friend bool operator==(SignalDefinition const &lhs, SignalDefinition const &rhs);
        
    private:
        int value_;
};

bool operator==(SignalDefinition const &lhs, SignalDefinition const &rhs) {
    return lhs.value_ == rhs.value_;
}

class SignalMonitoringServer {
    public:    
        unsigned int signalCount() const {
            return signal_definitions_.count();
        }
        
        void Monitor(SignalDefinition const &definition) {
            signal_definitions_.push_back(definition);
        }
        
        void Unmonitor(SignalDefinition const &definition) {
            signal_definitions_.erase(
                std::remove(
                    signal_definitions_.begin(), 
                    signal_definitions_.end(), 
                    definition
                ), 
                signal_definitions_.end()
            );
        }
        
        void UnmonitorAll() {
            signal_definitions_.clear();
        }
        
        // void ForEachSignal(boost::function<void (SignalDefinition const &)> iterate);
        
    private:
        fixed_vector<SignalDefinition, 64> signal_definitions_;
};

int main() {
    SignalMonitoringServer sigmon_server;
    
    SignalDefinition sig0(0);
    SignalDefinition sig1(1);
    SignalDefinition sig2(2);
    
    sigmon_server.Monitor(sig0);
    sigmon_server.Monitor(sig1);
    sigmon_server.Monitor(sig2);
    
    std::cout << "Signal count = " << sigmon_server.signalCount() << std::endl;
    
    sigmon_server.Unmonitor(sig1);
    
    std::cout << "Signal count = " << sigmon_server.signalCount() << std::endl;
}