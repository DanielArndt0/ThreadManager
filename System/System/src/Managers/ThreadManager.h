#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>
#include "DataTypes/SystemTypes.h"
#include "Macros/SystemMacros.h"
#include "Time/SystemTime.h"
#include "CoadjutorSystem/CoadjutorThreads.h"

namespace System
{
  namespace Managers
  {
    class ThreadManager
    {
    private:
      static unsigned char __manager_status__;
      static Data::Vector<unsigned long> __timer_stack__;
      static Data::Vector<CoadjutorSystem::Thread> __thread_stack__;

    private:
      static bool _check_existing_address_(Data::StdThread *thread);
      //----------
      static void _begin_();
      static bool _create_thread_(Data::StdThread *thread, Data::String threadName, unsigned long intermittenceTime);
      static void _manager_();
      //----------
      static void _enable_manager_();
      static void _disable_manager_();
      static void _delete_manager_();
      //----------
      static bool _execute_thread_(unsigned int ThreadNumber);
      static bool _execute_thread_(Data::StdThread *addr_Thread);
      //----
      static bool _pause_thread_(unsigned int ThreadNumber);
      static bool _pause_thread_(Data::StdThread *addr_Thread);
      //----
      static bool _resume_thread_(unsigned int ThreadNumber);
      static bool _resume_thread_(Data::StdThread *addr_Thread);
      //----
      static bool _delete_thread_(unsigned int ThreadNumber);
      static bool _delete_thread_(Data::StdThread *addr_Thread);
      //----
      static bool _change_intermittence_time_(unsigned int ThreadNumber, unsigned long intermittenceTime);
      static bool _change_intermittence_time_(Data::StdThread *addr_Thread, unsigned long intermittenceTime);
      //----------
      static Data::StdThread *_get_thread_addr_(unsigned int ThreadNumber);
      static int _get_thread_number_(Data::StdThread *addr_Thread);
      //----
      static bool _get_thread_status_(unsigned int ThreadNumber);
      static bool _get_thread_status_(Data::StdThread *addr_Thread);
      //----
      static Data::String _get_thread_name_(unsigned int ThreadNumber);
      static Data::String _get_thread_name_(Data::StdThread *addr_Thread);
      //----
      static unsigned long _get_intermittence_time_(unsigned int ThreadNumber);
      static unsigned long _get_intermittence_time_(Data::StdThread *addr_Thread);
      //----
      static unsigned char _get_manager_status_();
      static unsigned int _get_total_threads_();
      //----------

    public:
      ThreadManager();
      ThreadManager(ThreadManager &cpy) = delete;
      ThreadManager(ThreadManager &&move) = delete;
      ~ThreadManager();

    public:
      static void Begin();
      static bool Create(Data::StdThread *thread, Data::String threadName, unsigned long intermittenceTime);
      static void Manager();
      static void EnableManager();
      static void DisableManager();
      static void DeleteManager();

    public:
      static bool Execute(unsigned int ThreadNumber);
      static bool Execute(Data::StdThread *addr_Thread);

      static bool Pause(unsigned int ThreadNumber);
      static bool Pause(Data::StdThread *addr_Thread);

      static bool Resume(unsigned int ThreadNumber);
      static bool Resume(Data::StdThread *addr_Thread);

      static bool Delete(unsigned int ThreadNumber);
      static bool Delete(Data::StdThread *addr_Thread);

      static void changeTime(unsigned int ThreadNumber, unsigned long intermittenceTime);
      static void changeTime(Data::StdThread *addr_Thread, unsigned long intermittenceTime);

      static Data::StdThread *getAddress(unsigned int ThreadNumber);
      static int getNumber(Data::StdThread *addr_Thread);

      static bool getThreadStatus(unsigned int ThreadNumber);
      static bool getThreadStatus(Data::StdThread *addr_Thread);

      static Data::String getName(unsigned int ThreadNumber);
      static Data::String getName(Data::StdThread *addr_Thread);

      static unsigned long getTime(unsigned int ThreadNumber);
      static unsigned long getTime(Data::StdThread *addr_Thread);

      static unsigned char getManagerStatus();
      static unsigned int getTotalThreads();
    };
  }
}