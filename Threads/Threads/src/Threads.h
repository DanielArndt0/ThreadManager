#pragma once

#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "SystemMacros.h"

typedef void __std_thread__(void);

namespace subSystem
{
  class Thread
  {
  private:
    unsigned long __pauseExecutionTime__;
    bool __status__;

  private:
    const char *__name__;
    unsigned long __executionTime__;
    __std_thread__ *__address__;

  public:
    Thread();
    bool setAddress(__std_thread__ *address);
    __std_thread__ *getAddress() const;
    void setName(const char* name);
    const char *getName() const;
    void setExecutionTime(unsigned long time);
    unsigned long getExecutionTime() const;
    bool pin(__std_thread__ *thread, const char *threadName, unsigned long loopRuntime);
    bool pause();
    bool resume();
    bool status() const;
    bool _delete();
    bool run();
  };
}