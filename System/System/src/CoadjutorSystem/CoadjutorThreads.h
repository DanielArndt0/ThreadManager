#pragma once

#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Macros/SystemMacros.h"
#include "DataTypes/SystemTypes.h"

namespace CoadjutorSystem
{
  class Thread
  {
  public:
    void operator=(Thread &cpy);
    void operator=(Thread &&move);

  private:
    System::StdThread *__address__;
    System::Data::String __name__;
    unsigned long __intermittenceTime__;
    bool __status__;
    unsigned long __pauseIntermittenceTime__;

  private:
    void _set_name_(System::Data::String name);
    void _set_intermittence_time_(unsigned long intermittenceTime);
    bool _set_address_(System::StdThread *address);
    System::Data::String _get_name_() const;
    unsigned long _get_intermittence_time_() const;
    System::StdThread *_get_address_() const;
    bool _get_status_() const;
    bool _run_();
    bool _pause_();
    bool _resume_();
    bool _delete_();

  public:
    Thread();
    Thread(System::StdThread *thread, System::Data::String threadName, unsigned long intermittenceTime);
    Thread(Thread &cpy);
    Thread(Thread &&move);

  public:
    // Setters
    void setName(System::Data::String name);
    void setIntermittenceTime(unsigned long intermittenceTime);
    bool setAddress(System::StdThread *address);
    // Getters
    System::Data::String getName() const;
    unsigned long getIntermittenceTime() const;
    System::StdThread *getAddress() const;
    bool getStatus() const;
    // Operations
    bool Run();
    bool Pause();
    bool Resume();
    bool Delete();
  };
}