#include "SystemThreadManager.h"

extern System::UART Serial;

extern unsigned long __system_tick_counter__;

System::Data::Vector<subSystem::Thread> System::ThreadManager::__thread_stack__;
System::Data::Vector<unsigned long> System::ThreadManager::__timer_stack__;
bool System::ThreadManager::__manager_status__ = FALSE;

System::ThreadManager::~ThreadManager()
{
  __thread_stack__.~Vector();
  __timer_stack__.~Vector();
  System::Settings::Interrupts::TIMER0()->Disable();
}

void System::ThreadManager::Begin()
{
  System::Settings::Interrupts::TIMER0()->Enable();
  __manager_status__ = TRUE;
}
//
void System::ThreadManager::xManager()
{
  register unsigned int i;
  System::Settings::Interrupts::TIMER0()->Reset();
  if (__timer_stack__.Size() > 0x00)
  {
    for (i = 0x00; i < __timer_stack__.Size(); i++)
    {
      __timer_stack__[i] += 1;
      if (__thread_stack__[i].getExecutionTime() == FALSE)
        __timer_stack__[i] = 0x00;
      else if (__timer_stack__[i] == __thread_stack__[i].getExecutionTime())
      {
        __timer_stack__[i] = 0x00;
        __thread_stack__[i].run();
      }
    }
  }
}

bool System::ThreadManager::xCreateThread(__std_thread__ *function, const char *threadName, unsigned long loopRuntime_ms)
{
  if (!__manager_status__)
    return FALSE;

  subSystem::Thread *temp = new subSystem::Thread;
  if (!temp->pin(function, threadName, loopRuntime_ms))
    return false;
  __thread_stack__.Add(*temp);
  __timer_stack__.Add(0x00);
  delete temp;
  return TRUE;
}

bool System::ThreadManager::control::xDeleteThread(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __thread_stack__.Size())
    return FALSE;

  if (!__thread_stack__[ThreadNumber]._delete())
    return FALSE;
  __thread_stack__.Remove(ThreadNumber);
  __timer_stack__.Remove(ThreadNumber);
  return TRUE;
}

bool System::ThreadManager::control::xDeleteThread(__std_thread__ *addr_Thread) { return xDeleteThread(get::xThreadNumber(addr_Thread)); }

bool System::ThreadManager::control::xDeleteThread(const char *functionName) { return xDeleteThread(get::xThreadNumber(functionName)); }

void System::ThreadManager::xChangeThreadRuntime(unsigned int ThreadNumber, unsigned long loopRuntime_ms)
{
  if (!__manager_status__ || ThreadNumber > __thread_stack__.Size())
    return;
  __thread_stack__[ThreadNumber].setExecutionTime(loopRuntime_ms);
}

void System::ThreadManager::xChangeThreadRuntime(__std_thread__ *addr_Thread, unsigned long loopRuntime_ms) { xChangeThreadRuntime(get::xThreadNumber(addr_Thread), loopRuntime_ms); }

void System::ThreadManager::xChangeThreadRuntime(const char *functionName, unsigned long loopRuntime_ms) { xChangeThreadRuntime(get::xThreadNumber(functionName), loopRuntime_ms); }

bool System::ThreadManager::control::xRunThread(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __thread_stack__.Size())
    return FALSE;
  __thread_stack__[ThreadNumber].run();
  return TRUE;
}

bool System::ThreadManager::control::xRunThread(__std_thread__ *addr_Thread) { return xRunThread(get::xThreadNumber(addr_Thread)); }

bool System::ThreadManager::control::xRunThread(const char *functionName) { return xRunThread(get::xThreadNumber(functionName)); }

bool System::ThreadManager::control::xPauseThread(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __thread_stack__.Size())
    return FALSE;
  return __thread_stack__[ThreadNumber].pause();
}

bool System::ThreadManager::control::xPauseThread(__std_thread__ *addr_Thread) { return xPauseThread(get::xThreadNumber(addr_Thread)); }

bool System::ThreadManager::control::xPauseThread(const char *functionName) { return xPauseThread(get::xThreadNumber(functionName)); }

bool System::ThreadManager::control::xResumeThread(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __thread_stack__.Size())
    return FALSE;
  return __thread_stack__[ThreadNumber].resume();
}

bool System::ThreadManager::control::xResumeThread(__std_thread__ *addr_Thread) { return xResumeThread(get::xThreadNumber(addr_Thread)); }

bool System::ThreadManager::control::xResumeThread(const char *functionName) { return xResumeThread(get::xThreadNumber(functionName)); }

void (*System::ThreadManager::get::xThreadAddress(unsigned int ThreadNumber))()
{
  if (!__manager_status__ || ThreadNumber > __thread_stack__.Size())
    return NULL;
  return __thread_stack__[ThreadNumber].getAddress();
}

void (*System::ThreadManager::get::xThreadAddress(const char *functionName))() { return xThreadAddress(get::xThreadNumber(functionName)); }

unsigned int System::ThreadManager::get::xThreadNumber(__std_thread__ *addr_Thread)
{
  if (addr_Thread == NULL || !__manager_status__)
    return (unsigned int)(pow(0x02, (sizeof(unsigned int) * 0x08)) - 0x01);
  for (register unsigned int i = 0x00; i < __thread_stack__.Size(); i++)
    if (__thread_stack__[i].getAddress() == addr_Thread)
      return i;
  return (unsigned int)(pow(0x02, (sizeof(unsigned int) * 0x08)) - 0x01);
}

unsigned int System::ThreadManager::get::xThreadNumber(const char *functionName)
{
  if (!__manager_status__)
    return (unsigned int)(pow(0x02, (sizeof(unsigned int) * 0x08)) - 0x01);
  for (register unsigned int i = 0x00; i < __thread_stack__.Size(); i++)
    if (__thread_stack__[i].getName() == functionName)
      return i;
  return (unsigned int)(pow(0x02, (sizeof(unsigned int) * 0x08)) - 0x01);
}

bool System::ThreadManager::get::xThreadStatus(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __thread_stack__.Size())
    return FALSE;
  return __thread_stack__[ThreadNumber].status();
}

bool System::ThreadManager::get::xThreadStatus(__std_thread__ *addr_Thread) { return xThreadStatus(xThreadNumber(addr_Thread)); }

bool System::ThreadManager::get::xThreadStatus(const char *functionName) { return xThreadStatus(xThreadNumber(functionName)); }

const char *System::ThreadManager::get::xThreadName(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __thread_stack__.Size())
    return "";
  return __thread_stack__[ThreadNumber].getName();
}

const char *System::ThreadManager::get::xThreadName(__std_thread__ *addr_Thread) { return xThreadName(xThreadNumber(addr_Thread)); }

const char *System::ThreadManager::get::xThreadName(const char *functionName) { return xThreadName(xThreadNumber(functionName)); }

unsigned long System::ThreadManager::get::xThreadRuntime(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __thread_stack__.Size())
    return FALSE;
  return __thread_stack__[ThreadNumber].getExecutionTime();
}

unsigned long System::ThreadManager::get::xThreadRuntime(__std_thread__ *addr_Thread) { return xThreadRuntime(xThreadNumber(addr_Thread)); }

unsigned long System::ThreadManager::get::xThreadRuntime(const char *functionName) { return xThreadRuntime(xThreadNumber(functionName)); }

unsigned int System::ThreadManager::get::xTotalThreads() { return __thread_stack__.Size(); }

unsigned int System::ThreadManager::get::xStackSpace() { return __thread_stack__.Capacity(); }