#include "CoadjutorSystem/CoadjutorThreads.h"

CoadjutorSystem::Thread::Thread()
{
  __name__ = "";
  __address__ = NULL;
  __executionTime__ = 0x00;
  __pauseExecutionTime__ = 0x00;
  __status__ = TRUE;
}

CoadjutorSystem::Thread::Thread(CoadjutorSystem::Thread &cpy)
{
  __name__ = cpy.__name__;
  __address__ = cpy.__address__;
  __executionTime__ = cpy.__executionTime__;
  __pauseExecutionTime__ = cpy.__pauseExecutionTime__;
  __status__ = cpy.__status__;
}

bool CoadjutorSystem::Thread::pin(__std_thread__ *thread, const char *threadName, unsigned long loopRuntime)
{
  if (thread == NULL)
    return FALSE;
  if (!setAddress(thread))
    return FALSE;
  setExecutionTime(loopRuntime);
  setName(threadName);
  return TRUE;
}

bool CoadjutorSystem::Thread::setAddress(__std_thread__ *address)
{
  if (__address__ != NULL || address == NULL)
    return FALSE;
  __address__ = address;
  return TRUE;
}

__std_thread__ *CoadjutorSystem::Thread::getAddress() const { return __address__; }

void CoadjutorSystem::Thread::setName(const char *name) { __name__ = name; }

const char *CoadjutorSystem::Thread::getName() const { return __name__; }

void CoadjutorSystem::Thread::setExecutionTime(unsigned long time)
{
  if (time == 0x00)
    __status__ = FALSE;
  __executionTime__ = time;
}

unsigned long CoadjutorSystem::Thread::getExecutionTime() const { return __executionTime__; }

bool CoadjutorSystem::Thread::run()
{
  if (__address__ == NULL)
    return FALSE;
  __status__ = TRUE;
  __address__();
  return TRUE;
}

bool CoadjutorSystem::Thread::pause()
{
  if (__status__ == FALSE)
    return FALSE;
  __pauseExecutionTime__ = __executionTime__;
  __executionTime__ = 0x00;
  __status__ = FALSE;
  return TRUE;
}

bool CoadjutorSystem::Thread::resume()
{
  if (__status__ == TRUE)
    return FALSE;
  __executionTime__ = __pauseExecutionTime__;
  __pauseExecutionTime__ = 0x00;
  __status__ = TRUE;
  return TRUE;
}

bool CoadjutorSystem::Thread::status() const { return __status__; }

bool CoadjutorSystem::Thread::_delete()
{
  if (__address__ == NULL)
    return FALSE;
  __name__ = "";
  __address__ = NULL;
  __executionTime__ = 0x00;
  __pauseExecutionTime__ = 0x00;
  __status__ = TRUE;
  return TRUE;
}
