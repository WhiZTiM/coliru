
#include <iostream>
#include <array>
#include <algorithm>


typedef unsigned long * const SCR_LONG_PTR;  // Just a dummy RM pointer type.

// Do I even need this?  std::array already has an iterator type doesn't it?
//template <class ElemT>
//class fixed_vector_iterator
//{
//    public:
//        typedef bidirectional_iterator_tag  iterator_category;
//        typedef ElemT                       value_type;
//        typedef value_type &                reference;
//        typedef value_type *                pointer;
//        typedef int                         difference_type;
//
//        fixed_vector_iterator(pointer p_element) : p_element_(p_element) {}
//        
//        reference operator*() const { return (*p_element_); }
//        
//        fixed_vector_iterator& operator++() {  // preincrement
//            ++m_Ptr;
//            return (*this);
//        }
//    
//        fixed_vector_iterator& operator--() {  // predecrement
//            --m_Ptr;
//            return (*this);
//        }
//    
//        fixed_vector_iterator operator++(int) {  // postincrement
//            fixed_vector_iterator initial = *this;
//            ++*this;
//            return (initial);
//        }
//    
//        fixed_vector_iterator operator--(int) {  // postdecrement
//            fixed_vector_iterator initial = *this;
//            --*this;
//            return (initial);
//        }
//    
//        bool operator==(fixed_vector_iterator const &other) const {
//            return (p_element_ == other.p_element_);
//        }
//    
//        bool operator!=(fixed_vector_iterator const &other) const {
//            return (!(p_element_ == other.p_element_));
//        }
//    
//    private:
//        pointer p_element_;
//};

template <class ElemT, std::size_t kMaxSize>
class fixed_vector {    
    private:
        typedef std::array<ElemT, kMaxSize> base_type;
        
    public:
//        typedef base_type::value_type       value_type;
//        typedef base_type::reference        reference;
        typedef typename base_type::const_reference  const_reference;
        typedef typename base_type::iterator         iterator;
        typedef typename base_type::const_iterator   const_iterator;
//        typedef base_type::difference_type  difference_type;
        typedef typename base_type::size_type        size_type;
    
    
        // -- Constructors/Destructors --
        
        fixed_vector() : end_(elements_.begin()) {}
        
        
        // -- Iterators --
        
        iterator begin() {
            return elements_.begin();
        }
        
        iterator end() {
            return end_;
        }
        
        const_iterator cend() const {
            return end_;
        }
        
        
        // -- Capacity --
        
        size_type size() const {  // Implement our own size(); std::array's doesn't fit our needs.
            return std::distance(elements_.cbegin(), cend());
        }
        
        size_type max_size() const {
            return elements_.size();
        }
        
        
        // -- Modifiers --
        
        void clear() {
            end_ = begin();
        }
        
        iterator erase( iterator first, iterator last ) {  // Add erase() functionality; std::array doesn't provide this.
            // The to-be-erased elements now constitute a "gap" in the container. We
            //  slide the not-to-be-erased elements toward the beginning of the container
            //  in order to close the gap.
            iterator next_valid = first;
            while(last != end()) {
                *first = *last;
                ++first; ++last;
            }
            end_ = first;
            return next_valid;
        }
        
        void push_back( const_reference element ) {  // Add push_back() functionality; std::array doesn't provide this.
            elements_.at(size()) = element;
            end_++;
        }
        
    private:
        base_type elements_;
        iterator end_;
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