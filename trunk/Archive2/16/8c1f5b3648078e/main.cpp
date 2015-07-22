#include <iostream>
#include <memory>

class Format{
    public:
        virtual const char *format_str() = 0;
        virtual char *data() = 0;
};

class SpecificFormat: public Format{
    public:
        const char *format_str(){return "SpecificFormat";}
        char *data(){return nullptr;}
};

class SpecificFormatOne: public Format{
    public:
        const char *format_str(){return "SpecificFormatOne";}
        char *data(){return nullptr;}
};

class SpecificFormatTwo: public Format{
    public:
        const char *format_str(){return "SpecificFormatTwo";}
        char *data(){return nullptr;}
};

class Parser{
    public:
        virtual std::unique_ptr<Format> get_results() = 0;
};

class SpecificParser: public Parser{
    public:
        std::unique_ptr<Format> get_results(){
            return std::make_unique<SpecificFormat>();
        }
};

class FileParser{
    public:
        FileParser(const std::string &file_path, std::unique_ptr<Parser> &&parser)
            : parser(std::move(parser)){}

        auto get_results(){
            return parser->get_results();
        }
        
    private:
        std::unique_ptr<Parser> parser;
};

int main(){
    auto parser = FileParser{"test.my_format", std::make_unique<SpecificParser>()};
    auto results = parser.get_results();
    auto data = results->data();
    
    std::unique_ptr<Format> format = std::make_unique<SpecificFormat>();
    std::cout << format->format_str() << std::endl;
    
    format = std::make_unique<SpecificFormatOne>();
    std::cout << format->format_str() << std::endl;
    
    format = std::make_unique<SpecificFormatTwo>();
    std::cout << format->format_str() << std::endl;
}
