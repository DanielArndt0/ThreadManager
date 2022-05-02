#include "Managers/ThreadManager.h"
#include "Com/SystemUART.h"

extern System::Com::UART Serial;

extern unsigned long __system_tick_counter__;

unsigned char System::Managers::ThreadManager::__manager_status__ = __FALSE;
System::Data::Vector<unsigned long> System::Managers::ThreadManager::__timer_stack__;
System::Data::Vector<CoadjutorSystem::Thread> System::Managers::ThreadManager::__thread_stack__;

bool System::Managers::ThreadManager::_check_existing_address_(System::StdThread *thread)
{
  for (register unsigned int i; i < __thread_stack__.Size(); i++)
  {
    if (__thread_stack__[i].getAddress() == thread)
      return __FALSE;
  }
  return __TRUE;
}

void System::Managers::ThreadManager::_begin_()
{
  System::Settings::Interrupts::TIMER0()->Enable();
  __manager_status__ = System::Settings::Interrupts::TIMER0()->Status();
}

bool System::Managers::ThreadManager::_create_thread_(StdThread *thread, Data::String threadName, unsigned long intermittenceTime)
{
  if (!__manager_status__ || !_check_existing_address_(thread))
    return __FALSE;
  __thread_stack__.Push(CoadjutorSystem::Thread(thread, threadName, intermittenceTime));
  __timer_stack__.Push(0x00);
  return __TRUE;
}

void System::Managers::ThreadManager::_manager_()
{
  register unsigned int i;
  System::Settings::Interrupts::TIMER0()->Reset();
  if (__thread_stack__.Size() > 0x00)
  {
    for (i = 0x00; i <= __thread_stack__.Size(); i++)
    {
      __timer_stack__[i]++;
      if (__thread_stack__[i].getIntermittenceTime() == __FALSE)
        __timer_stack__[i] = 0x00;
      else if (__timer_stack__[i] == __thread_stack__[i].getIntermittenceTime())
      {
        __timer_stack__[i] = 0x00;
        __thread_stack__[i].Run();
      }
    }
  }
}

void System::Managers::ThreadManager::_enable_manager_() { System::Settings::Interrupts::TIMER0()->Enable(); }

void System::Managers::ThreadManager::_disable_manager_() { System::Settings::Interrupts::TIMER0()->Disable(); }

void System::Managers::ThreadManager::_delete_manager_()
{
  __thread_stack__.Reset(); // Trocar para delete()
  __timer_stack__.Reset();  // Trocar para delete()
  System::Settings::Interrupts::TIMER0()->Disable();
}

bool System::Managers::ThreadManager::_execute_thread_(unsigned int ThreadNumber)
{
  if (!__manager_status__)
    return __FALSE;
  return __thread_stack__[ThreadNumber].Run();
}

bool System::Managers::ThreadManager::_execute_thread_(System::StdThread *addr_Thread) { return _execute_thread_(_get_thread_number_(addr_Thread)); }

bool System::Managers::ThreadManager::_pause_thread_(unsigned int ThreadNumber)
{
  if (!__manager_status__)
    return __FALSE;
  return __thread_stack__[ThreadNumber].Pause();
}

bool System::Managers::ThreadManager::_pause_thread_(System::StdThread *addr_Thread) { return _pause_thread_(_get_thread_number_(addr_Thread)); }

bool System::Managers::ThreadManager::_resume_thread_(unsigned int ThreadNumber)
{
  if (!__manager_status__)
    return __FALSE;
  return __thread_stack__[ThreadNumber].Resume();
}

bool System::Managers::ThreadManager::_resume_thread_(System::StdThread *addr_Thread) { return _resume_thread_(_get_thread_number_(addr_Thread)); }

bool System::Managers::ThreadManager::_delete_thread_(unsigned int ThreadNumber)
{
  if (!__manager_status__)
    return __FALSE;
  __thread_stack__.Pop(ThreadNumber);
  __timer_stack__.Pop(ThreadNumber);
  return __TRUE;
}

bool System::Managers::ThreadManager::_delete_thread_(System::StdThread *addr_Thread) { return _delete_thread_(_get_thread_number_(addr_Thread)); }

bool System::Managers::ThreadManager::_change_intermittence_time_(unsigned int ThreadNumber, unsigned long intermittenceTime)
{
  if (!__manager_status__)
    return __FALSE;
  __thread_stack__[ThreadNumber].setIntermittenceTime(intermittenceTime);
  return __TRUE;
}

bool System::Managers::ThreadManager::_change_intermittence_time_(StdThread *addr_Thread, unsigned long intermittenceTime) { return _change_intermittence_time_(_get_thread_number_(addr_Thread), intermittenceTime); }

System::StdThread *System::Managers::ThreadManager::_get_thread_addr_(unsigned int ThreadNumber)
{
  if (!__manager_status__)
    return NULL;
  return __thread_stack__[ThreadNumber].getAddress();
}

int System::Managers::ThreadManager::_get_thread_number_(System::StdThread *addr_Thread)
{
  if (addr_Thread == NULL)
    return -0x01;
  for (register int i = 0x00; i < (signed)__thread_stack__.Size(); i++)
    if (__thread_stack__[i].getAddress() == addr_Thread)
      return i;
  return -0x01;
}

bool System::Managers::ThreadManager::_get_thread_status_(unsigned int ThreadNumber)
{
  if (!__manager_status__)
    return __FALSE;
  return __thread_stack__[ThreadNumber].getStatus();
}

bool System::Managers::ThreadManager::_get_thread_status_(System::StdThread *addr_Thread) { return _get_thread_status_(_get_thread_number_(addr_Thread)); }

System::Data::String System::Managers::ThreadManager::_get_thread_name_(unsigned int ThreadNumber)
{
  if (!__manager_status__)
    return "";
  return __thread_stack__[ThreadNumber].getName();
}

System::Data::String System::Managers::ThreadManager::_get_thread_name_(System::StdThread *addr_Thread) { return _get_thread_status_(_get_thread_number_(addr_Thread)); }

unsigned long System::Managers::ThreadManager::_get_intermittence_time_(unsigned int ThreadNumber)
{
  if (!__manager_status__)
    return __FALSE;
  return __thread_stack__[ThreadNumber].getIntermittenceTime();
}

unsigned long System::Managers::ThreadManager::_get_intermittence_time_(System::StdThread *addr_Thread) { return _get_intermittence_time_(_get_thread_number_(addr_Thread)); }

unsigned char System::Managers::ThreadManager::_get_manager_status_() { return __manager_status__; }

unsigned int System::Managers::ThreadManager::_get_total_threads_() { return __thread_stack__.Size(); }

System::Managers::ThreadManager::ThreadManager() {}

System::Managers::ThreadManager::~ThreadManager() { _delete_manager_(); }

void System::Managers::ThreadManager::Begin() { _begin_(); }

bool System::Managers::ThreadManager::Create(System::StdThread *thread, System::Data::String threadName, unsigned long intermittenceTime) { return _create_thread_(thread, threadName, intermittenceTime); }

void System::Managers::ThreadManager::Manager() { _manager_(); }

void System::Managers::ThreadManager::EnableManager() { _enable_manager_(); }

void System::Managers::ThreadManager::DisableManager() { _disable_manager_(); }

void System::Managers::ThreadManager::DeleteManager() { _delete_manager_(); }

bool System::Managers::ThreadManager::Execute(unsigned int ThreadNumber) { return _execute_thread_(ThreadNumber); }

bool System::Managers::ThreadManager::Execute(System::StdThread *addr_Thread) { return _execute_thread_(_get_thread_number_(addr_Thread)); }

bool System::Managers::ThreadManager::Pause(unsigned int ThreadNumber) { return _pause_thread_(ThreadNumber); }

bool System::Managers::ThreadManager::Pause(System::StdThread *addr_Thread) { return _pause_thread_(_get_thread_number_(addr_Thread)); }

bool System::Managers::ThreadManager::Resume(unsigned int ThreadNumber) { return _resume_thread_(ThreadNumber); }

bool System::Managers::ThreadManager::Resume(System::StdThread *addr_Thread) { return _resume_thread_(_get_thread_number_(addr_Thread)); }

bool System::Managers::ThreadManager::Delete(unsigned int ThreadNumber) { return _delete_thread_(ThreadNumber); }

bool System::Managers::ThreadManager::Delete(System::StdThread *addr_Thread) { return _delete_thread_(_get_thread_number_(addr_Thread)); }

void System::Managers::ThreadManager::changeTime(unsigned int ThreadNumber, unsigned long intermittenceTime) { _change_intermittence_time_(ThreadNumber, intermittenceTime); }

void System::Managers::ThreadManager::changeTime(System::StdThread *addr_Thread, unsigned long intermittenceTime) { _change_intermittence_time_(_get_thread_number_(addr_Thread), intermittenceTime); }

System::StdThread *System::Managers::ThreadManager::getAddress(unsigned int ThreadNumber) { return _get_thread_addr_(ThreadNumber); }

int System::Managers::ThreadManager::getNumber(System::StdThread *addr_Thread) { return _get_thread_number_(addr_Thread); }

bool System::Managers::ThreadManager::getThreadStatus(unsigned int ThreadNumber) { return _get_thread_status_(ThreadNumber); }

bool System::Managers::ThreadManager::getThreadStatus(System::StdThread *addr_Thread) { return _get_thread_status_(_get_thread_number_(addr_Thread)); }

System::Data::String System::Managers::ThreadManager::getName(unsigned int ThreadNumber) { return _get_thread_name_(ThreadNumber); }

System::Data::String System::Managers::ThreadManager::getName(System::StdThread *addr_Thread) { return _get_thread_name_(_get_thread_number_(addr_Thread)); }

unsigned long System::Managers::ThreadManager::getTime(unsigned int ThreadNumber) { return _get_intermittence_time_(ThreadNumber); }

unsigned long System::Managers::ThreadManager::getTime(System::StdThread *addr_Thread) { return _get_intermittence_time_(_get_thread_number_(addr_Thread)); }

unsigned char System::Managers::ThreadManager::getManagerStatus() { return _get_manager_status_(); }

unsigned int System::Managers::ThreadManager::getTotalThreads() { return _get_total_threads_(); }