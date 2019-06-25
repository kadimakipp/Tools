/**********************************
 ** 
 ** author: kipp
 ** email: kadima.kipp@gmail.com
 ** file: xlog_test.cpp
 ** date: 2019-06-25
 ** 
***********************************/


#include "xlog.hpp"


int main(int argc, char * agrv[])
{
    LOGX_INIT();
    logx("general logging...");
    logxl("general logging...");
    LOGX("general logging...");
    LOGXL("general logging...");

    logw("warn log");
    logwl("warn log");
    LOGW("warn log");
    LOGWL("warn log");
    //attention spdlog::set_level(spdlog::level::debug);
    logd("debug log");
    logdl("debug log");
    LOGD("debug log");
    LOGDL("debug log");

    loge("error log");
    logel("error log");
    LOGE("error log");
    LOGEL("error log");




    return 0;
}

