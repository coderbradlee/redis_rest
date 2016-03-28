#pragma once
#define BOOST_LOG_DYN_LINK 1

#include <stdexcept>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <functional>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/record_ordering.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/format.hpp>
namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

std::string&   replace_all(std::string&   str,const   std::string&   old_value,const   std::string&   new_value);     
std::string&   replace_all_distinct(std::string&   str,const   std::string&   old_value,const   std::string& new_value); 



//boost::shared_ptr< file_sink > initsink = initlog();//init log;
//src::severity_logger< severity_level > slg;
#include <memory>
#include <cstdio>
#include <cstdarg>
#include <restbed>
using namespace restbed;
class CustomLogger : public Logger
{
public:
	//boost::shared_ptr< file_sink > initsink;
	void stop(void)
	{

		return;
	}

	void start(const std::shared_ptr< const Settings >&)
	{
		//initsink = initlog();
		return;
	}

	void log(const Level, const char* fmt, ...)
	{
		va_list arguments;
		va_start(arguments, fmt);

		vfprintf(stderr, fmt, arguments);
		fprintf(stderr, "\n");

		//BOOST_LOG(test_lg::get()) << "webserver port:" << port;
		//BOOST_LOG(test_lg::get()) << "webserver threads:" << num_threads;
		
		/*boost::format fmt(format);
		fmt%arguments;

		BOOST_LOG_SEV(slg, notification) << fmt.str();*/

		//char buffer[1024] = { 0 };
		//vsnprintf(buffer,1024, fmt, arguments);
		//std::cout << buffer << std::endl;
		//BOOST_LOG_SEV(slg, notification) << buffer;
		va_end(arguments);
		//initsink->flush();
	}

	void log_if(bool expression, const Level level, const char* format, ...)
	{
		if (expression)
		{
			va_list arguments;
			va_start(arguments, format);
			log(level, format, arguments);
			va_end(arguments);
		}
	}
};
enum severity_level
{
	normal,
	notification,
	warning,
	error,
	critical
};
// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
	std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
	static const char* const str[] =
	{
		"normal",
		"notification",
		"warning",
		"error",
		"critical"
	};
	if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
		strm << str[lvl];
	else
		strm << static_cast< int >(lvl);
	return strm;
}


typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;
class singleton_boost_log :public boost::enable_shared_from_this<singleton_boost_log>, boost::noncopyable
{
public:
	singleton_boost_log()
	{
		if (initsink_ == nullptr)
		{
			initsink_ = initlog();
		}
	}
	static boost::shared_ptr<singleton_boost_log> get_instance()
	{
		boost::mutex::scoped_lock t(mu_);
		if (ps_ == nullptr)
		{
			ps_ = boost::shared_ptr<singleton_boost_log>(new singleton_boost_log());
		}
		/*if (initsink_ == nullptr)
		{
			initsink_ = initlog();
		}*/
		return ps_;
	}
	boost::shared_ptr<file_sink> get_initsink()
	{
		if (initsink_ == nullptr)
		{
			initsink_ = initlog();
		}
		return initsink_;
	}
	boost::shared_ptr< file_sink > initlog()
	{
		try
		{
			std::map<std::string, severity_level> severitymap = { { "normal", severity_level::normal }, { "notification", severity_level::notification }, { "warning", severity_level::warning }, { "error", severity_level::error }, { "critical", severity_level::critical } };
			boost::property_tree::ptree pt;
			boost::property_tree::ini_parser::read_ini("config.ini", pt);
			std::string logName = pt.get<std::string>("log.name");
			std::string logLevel = pt.get<std::string>("log.level");
			auto iter = severitymap.find(logLevel);
			if (iter != severitymap.end())
			{
				log_level_ = iter->second;
			}
			else
			{
				log_level_ = severity_level::error;
			}
			typedef sinks::text_ostream_backend backend_t;
			typedef sinks::asynchronous_sink<
				backend_t,
				sinks::unbounded_ordering_queue<
				logging::attribute_value_ordering< unsigned int, std::less< unsigned int > >
				>
			> sink_t;

			boost::shared_ptr< file_sink > sink(new file_sink(
				//keywords::file_name = logName+"_%Y%m%d_%H%M%S_%5N.log",      // file name pattern
				keywords::file_name = logName + "_%Y%m%d_%5N.log",
				//keywords::filter = expr::attr< severity_level >("Severity") >= logLevel,
				keywords::rotation_size = 16 * 1024 * 1024                     // rotation size, in characters
				));

			// Set up where the rotated files will be stored
			sink->locked_backend()->set_file_collector(sinks::file::make_collector(
				keywords::target = "logs",                          // where to store rotated files
				keywords::max_size = 16 * 1024 * 1024,              // maximum total size of the stored files, in bytes
				keywords::min_free_space = 100 * 1024 * 1024        // minimum free space on the drive, in bytes
				));

			// Upon restart, scan the target directory for files matching the file_name pattern
			sink->locked_backend()->scan_for_files();
			sink->set_formatter
				(
				expr::format("%1%: [%2%] [%3%] [%4%] - %5%")
				% expr::attr< unsigned int >("RecordID")
				% expr::attr< severity_level >("Severity")
				% expr::attr< boost::posix_time::ptime >("TimeStamp")
				// % expr::attr< boost::thread::id >("ThreadID")
				% expr::attr< attrs::current_thread_id::value_type >("ThreadID")
				% expr::smessage
				);
			//sink->set_filter(expr::attr< severity_level >("Severity").or_default(normal) >= logLevel);
			sink->set_filter(expr::attr< severity_level >("Severity").or_default(normal) >= severitymap[logLevel]);
			// Add it to the core
			logging::core::get()->add_sink(sink);

			// Add some attributes too
			logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
			logging::core::get()->add_global_attribute("RecordID", attrs::counter< unsigned int >());
			logging::core::get()->add_global_attribute("ThreadID", attrs::current_thread_id());

			return sink;
		}
		catch (std::exception& e)
		{
			std::cout << "FAILURE: " << e.what() << std::endl;
			return nullptr;
		}
	}
	/*src::severity_logger< severity_level > get_slg()
	{
		return slg_;
	}*/
	severity_level get_log_level()
	{
		return log_level_;
	}
private:
	boost::shared_ptr< file_sink > initsink_;
	//src::severity_logger< severity_level > slg_;
	static boost::mutex mu_;
	severity_level log_level_;
	static boost::shared_ptr<singleton_boost_log> ps_;
	
	
};
boost::shared_ptr<singleton_boost_log> singleton_boost_log::ps_ = nullptr;
boost::mutex singleton_boost_log::mu_;
//boost::shared_ptr< file_sink > singleton_boost_log::initsink_ = nullptr;
src::severity_logger< severity_level > slg;
boost::shared_ptr<singleton_boost_log> boost_log = singleton_boost_log::get_instance();