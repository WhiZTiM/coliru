#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <boost/optional.hpp>

#include <vector>

#include <iostream>

template <size_t N>
struct BufferingWriter{
    struct OutputIterator{
        char& operator*(){
            return *pointer;
        }
        
        OutputIterator& operator++(){
            if(bw){
                pointer = (*bw)++;
            }
            return *this;
        }
        
        void operator++(int){
            if(bw){
                pointer = (*bw)++;
            }
        }
        
        friend BufferingWriter;
        
        private:
        BufferingWriter* bw = nullptr;
        char* pointer;
    };
    friend OutputIterator;
    
    OutputIterator getIterator(){
        OutputIterator result;
        result.bw = this;
        result.pointer = &(buffer[end]);
        return result;
    };
    
    ~BufferingWriter(){
        flush();
    }
    
    private:  
    char* operator++(int){
        ++end;
        if(end == N){
            flush();
        }
        return &(buffer[end]);
    }
    
    void flush(){
        for(auto i = 0u; i < end; ++i){
            std::cout << buffer[i];
        }
        std::cout << std::endl;
        end = 0;
    }
    
    char buffer[N];
    size_t end = 0;
};

int main(){
    using boost::spirit::karma::generate;
    using boost::spirit::karma::lit;
    using boost::spirit::karma::uint_;
    using boost::spirit::karma::int_;
    using boost::spirit::ascii::string;
    
    BufferingWriter<28> bw;
    
    generate(bw.getIterator(), int_(1) << lit(' ') << string("quick brown fox jumps ") << int_(0) << lit('v') << uint_(3) << string("r the lazy dog"));
    generate(bw.getIterator(), lit('-'));
    generate(bw.getIterator(), int_(1) << lit(' ') << string("quick brown fox jumps ") << int_(0) << lit('v') << uint_(3) << string("r the lazy dog"));
    generate(bw.getIterator(), lit('-'));
    generate(bw.getIterator(), string("tre tigri contro tre tigri"));
    generate(bw.getIterator(), lit('-'));
    generate(bw.getIterator(), int_(1) << lit(' ') << string("quick brown fox jumps ") << int_(0) << lit('v') << uint_(3) << string("r the lazy dog"));
    generate(bw.getIterator(), lit('-'));
    generate(bw.getIterator(), int_(1) << lit(' ') << string("quick brown fox jumps ") << int_(0) << lit('v') << uint_(3) << string("r the lazy dog"));
    
    return 0;
}
