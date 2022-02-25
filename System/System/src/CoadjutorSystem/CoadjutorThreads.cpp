#include "CoadjutorSystem/CoadjutorThreads.h"

void CoadjutorSystem::Thread::operator=(CoadjutorSystem::Thread &cpy)
{
  __name__ = cpy.__name__;
  __address__ = cpy.__address__;
  __intermittenceTime__ = cpy.__intermittenceTime__;
  __pauseIntermittenceTime__ = cpy.__pauseIntermittenceTime__;
  __status__ = cpy.__status__;
}

void CoadjutorSystem::Thread::operator=(CoadjutorSystem::Thread &&move)
{
  __name__ = move.__name__;
  __address__ = move.__address__;
  __intermittenceTime__ = move.__intermittenceTime__;
  __pauseIntermittenceTime__ = move.__pauseIntermittenceTime__;
  __status__ = move.__status__;
}

void CoadjutorSystem::Thread::_set_name_(System::Data::String name) { __name__ = name; }

void CoadjutorSystem::Thread::_set_intermittence_time_(unsigned long intermittenceTime)
{
  if (intermittenceTime == 0x00)
    __status__ = __FALSE;
  __intermittenceTime__ = intermittenceTime;
}

bool CoadjutorSystem::Thread::_set_address_(System::StdThread *address)
{
  if (__address__ != NULL || address == NULL)
    return __FALSE;
  __address__ = address;
  return __TRUE;
}

System::Data::String CoadjutorSystem::Thread::_get_name_() const { return __name__; }

unsigned long CoadjutorSystem::Thread::_get_intermittence_time_() const { return __intermittenceTime__; }

System::StdThread *CoadjutorSystem::Thread::_get_address_() const { return __address__; }

bool CoadjutorSystem::Thread::_get_status_() const { return __status__; }

bool CoadjutorSystem::Thread::_run_()
{
  if (__address__ == NULL)
    return __FALSE;
  __status__ = __TRUE;
  __address__();
  return __TRUE;
}

bool CoadjutorSystem::Thread::_pause_()
{
  if (__status__ == __FALSE)
    return __FALSE;
  __pauseIntermittenceTime__ = __intermittenceTime__;
  __intermittenceTime__ = 0x00;
  __status__ = __FALSE;
  return __TRUE;
}

bool CoadjutorSystem::Thread::_resume_()
{
  if (__status__ == __TRUE)
    return __FALSE;
  __intermittenceTime__ = __pauseIntermittenceTime__;
  __pauseIntermittenceTime__ = 0x00;
  __status__ = __TRUE;
  return __TRUE;
}

bool CoadjutorSystem::Thread::_delete_()
{
  if (__address__ == NULL)
    return __FALSE;
  __name__ = "";
  __address__ = NULL;
  __intermittenceTime__ = 0x00;
  __pauseIntermittenceTime__ = 0x00;
  __status__ = __FALSE;
  return __TRUE;
}

CoadjutorSystem::Thread::Thread() {}

CoadjutorSystem::Thread::Thread(System::StdThread *thread, System::Data::String threadName, unsigned long intermittenceTime) : __address__(thread), __name__(threadName), __intermittenceTime__(intermittenceTime) {}

CoadjutorSystem::Thread::Thread(CoadjutorSystem::Thread &cpy) { *this = cpy; }

CoadjutorSystem::Thread::Thread(CoadjutorSystem::Thread &&move) { *this = move; }

void CoadjutorSystem::Thread::setName(System::Data::String name) { _set_name_(name); }

void CoadjutorSystem::Thread::setIntermittenceTime(unsigned long intermittenceTime) { _set_intermittence_time_(intermittenceTime); }

bool CoadjutorSystem::Thread::setAddress(System::StdThread *address) { return _set_address_(address); }

System::Data::String CoadjutorSystem::Thread::getName() const { return _get_name_(); }

unsigned long CoadjutorSystem::Thread::getIntermittenceTime() const { return _get_intermittence_time_(); }

System::StdThread *CoadjutorSystem::Thread::getAddress() const { return _get_address_(); }

bool CoadjutorSystem::Thread::getStatus() const { return _get_status_(); }

bool CoadjutorSystem::Thread::Run() { return _run_(); }

bool CoadjutorSystem::Thread::Pause() { return _pause_(); }

bool CoadjutorSystem::Thread::Resume() { return _resume_(); }

bool CoadjutorSystem::Thread::Delete() { return _delete_(); }