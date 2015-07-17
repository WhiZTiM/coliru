#define BOOST_LOG_DYN_LINK 1
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <string>

void initLogging()
{
    boost::log::add_common_attributes();
    auto core = boost::log::core::get();

    core->add_global_attribute("UTCTimeStamp",boost::log::attributes::utc_clock());

    auto x = boost::log::add_file_log(
            boost::log::keywords::file_name             = "Log_%3N.log",
            boost::log::keywords::rotation_size         = 1 * 1024, // 1k
            boost::log::keywords::target                = "Logs",
            boost::log::keywords::min_free_space        = 30 * 1024 * 1024,
            boost::log::keywords::max_size              = 20 * 1024,
            boost::log::keywords::time_based_rotation   = boost::log::sinks::file::rotation_at_time_point(boost::gregorian::greg_day(31)),
            boost::log::keywords::scan_method           = boost::log::sinks::file::scan_all,
            boost::log::keywords::format                = "%UTCTimeStamp% (%TimeStamp%) [%ThreadID%]: %Message%",
            boost::log::keywords::auto_flush            = true
        );

    //auto d = x->locked_backend()->scan_for_files();
}

int main()
{
    initLogging();
    for (int i = 0; i < 20; ++i) {
        BOOST_LOG_TRIVIAL(trace) << "Let's go shopping " << std::string(400, '*');
    }
}
