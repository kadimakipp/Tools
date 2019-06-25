/**********************************
 ** 
 ** author: kipp
 ** email: kadima.kipp@gmail.com
 ** file: xlog.cpp
 ** date: 2019-06-25
 ** 
***********************************/


#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"  //support for stdout logging
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "xlog.hpp"

namespace kipp {
std::shared_ptr<spdlog::logger> logger, console;

#include <cstdlib>
XLog::XLog(const char * filename)
{
    time_t nowtime = time(NULL);
    struct tm *local;

    local = localtime(&nowtime);

    if(filename)
    {
        char surffix[80];
        strftime(surffix, 80, "-%Y-%m-%d.xlog", local);

        std::string tmp = std::string(filename) + std::string(surffix);
        strcpy(fname, tmp.c_str());
    }
    else
    {
        strftime(fname, 80, "kipp-%Y-%m-%d.log", local);
    }

    spdlog::set_pattern("[%H:%M:%S.%e] %^[%L]%$ %v");
    logger = spdlog::basic_logger_mt("036", fname);
    console = spdlog::stdout_color_mt("x36");

    console->warn("XLog started. Log File At [{}].", std::string(fname));

    char tmp[80];
    sprintf(tmp, "ln -s -f %s today.xlog\n", fname);
    int a = system(tmp);

    last_t = time(NULL);

}
void XLog::Log(const char * szFormat, ...)
{
    char szBuff[255];
    memset(szBuff, 0, sizeof(szBuff));

    va_list args;
    va_start(args, szFormat);
    vsprintf(szBuff, szFormat, args);
    va_end(args);

    console->info(szBuff);
    logger->info(szBuff);

    auto current = time(NULL);
    int diff = current - last_t;
    if (diff>5)
    {
        Flush();
    }
}

void XLog::Warn(const char *szFormat, ...)
{
    char szBuff[255];
    memset(szBuff, 0, sizeof(szBuff));

    va_list args;
    va_start(args, szFormat);
    vsprintf(szBuff, szFormat, args);
    va_end(args);

    console->warn(szBuff);
    logger->warn(szBuff);
    auto current = time(NULL);
    int diff =current- last_t;
    if(diff>3)
        Flush();
}

void XLog::Debug(const char *szFormat, ...)
{
    char szBuff[255];
    memset(szBuff, 0, sizeof(szBuff));

    va_list args;
    va_start(args, szFormat);
    vsprintf(szBuff, szFormat, args);
    va_end(args);
    //TODO:: set_level api
    spdlog::set_level(spdlog::level::debug);
    console->debug(szBuff);
    logger->debug(szBuff);
    auto current = time(NULL);
    int diff =current- last_t;
    if(diff>3)
        Flush();
}

void XLog::Error(const char *szFormat, ...)
{
    char szBuff[255];
    memset(szBuff, 0, sizeof(szBuff));

    va_list args;
    va_start(args, szFormat);
    vsprintf(szBuff, szFormat, args);
    va_end(args);

    console->error(szBuff);
    logger->error(szBuff);
    auto current = time(NULL);
    int diff =current- last_t;
    if(diff>3)
        Flush();
}
void XLog::Flush()
{
    logger->flush();
    last_t = time(NULL);
}

template<typename... Args>
void XLog::warn(const char *fmt, const Args & ... args)
{
    console->warn(fmt, args...);
    logger->warn(fmt, args...);
    Flush();
}


}

