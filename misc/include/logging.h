#ifndef _SMT_VISFRAME_LOGGING_H
#define _SMT_VISFRAME_LOGGING_H




#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>


#include <iostream>
#include <boost/locale/generator.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;


class boost_log{
public:
  static inline void init(char* szLogFile);

  /*
    所有log分为wide character 和 narrow character两个版本
    对于带有中文的记录（纯英文也可以），使用wide character版本
    例： boost_log::log_debug(L"此处有一个错误");
    对于纯英文的记录，可以采用narrow character版本
    例： boost_log::log_warning("there is a warning here");
   */
  static inline void log_trace(const wchar_t * str);
  static inline void log_trace(const char* str);

  static inline void log_debug(const wchar_t * str);
  static inline void log_debug(const char* str);

  static inline void log_warning(const wchar_t * str);
  static inline void log_warning(const char * str);

  static inline void log_error(const wchar_t * str);
  static inline void log_error(const char* str);
};


inline void boost_log::init(char* szLogFile)
{
#if 0    //logging::add_file_log(keywords::file_name = "SmartSM_VisFrame.log");
    logging::add_file_log
        (
        keywords::file_name = szLogFile,
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%]: %Message%"
        );

#else
    boost::shared_ptr< sinks::synchronous_sink< sinks::text_file_backend > > sink = logging::add_file_log
        (
        keywords::file_name = szLogFile,
        // This makes the sink to write log records that look like this:
        // 1: <normal> A normal severity message
        // 2: <error> An error severity message
        keywords::format =
        (
            expr::stream
            << expr::attr< unsigned int >("LineID")
            << " [" <<  expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
            << " ] : <" << logging::trivial::severity
            << "> " << expr::message
        )
        );
    std::locale loc = boost::locale::generator()("zh_CN.UTF-8");
	sink->locked_backend()->auto_flush(true);
    sink->imbue(loc);
#endif
    logging::add_common_attributes();
}

inline void boost_log::log_trace(const wchar_t * str)
{
    using namespace logging::trivial;
    src::wseverity_logger< severity_level > slg;

    BOOST_LOG_SEV(slg, trace) << str;

}

inline void boost_log::log_trace(const char* str)
{
    using namespace logging::trivial;
    src::severity_logger< severity_level > lg;

    BOOST_LOG_SEV(lg, trace) << str;


}

inline void boost_log::log_debug(const wchar_t * str)
{
    using namespace logging::trivial;
    src::wseverity_logger< severity_level > slg;

    BOOST_LOG_SEV(slg, debug) << str;

}

inline void boost_log::log_debug(const char* str)
{
    using namespace logging::trivial;
    src::severity_logger< severity_level > lg;

    BOOST_LOG_SEV(lg, debug) << str;
}

inline void log_warning(const wchar_t * str)
{
    using namespace logging::trivial;
    src::wseverity_logger< severity_level > slg;

    BOOST_LOG_SEV(slg, warning) << str;
}

inline void log_warning(const char * str)
{
    using namespace logging::trivial;
    src::severity_logger< severity_level > lg;

    BOOST_LOG_SEV(lg, warning) << str;
}

inline void boost_log::log_error(const wchar_t * str)
{
    using namespace logging::trivial;
    src::wseverity_logger< severity_level > slg;

    BOOST_LOG_SEV(slg, error) << str;

}

inline void boost_log::log_error(const char* str)
{
    using namespace logging::trivial;
    src::severity_logger< severity_level > lg;

    BOOST_LOG_SEV(lg, error) << str;
}

#endif
