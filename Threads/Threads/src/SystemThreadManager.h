#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "SystemMacros.h"
#include "Threads.h"
#include "SystemTime.h"

//
#if defined(__max_tasks__) && __max_tasks__ >= 0x01
#else
#undef __max_tasks__
#define __max_tasks__ 0x0A
#endif

//
#define PAUSED 0x01
#define RESUMED 0x00
#define NOT_STARTED 0x00
#define STARTED 0x01
#define NOT_RUNNING 0x00
#define RUNNING 0x01

namespace System
{
  class ThreadManager
  {
  friend System::Settings::Interrupts;

  private:
    static bool __manager_status__;
    static unsigned int __total_threads__;
    static unsigned int __bank_size__;
    static unsigned long __thread_tick_counter__;
    static unsigned long __thread_manager_counter__[__max_tasks__];
    static subSystem::Thread __thread_bank__[__max_tasks__];

  private:
    static void p_shift_thread_bank(unsigned int cursor);    

  public:
    struct control
    {
      static bool xRunThread(unsigned int ThreadNumber);
      static bool xRunThread(__std_thread__ *addr_Thread);
      static bool xPauseThread(unsigned int ThreadNumber);
      static bool xPauseThread(__std_thread__ *addr_Thread);
      static bool xResumeThread(unsigned int ThreadNumber);
      static bool xResumeThread(__std_thread__ *addr_Thread);
      static bool xDeleteThread(unsigned int ThreadNumber);
      static bool xDeleteThread(__std_thread__ *addr_Thread);
    } Control;

    struct get
    {
      static __std_thread__ *xThreadAddress(unsigned int ThreadNumber);
      static unsigned int xThreadNumber(__std_thread__ *addr_Thread);
      static unsigned int xTotalThreads();
      static unsigned int xStackSpace();
      static bool xThreadStatus(unsigned int ThreadNumber);
      static bool xThreadStatus(__std_thread__ *addr_Thread);
      static const char *xThreadName(unsigned int ThreadNumber);
      static const char *xThreadName(__std_thread__ *addr_Thread);
      static unsigned long xThreadRuntime(unsigned int ThreadNumber);
      static unsigned long xThreadRuntime(__std_thread__ *addr_Thread);
    } Get;

  public:
    static void Begin();
    static void xManager();
    static bool xCreateThread(__std_thread__ *thread, const char *threadName, unsigned int ThreadNumber, unsigned long loopRuntime_ms);
    static void xChangeThreadRuntime(unsigned int ThreadNumber, unsigned long loopRuntime);
    static void xChangeThreadRuntime(__std_thread__ *addr_Thread, unsigned long loopRuntime);
  };
}