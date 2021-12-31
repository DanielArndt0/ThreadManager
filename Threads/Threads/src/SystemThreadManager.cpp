#include "SystemThreadManager.h"
#include "SystemInterrupt.h"

extern unsigned long __system_tick_counter__;

subSystem::Thread System::ThreadManager::__thread_bank__[__max_tasks__];
unsigned long System::ThreadManager::__thread_manager_counter__[__max_tasks__] = {0x00};
unsigned int System::ThreadManager::__total_threads__ = 0x00;
unsigned int System::ThreadManager::__bank_size__ = 0x00;
bool System::ThreadManager::__manager_status__ = NOT_STARTED;
unsigned long System::ThreadManager::__thread_tick_counter__ = NOT_STARTED;

void System::ThreadManager::Begin()
{
  System::Settings::Interrupts::TIMER0()->Enable();
  __manager_status__ = STARTED;
}

void System::ThreadManager::xManager()
{
  register unsigned int i;
  __thread_tick_counter__++;
  System::Settings::Interrupts::TIMER0()->Reset();
  if (System::ThreadManager::get::xTotalThreads() > 0x00)
  {
    for (i = 0x00; i < System::ThreadManager::get::xTotalThreads(); i++)
    {
      __thread_manager_counter__[i]++;
      if (System::ThreadManager::get::xThreadRuntime(i) == NOT_RUNNING)
        __thread_manager_counter__[i] = 0x00;
      else if (__thread_manager_counter__[i] == System::ThreadManager::get::xThreadRuntime(i))
      {
        __thread_manager_counter__[i] = 0x00;
        System::ThreadManager::control::xRunThread(i);
      }
    }
  }
}

bool System::ThreadManager::xCreateThread(__std_thread__ *thread, const char *threadName, unsigned int ThreadNumber, unsigned long loopRuntime_ms)
{
  if (__manager_status__ == NOT_STARTED || ThreadNumber > __max_tasks__)
    return false;
  if (!__thread_bank__[ThreadNumber].pin(thread, threadName, loopRuntime_ms))
    return false;
  __total_threads__++;
  __bank_size__ = __max_tasks__ - __total_threads__;
  return true;
}

bool System::ThreadManager::control::xRunThread(unsigned int ThreadNumber)
{
  if (ThreadNumber > __max_tasks__ || __manager_status__ == NOT_STARTED)
    return false;
  __thread_bank__[ThreadNumber].run();
  return true;
}

bool System::ThreadManager::control::xRunThread(void (*addr_Thread)())
{
  if (addr_Thread == NULL || __manager_status__ == NOT_STARTED)
    return false;
  return xRunThread(get::xThreadNumber(addr_Thread));
}

unsigned long System::ThreadManager::get::xThreadRuntime(unsigned int ThreadNumber)
{
  if (__manager_status__ == NOT_STARTED)
    return false;
  return __thread_bank__[ThreadNumber].getExecutionTime();
}

unsigned long System::ThreadManager::get::xThreadRuntime(void (*addr_Thread)())
{
  if (addr_Thread == NULL || __manager_status__ == NOT_STARTED)
    return 0x00;
  return xThreadRuntime(xThreadNumber(addr_Thread));
}

const char *System::ThreadManager::get::xThreadName(unsigned int ThreadNumber)
{
  if (__manager_status__ == NOT_STARTED)
    return "";
  return __thread_bank__[ThreadNumber].getName();
}

const char *System::ThreadManager::get::xThreadName(void (*addr_Thread)())
{
  if (addr_Thread == NULL || __manager_status__ == NOT_STARTED)
    return "";
  return xThreadName(xThreadNumber(addr_Thread));
}

unsigned int System::ThreadManager::get::xStackSpace()
{
  if (__manager_status__ == NOT_STARTED)
    return false;
  return __bank_size__;
}

bool System::ThreadManager::control::xPauseThread(unsigned int ThreadNumber)
{
  if (ThreadNumber > __max_tasks__ || __manager_status__ == NOT_STARTED)
    return false;
  return __thread_bank__[ThreadNumber].pause();
}

bool System::ThreadManager::control::xPauseThread(void (*addr_Thread)())
{
  if (addr_Thread == NULL || __manager_status__ == NOT_STARTED)
    return false;
  return xPauseThread(get::xThreadNumber(addr_Thread));
}

bool System::ThreadManager::control::xResumeThread(unsigned int ThreadNumber)
{
  if (ThreadNumber > __max_tasks__ || __manager_status__ == NOT_STARTED)
    return false;
  return __thread_bank__[ThreadNumber].resume();
}

bool System::ThreadManager::control::xResumeThread(void (*addr_Thread)())
{
  if (addr_Thread == NULL || __manager_status__ == NOT_STARTED)
    return false;
  return xResumeThread(get::xThreadNumber(addr_Thread));
}

bool System::ThreadManager::get::xThreadStatus(unsigned int ThreadNumber)
{
  if (ThreadNumber > __max_tasks__ || __manager_status__ == NOT_STARTED)
    return false;
  return __thread_bank__[ThreadNumber].status();
}

bool System::ThreadManager::get::xThreadStatus(void (*addr_Thread)())
{
  if (addr_Thread == NULL || __manager_status__ == NOT_STARTED)
    return false;
  return xThreadStatus(xThreadNumber(addr_Thread));
}

void System::ThreadManager::xChangeThreadRuntime(unsigned int ThreadNumber, unsigned long loopRuntime_ms)
{
  if (ThreadNumber > __max_tasks__ || __manager_status__ == NOT_STARTED)
    return;
  __thread_bank__[ThreadNumber].setExecutionTime(loopRuntime_ms);
}

void System::ThreadManager::xChangeThreadRuntime(void (*addr_Thread)(), unsigned long loopRuntime_ms)
{
  if (addr_Thread == NULL || __manager_status__ == NOT_STARTED)
    return;
  xChangeThreadRuntime(get::xThreadNumber(addr_Thread), loopRuntime_ms);
}

bool System::ThreadManager::control::xDeleteThread(unsigned int ThreadNumber)
{
  if (ThreadNumber > __max_tasks__ || __manager_status__ == NOT_STARTED)
    return false;
  if (!__thread_bank__[ThreadNumber]._delete())
    return false;
  __total_threads__--;
  p_shift_thread_bank(ThreadNumber);
  __bank_size__++;
  return true;
}

bool System::ThreadManager::control::xDeleteThread(void (*addr_Thread)())
{
  if (addr_Thread == NULL || __manager_status__ == NOT_STARTED)
    return false;
  return xDeleteThread(get::xThreadNumber(addr_Thread));
}

unsigned int System::ThreadManager::get::xTotalThreads() { return __total_threads__; }

void (*System::ThreadManager::get::xThreadAddress(unsigned int ThreadNumber))()
{
  if (ThreadNumber > __max_tasks__ || __manager_status__ == NOT_STARTED)
    return NULL;
  return __thread_bank__[ThreadNumber].getAddress();
}

unsigned int System::ThreadManager::get::xThreadNumber(void (*addr_Thread)())
{
  if (addr_Thread == NULL || __manager_status__ == NOT_STARTED)
    return (pow(0x02, (sizeof(unsigned int) * 0x08)) - 0x01);
  for (register unsigned int i = 0x00; i < __total_threads__; i++)
    if (__thread_bank__[i].getAddress() == addr_Thread)
      return i;
  return (pow(0x02, (sizeof(unsigned int) * 0x08)) - 0x01);
}

void System::ThreadManager::p_shift_thread_bank(unsigned int cursor)
{
  for (register unsigned int i = cursor; i < __total_threads__; i++)
    __thread_bank__[i] = __thread_bank__[i + 1];
}
