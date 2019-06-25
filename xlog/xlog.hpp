/**********************************
 ** 
 ** author: kipp
 ** email: kadima.kipp@gmail.com
 ** file: xlog.hpp
 ** date: 2019-06-25
 ** 
***********************************/


#ifndef __XLOG_HPP
#define __XLOG_HPP
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <memory>
#include <time.h>
#include <stdarg.h>
#include <cstring>

namespace kipp {

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/')+1 : __FILE__)

//general logging
#define LOGX_INIT kipp::XLog::get
#define LOGX kipp::XLog::get().Log

#define LOGXL(fmt, ...)\
{\
    kipp::XLog::get().Log(fmt " [%d:%s] ", ##__VA_ARGS__, __LINE__, __FILENAME__);\
}

//logging warnning
#define LOGW kipp::XLog::get().Warn

#define LOGWL(fmt, ...)\
{\
    kipp::XLog::get().Warn(fmt " [%d:%s] ", ##__VA_ARGS__, __LINE__, __FILENAME__);\
}

//logging error
#define LOGE kipp::XLog::get().Error

#define LOGEL(fmt, ...)\
{\
    kipp::XLog::get().Error(fmt " [%d:%s] ", ##__VA_ARGS__, __LINE__, __FILENAME__);\
}

//logging debug
#define LOGD kipp::XLog::get().Debug

#define LOGDL(fmt, ...)\
{\
    kipp::XLog::get().Debug(fmt " [%d:%s] ", ##__VA_ARGS__, __LINE__, __FILENAME__);\
}

#define logx  LOGX
#define logxl LOGXL

#define logw  LOGW
#define logwl LOGWL

#define loge  LOGE
#define logel LOGEL

#define logd  LOGD
#define logdl LOGDL

class XLog
{
public:
    static XLog &get(const char* filename = nullptr)
    {
        static XLog instance(filename);
        return instance;
    }
    void Log(const char * szFormat, ...);
    void Warn(const char * szFormat, ...);
    void Error(const char *szFormat, ...);
    void Debug(const char *szFormat, ...);
    //Saving log to disk. every 5 seconds
    void Flush();

private:
    XLog(const char* filename);

    template<typename... Args>
    void warn(const char *fmt, const Args &... args);

    // last flush-time.
    time_t last_t;
    char fname[80];
};
}


#endif
