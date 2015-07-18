#include <string>
#include <ctime>
#include <chrono>
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <fstream>

namespace CodeDiary
{

/// Base formatter is an optional CRTP interface you can use. It
/// gives your formatter access to GetCurrentTime() (see DefaultFormatter
/// or SampleFormatter)
template<typename Implementation>
class BaseFormatter
{
protected:
    static std::string Format(const std::string& msg, const std::string& type)
    {
        return Implementation::Format(msg, type);
    }

    static std::string GetCurrentTime()
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        time_t curTime = std::chrono::system_clock::to_time_t(now);

        // CAREFUL: This rVal has a newline at the end. Don't return it
        std::string rVal(ctime(&curTime));

        return std::string(std::begin(rVal), std::end(rVal) - 1);
    }

};

/// Default formatter. Just formatts the log by putting first the current time,
/// then the type and then the log itself
class DefaultFormatter : public BaseFormatter <DefaultFormatter>
{
protected:
    static std::string Format(const std::string& msg, const std::string& type)
    {
        return std::string(GetCurrentTime() + " " + type + " " + msg);
    }
};

/// Default Dispatcher. Just prints the log to std::cout
class DefaultDispatcher
{
protected:
    static void Dispatch(const std::string& msg)
    {
        std::cout << msg << std::endl;
    }
};

/// Policy:
/// Formatter   -> must have one "static std::string Format(const std::string& msg, const std::string& type)"
/// Dispatcher  -> one "static void Dispatch(const std::string& msg)"
template<typename Formatter = DefaultFormatter, typename Dispatcher = DefaultDispatcher>
class Logger : private Formatter, private Dispatcher
{
    public:

        enum class LogType
        {
            DEBUG,
            INFO,
            WARN,
            ERROR
        };

        static void Log( const std::string& msg, LogType type )
        { Dispatcher::Dispatch( Formatter::Format( msg, LogTypeToString(type) ) ); }

        static int Log( LogType type, const char* format, ... )
        {
            va_list arg_list;
            va_start( arg_list, format );
            va_list arg_list_cpy;
            va_copy( arg_list_cpy, arg_list );

            const auto nchars = std::vsnprintf( nullptr, 0, format, arg_list );
            va_end(arg_list);

            if( nchars > 0 )
            {
                std::vector<char> buffer( nchars + 1 );
                std::vsnprintf( buffer.data(), buffer.size(), format, arg_list_cpy );
                Log( { buffer.begin(), buffer.end() }, type );
            }

            va_end(arg_list_cpy);
            return nchars ;
        }

    private:
        static std::string LogTypeToString( LogType type )
        {
            switch(type)
            {
                case LogType::DEBUG:
                    return std::string("DEBUG");
                case LogType::INFO:
                    return std::string(" INFO");
                case LogType::WARN:
                    return std::string(" WARN");
                case LogType::ERROR:
                    return std::string("ERROR");
                default:
                    return std::string();
            }
        }
};

}

int main()
{
    using namespace CodeDiary;

    Logger<>::Log( "hello world", Logger<>::LogType::DEBUG );

    Logger<>::Log( Logger<>::LogType::INFO, "the value is %d%c", 2345, '!' );

}
