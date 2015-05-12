#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <functional>


namespace brainfuck{
    struct vm_state{
        std::vector<char> data{0};
        unsigned int data_index = 0;
        std::string program_code = "";
        unsigned int instruction_index = 0;
        
        char fetch(){
            return program_code[instruction_index++];
        }
        
        char& data_ref(){
            return data[data_index];
        }
     
        bool at_program_end(){
            return instruction_index >= program_code.length();
        }
    };
        
    struct interpretor{
        std::function<std::pair<bool, char>()> read_fn;
        std::function<void(char)> write_fn;
        
        void load_program(std::string code){
            state.program_code = code;
        }
        
        void run(){
            while(!state.at_program_end() && error_msg == ""){
                advance();
            }
        }
        
        std::string get_error_msg() const{
            return error_msg;
        }
        
        bool did_error() const{
            return error_msg != "";
        }
        
        private:
        vm_state state;
        std::string error_msg;
        
        void data_index_left(){
            if(state.data_index == 0){
                error_msg = "Tried to decrement data pointer when already at 0";
                return;
            }
            --state.data_index;
        }
        
        void data_index_right(){
            ++state.data_index;
            if(state.data_index == state.data.size()){
                state.data.emplace_back(0);
            }
        }
        
        void data_increment(){
            state.data_ref() += 1;
        }
        
        void data_decrement(){
            state.data_ref() -= 1;
        }
        
        void io_out(){
            write_fn(state.data_ref());
        }
        
        void io_in(){
            auto value = read_fn();
            if(value.first){
                state.data_ref() = value.second;
            } else {
                error_msg = "Could not read from io";
            }
        }
        
        void loop_start(){
            if(state.data_ref() == 0){
                unsigned int loop_ends = 1;
                while(loop_ends != 0){
                    char next_op = state.fetch();
                    switch (next_op){
                        case '[': ++loop_ends; break;
                        case ']': --loop_ends; break;
                        default: break;
                    }
                }
            }
        }
        
        void loop_end(){
            if(state.data_ref() != 0){
                --state.instruction_index;
                unsigned int loop_starts = 1;
                while(loop_starts != 0){
                    char next_op = state.program_code[--state.instruction_index];
                    switch (next_op){
                        case '[': --loop_starts; break;
                        case ']': ++loop_starts; break;
                        default: break;
                    }
                }
                state.fetch();
            }
        }
    
        void advance(){
            auto op_code = state.fetch();
            switch (op_code){
                case '<' : data_index_left(); break;
                case '>' : data_index_right(); break;
                case '+' : data_increment(); break;
                case '-' : data_decrement(); break;
                case '.' : io_out(); break;
                case ',' : io_in(); break;
                case '[' : loop_start(); break;
                case ']' :loop_end(); break;
                default: break;
            }
        }
    };
}

struct buffered_io{
    std::string input_buffer;
    std::string output_buffer;
    
    std::pair<bool, int> read(){
        if(marker >= input_buffer.size()){
            return std::make_pair(false, 0);
        }
        return std::make_pair(true, input_buffer[marker++]);
    }
    
    void write(char value){
        output_buffer += value;
    }
    
    private:
    unsigned int marker = 0;
};

int main()
{
    std::string hello_world_code = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    std::string echo_hi = ",>,<.>.,";
    std::string bad_decrement = "<";
    std::string bad_read = ",,,";
    
    buffered_io io;
    io.input_buffer = "Hi";
    brainfuck::interpretor vm;
    vm.read_fn = [&io]() { return io.read(); };
    vm.write_fn = [&io](char value) { io.write(value); };
    vm.load_program(bad_read);
    vm.run();
    std::cout << io.output_buffer;
    if(vm.did_error()){
        std::cout << "    " << vm.get_error_msg() << "\n";
    }
}
