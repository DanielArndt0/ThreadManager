#pragma once
#include "SystemMacros.h"
#include "SystemString.h"

#define REGERR(name) SystemErrors::Error(name)(__FUNCTION__, __FILE__, __DATE__, __TIME__, __LINE__);
#define PAR __FUNCTION__, __FILE__, __DATE__, __TIME__, __LINE__

namespace SystemErrors
{
  class Error
  {
  private:
    System::Data::String __thread_name__;
    void (*__func_addr)(void);
    int __stack_addr__;

  public:
    Error();

  public:

  };
}