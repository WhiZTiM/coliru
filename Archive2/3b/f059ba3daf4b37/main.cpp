
#include <iostream>

typedef enum android_LogPriority {
    ANDROID_LOG_UNKNOWN = 0,
    ANDROID_LOG_DEFAULT,
    ANDROID_LOG_VERBOSE,
    ANDROID_LOG_DEBUG,
    ANDROID_LOG_INFO,
    ANDROID_LOG_WARN,
    ANDROID_LOG_ERROR,
    ANDROID_LOG_FATAL,
    ANDROID_LOG_SILENT,
} android_LogPriority;


int fake__android_log_print(int prio, const char *tag, const char *fmt, ...)
{
  std::cout << prio << " " << tag << ": " << fmt << std::endl;
  return 0;
}


#include <boost/log/attributes.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/expressions/keyword.hpp>

namespace boost_android_logging
{

  BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", android_LogPriority)
BOOST_LOG_ATTRIBUTE_KEYWORD(module, "Module", std::string)

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;

struct android_sink_backend : public sinks::basic_sink_backend<logging::sinks::concurrent_feeding>
{
    void consume(const logging::record_view& rec)
    {
        android_LogPriority log_sev = rec[severity].get();
        const char* log_msg = rec[expr::smessage].get().c_str();
        
        const char* log_module = "unknown";

        if (rec[module])
        {
            log_module = rec[module].get().c_str();
        }
        
        // forward to actual logging function
        fake__android_log_print(log_sev, log_module, log_msg);
    }
};

typedef boost::log::sources::severity_logger<android_LogPriority> Logger;
  
void init()
{
    logging::add_common_attributes();
    typedef sinks::synchronous_sink<android_sink_backend> android_sink;
    boost::shared_ptr<android_sink> sink = boost::make_shared<android_sink>();

    sink->set_filter(severity >= ANDROID_LOG_INFO);
    logging::core::get()->add_sink(sink);
}

void shutdown()
{
    logging::core::get()->remove_all_sinks();
}

} // namespace boost_android_logging


#define SET_MODULE(logger,log_module)  logger.add_attribute(boost_android_logging::module.get_name(), boost::log::attributes::constant<std::string>(#log_module));

struct Demo
{
  Demo()
  {
    SET_MODULE(logger, Demo);
    BOOST_LOG_SEV(logger, ANDROID_LOG_WARN) << "this is a warning"; 
  }
  
  void test()
  {
    BOOST_LOG_SEV(logger, ANDROID_LOG_FATAL) << "fatal error occured";
  }
  
  boost_android_logging::Logger logger;
};

int main()
{
  boost_android_logging::init();
  
  boost_android_logging::Logger logger;
  SET_MODULE(logger, main);

  BOOST_LOG_SEV(logger, ANDROID_LOG_WARN) << "this is a warning";
  BOOST_LOG_SEV(logger, ANDROID_LOG_DEBUG) << "this will be filtered";
  BOOST_LOG_SEV(logger, ANDROID_LOG_FATAL) << "fatal error occured";
  
  Demo d;
  d.test();
  boost_android_logging::shutdown();
}
