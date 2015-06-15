
#include <iostream>
#include <array> 
#include <algorithm>
#include <stdexcept>


typedef unsigned long * const SCR_LONG_PTR;  // Just a dummy RM pointer type.

template <class ElementT, std::size_t kMaxSize>
class fixed_vector {
    public:
        // -- Constructors/Destructors --
        
        fixed_vector() : end_(0) {}
        
        
        // -- Capacity --
        
        std::size_t size() const {
            return end_;
        }
        
        std::size_t max_size() const {
            return kMaxSize;
        }
        
        
        // -- Accessors
        
        ElementT& at( unsigned int index ) {
            if ( index < 0 || index >= end_ ) {
                throw std::out_of_range("index");
            } else {
                return elements_[index];
            }
        }
        
        
        // -- Mutators --
        
        void clear() {
            end_ = 0;
        }
        
        void remove_first( ElementT const &element ) {
            for( unsigned int i = 0; i != end_; ++i ) {
                if( at( i ) == element ) {
                    erase( i, i + 1 );
                }
            }
        }
        
        unsigned int erase( unsigned int first, unsigned int last ) {
            // The to-be-erased elements now constitute a "gap" in the container. We
            //  slide the not-to-be-erased elements toward the beginning of the container
            //  in order to close the gap.
            unsigned int next_valid = first;
            while( last != end_ ) {
                at( first++ ) = at( last++ );
            }
            end_ = first;
            return next_valid;
        }
        
        void push_back( ElementT const &element ) {
            at( end_++ ) = element;
        }
        
    private:
        ElementT elements_[kMaxSize];
        unsigned int end_;
};

class SignalDefinition {
    public:
        SignalDefinition() : value_(0) { }
    
        SignalDefinition(int value) : value_(value) { }
        
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
            return signal_definitions_.size();
        }
        
        void Monitor(SignalDefinition const &definition) {
            signal_definitions_.push_back(definition);
        }
        
        void Unmonitor(SignalDefinition const &definition) {
            signal_definitions_.remove_first(definition);
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
    
    std::cout << "sigmon_server.signalCount() = " << sigmon_server.signalCount() << std::endl;
    
    SignalDefinition sig0(0);
    SignalDefinition sig1(1);
    SignalDefinition sig2(2);
    
    sigmon_server.Monitor(sig0);
    sigmon_server.Monitor(sig1);
    sigmon_server.Monitor(sig2);
    
    SCR_LONG_PTR refmem = reinterpret_cast<SCR_LONG_PTR>(&sigmon_server);
    SignalMonitoringServer &sigmon_server_2 = reinterpret_cast<SignalMonitoringServer &>(*refmem);
    std::cout << "sigmon_server_2.signalCount() = " << sigmon_server_2.signalCount() << std::endl;
    
    sigmon_server_2.Unmonitor(sig1);
    
    std::cout << "sigmon_server.signalCount() = " << sigmon_server.signalCount() << std::endl;
}