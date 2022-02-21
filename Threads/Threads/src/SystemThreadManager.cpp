#include "SystemThreadManager.h"

extern unsigned long __system_tick_counter__;

CoadjutorSystem::Thread *System::ThreadManager::__thread_stack__ = NULL;
unsigned int System::ThreadManager::__thread_stack_size__ = 0x01;
unsigned long *System::ThreadManager::__thread_timer_stack__ = NULL;
unsigned int System::ThreadManager::__total_threads__ = 0x00;
bool System::ThreadManager::__manager_status__ = FALSE;

int System::ThreadManager::_check_stack_address_()
{
  for (register int i = 0x00; (unsigned int)i < __thread_stack_size__; i++)
  {
    if (__thread_stack__[i].getAddress() == NULL)
      return i;
  }
  return -0x01;
}

bool System::ThreadManager::_check_existing_address_(__std_thread__ *thread)
{
  for (register unsigned int i; i < __thread_stack_size__; i++)
  {
    if (__thread_stack__[i].getAddress() == thread)
      return FALSE;
  }
  return TRUE;
}

void System::ThreadManager::_shift_thread_stack_(unsigned int cursor)
{
  for (register unsigned int i = cursor; i < __total_threads__; i++)
    __thread_stack__[i] = __thread_stack__[i + 1];
}

System::ThreadManager::~ThreadManager()
{
  if (__thread_stack__)
    free(__thread_stack__);
  if (__thread_timer_stack__)
    free(__thread_timer_stack__);
  System::Settings::Interrupts::TIMER0()->Disable();
}

bool System::ThreadManager::Begin()
{
  if ((__thread_stack__ = (CoadjutorSystem::Thread *)calloc(__thread_stack_size__, sizeof(CoadjutorSystem::Thread))) == NULL)
    return FALSE;
  if ((__thread_timer_stack__ = (unsigned long *)calloc(__thread_stack_size__, sizeof(unsigned long))) == NULL)
    return FALSE;
  System::Settings::Interrupts::TIMER0()->Enable();
  __manager_status__ = TRUE;
  return TRUE;
}
//
void System::ThreadManager::xManager()
{
  register unsigned int i;
  System::Settings::Interrupts::TIMER0()->Reset();
  if (__total_threads__ > 0x00)
  {
    for (i = 0x00; i < __thread_stack_size__; i++)
    {
      __thread_timer_stack__[i]++;
      if (__thread_stack__[i].getExecutionTime() == FALSE)
        __thread_timer_stack__[i] = 0x00;
      else if (__thread_timer_stack__[i] == __thread_stack__[i].getExecutionTime())
      {
        __thread_timer_stack__[i] = 0x00;
        __thread_stack__[i].run();
      }
    }
  }
}

bool System::ThreadManager::xCreateThread(__std_thread__ *thread, const char *threadName, unsigned long loopRuntime_ms)
{
  if (!__manager_status__ || __total_threads__ >= __thread_stack_size__)
    return FALSE;

  if (!_check_existing_address_(thread))
    return FALSE;

  int addr = -0x01;
  if ((addr = _check_stack_address_()) < 0x00)
    return FALSE;

  if (!__thread_stack__[addr].pin(thread, threadName, loopRuntime_ms))
    return FALSE;
  __total_threads__++;

  if ((__thread_stack__ = (CoadjutorSystem::Thread *)realloc(__thread_stack__, (__total_threads__ + 1) * sizeof(CoadjutorSystem::Thread))) == NULL)
    return FALSE;
  __thread_stack__[__total_threads__]._delete();

  if ((__thread_timer_stack__ = (unsigned long *)realloc(__thread_timer_stack__, (__total_threads__ + 1) * sizeof(unsigned long))) == NULL)
    return FALSE;
  __thread_timer_stack__[__total_threads__] = 0x00;

  __thread_stack_size__++;
  return TRUE;
}

void System::ThreadManager::xChangeThreadRuntime(unsigned int ThreadNumber, unsigned long loopRuntime_ms)
{
  if (!__manager_status__ || ThreadNumber > __total_threads__)
    return;
  __thread_stack__[ThreadNumber].setExecutionTime(loopRuntime_ms);
}

void System::ThreadManager::xChangeThreadRuntime(__std_thread__ *addr_Thread, unsigned long loopRuntime_ms) { xChangeThreadRuntime(get::xThreadNumber(addr_Thread), loopRuntime_ms); }

bool System::ThreadManager::control::xRunThread(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __total_threads__)
    return FALSE;
  __thread_stack__[ThreadNumber].run();
  return TRUE;
}

bool System::ThreadManager::control::xRunThread(__std_thread__ *addr_Thread) { return xRunThread(get::xThreadNumber(addr_Thread)); }

bool System::ThreadManager::control::xPauseThread(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __total_threads__)
    return FALSE;
  return __thread_stack__[ThreadNumber].pause();
}

bool System::ThreadManager::control::xPauseThread(__std_thread__ *addr_Thread) { return xPauseThread(get::xThreadNumber(addr_Thread)); }

bool System::ThreadManager::control::xResumeThread(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __total_threads__)
    return FALSE;
  return __thread_stack__[ThreadNumber].resume();
}

bool System::ThreadManager::control::xResumeThread(__std_thread__ *addr_Thread) { return xResumeThread(get::xThreadNumber(addr_Thread)); }

bool System::ThreadManager::control::xDeleteThread(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __total_threads__)
    return FALSE;

  if (!__thread_stack__[ThreadNumber]._delete())
    return FALSE;
  __total_threads__--;

  _shift_thread_stack_(ThreadNumber);

  if ((__thread_stack__ = (CoadjutorSystem::Thread *)realloc(__thread_stack__, (__thread_stack_size__ - 1) * sizeof(CoadjutorSystem::Thread))) == NULL)
    return FALSE;

  if ((__thread_timer_stack__ = (unsigned long *)realloc(__thread_timer_stack__, (__thread_stack_size__ - 1) * sizeof(unsigned long))) == NULL)
    return FALSE;

  __thread_stack_size__--;
  return TRUE;
}

bool System::ThreadManager::control::xDeleteThread(__std_thread__ *addr_Thread) { return xDeleteThread(get::xThreadNumber(addr_Thread)); }

void (*System::ThreadManager::get::xThreadAddress(unsigned int ThreadNumber))()
{
  if (!__manager_status__ || ThreadNumber > __total_threads__)
    return NULL;
  return __thread_stack__[ThreadNumber].getAddress();
}

unsigned int System::ThreadManager::get::xThreadNumber(__std_thread__ *addr_Thread)
{
  if (addr_Thread == NULL || !__manager_status__)
    return (pow(0x02, (sizeof(unsigned int) * 0x08)) - 0x01);
  for (register unsigned int i = 0x00; i < __total_threads__; i++)
    if (__thread_stack__[i].getAddress() == addr_Thread)
      return i;
  return (pow(0x02, (sizeof(unsigned int) * 0x08)) - 0x01);
}

bool System::ThreadManager::get::xThreadStatus(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __total_threads__)
    return FALSE;
  return __thread_stack__[ThreadNumber].status();
}

bool System::ThreadManager::get::xThreadStatus(__std_thread__ *addr_Thread) { return xThreadStatus(xThreadNumber(addr_Thread)); }

const char *System::ThreadManager::get::xThreadName(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __total_threads__)
    return "";
  return __thread_stack__[ThreadNumber].getName();
}

const char *System::ThreadManager::get::xThreadName(__std_thread__ *addr_Thread) { return xThreadName(xThreadNumber(addr_Thread)); }

unsigned long System::ThreadManager::get::xThreadRuntime(unsigned int ThreadNumber)
{
  if (!__manager_status__ || ThreadNumber > __total_threads__)
    return FALSE;
  return __thread_stack__[ThreadNumber].getExecutionTime();
}

unsigned long System::ThreadManager::get::xThreadRuntime(__std_thread__ *addr_Thread) { return xThreadRuntime(xThreadNumber(addr_Thread)); }

unsigned int System::ThreadManager::get::xTotalThreads() { return __total_threads__; }

unsigned int System::ThreadManager::get::xStackSpace() { return __thread_stack_size__; }