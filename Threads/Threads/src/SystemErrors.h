#pragma once
#include "SystemMacros.h"
#include "SystemString.h"

#define REGERR(name) SystemErrors::Error(name)(__FUNCTION__, __FILE__, __DATE__, __TIME__, __LINE__);

namespace SystemErrors
{
  class Error
  {
  private:
    SystemData::String __thread_name__;
    void (*__func_addr)(void);
    int __stack_addr__;
    SystemData::String __func_name__;
    SystemData::String __file_path__;
    SystemData::String __last_build_date__;
    SystemData::String __last_build_time__;
    unsigned int __line__;

  public:
    Error();
    Error(Error &cpy);
    Error(SystemData::String funcName, SystemData::String filePath, SystemData::String lastBuildDate, SystemData::String lastBuildTime, int __line__);
    ~Error();

  public:
    void alert();
    void setError(Error &cpy);
    SystemData::String getFunction();
    SystemData::String getFilePath();
    SystemData::String getDate();
    SystemData::String getTime();
    unsigned int getLine();
  };
}