#include <iostream>
#include <utility>

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
