#define BOOST_LOG_DLL 1
#include <boost/log/core.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/trivial.hpp>
#undef BOOST_LOG_DLL

#include <boost/shared_ptr.hpp>
#include <queue>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;

typedef sinks::combine_requirements<sinks::synchronized_feeding, sinks::flushing>::type sync_flushing;

struct message_t
{
   message_t(const logging::record_view& r, const std::string& f) :
      record(r), fstring(f)
   {
   }
   logging::record_view record;
   std::string fstring;
};

template<typename Sink>
class memory_sink : public sinks::basic_formatted_sink_backend<char, sync_flushing>
{
public:
   memory_sink(const boost::shared_ptr<Sink>& sink) : sink_(sink)
   {
   }

   void consume(const logging::record_view& rec, const string_type& fstring)
   {
      const message_t msg(rec, fstring);
      messages_.push(msg);
   }

   void flush()
   {
      while (!messages_.empty())
      {
         const message_t& msg = messages_.front();
         sink_->consume(msg.record, msg.fstring);
         messages_.pop();
      }
   }
private:
   typedef std::queue<message_t> buffer_t;
   buffer_t messages_;
   const boost::shared_ptr<Sink> sink_;
};

std::ostream& operator << (std::ostream& stream, logging::trivial::severity_level lvl)
{
   return stream << boost::log::trivial::to_string(lvl);
}

class cout_sink : public sinks::basic_formatted_sink_backend< char, sinks::synchronized_feeding >
{
public:
   std::string format(const logging::record_view& rec, const std::string& fstring) const
   {
      return fstring;
   }
   void consume(const logging::record_view& rec, const std::string& fstring)
   {
      std::cout << "[" << rec[boost::log::trivial::severity] << "] " << fstring << std::endl;
   }
};

void init_cout()
{
   typedef sinks::synchronous_sink<memory_sink<cout_sink> > sink_t;

   boost::shared_ptr< logging::core > core = logging::core::get();
   core->remove_all_sinks();

   boost::shared_ptr< cout_sink > tsink = boost::make_shared<cout_sink>();
   boost::shared_ptr<memory_sink<cout_sink> > backend = boost::make_shared<memory_sink<cout_sink> >(tsink);
   boost::shared_ptr< sink_t > sink = boost::make_shared<sink_t>(tsink);
   
   core->add_sink(sink);
}

void flush_logs()
{
   logging::core::get()->flush();
}

int main()
{
   std::cout << "start" << std::endl;
   logging::add_common_attributes();
   init_cout();
   BOOST_LOG_TRIVIAL(warning) << "warning message";
   BOOST_LOG_TRIVIAL(error) << "error message";
   flush_logs();
}