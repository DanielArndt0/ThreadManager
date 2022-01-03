#include "SystemErrors.h"

SystemErrors::Error::Error(SystemData::String funcName, SystemData::String filePath, SystemData::String lastBuildDate, SystemData::String lastBuildTime, int line)
    : __func_name__(funcName), __file_path__(filePath), __last_build_date__(lastBuildDate), __last_build_time__(lastBuildTime), __line__(line) {}

SystemErrors::Error::Error()
{
  this->__file_path__ = "";
  this->__func_addr = NULL;
  this->__func_name__ = "";
  this->__last_build_date__ = "";
  this->__last_build_time__ = "";
  this->__line__ = 0;
  this->__stack_addr__ = -1;
  this->__thread_name__ = "";
}

SystemErrors::Error::Error(SystemErrors::Error &cpy)
{
  this->__file_path__ = cpy.__file_path__;
  this->__func_addr = cpy.__func_addr;
  this->__func_name__ = cpy.__func_name__;
  this->__last_build_date__ = cpy.__last_build_date__;
  this->__last_build_time__ = cpy.__last_build_time__;
  this->__line__ = cpy.__line__;
  this->__stack_addr__ = cpy.__stack_addr__;
  this->__thread_name__ = cpy.__thread_name__;
}

SystemErrors::Error::~Error()
{

}

void SystemErrors::Error::setError(SystemErrors::Error &cpy)
{
  this->__file_path__ = cpy.__file_path__;
  this->__func_addr = cpy.__func_addr;
  this->__func_name__ = cpy.__func_name__;
  this->__last_build_date__ = cpy.__last_build_date__;
  this->__last_build_time__ = cpy.__last_build_time__;
  this->__line__ = cpy.__line__;
  this->__stack_addr__ = cpy.__stack_addr__;
  this->__thread_name__ = cpy.__thread_name__;
}

SystemData::String SystemErrors::Error::getFunction() { return __func_name__; }

SystemData::String SystemErrors::Error::getFilePath() { return __file_path__; }

SystemData::String SystemErrors::Error::getDate() { return __last_build_date__; }

SystemData::String SystemErrors::Error::getTime() { return __last_build_time__; }

unsigned int SystemErrors::Error::getLine() { return __line__; }