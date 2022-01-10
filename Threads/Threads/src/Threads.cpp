#include "Threads.h"

subSystem::Thread::Thread()
{
  __name__ = "";
  __address__ = NULL;
  __executionTime__ = 0x00;
  __pauseExecutionTime__ = 0x00;
  __status__ = TRUE;
}

subSystem::Thread::Thread(subSystem::Thread &cpy)
{
  __name__ = cpy.__name__;
  __address__ = cpy.__address__;
  __executionTime__ = cpy.__executionTime__;
  __pauseExecutionTime__ = cpy.__pauseExecutionTime__;
  __status__ = cpy.__status__;
}

bool subSystem::Thread::pin(__std_thread__ *thread, const char *threadName, unsigned long loopRuntime)
{
  if (thread == NULL)
    return FALSE;
  if (!setAddress(thread))
    return FALSE;
  setExecutionTime(loopRuntime);
  setName(threadName);
  return TRUE;
}

bool subSystem::Thread::setAddress(__std_thread__ *address)
{
  if (__address__ != NULL || address == NULL)
    return FALSE;
  __address__ = address;
  return TRUE;
}

__std_thread__ *subSystem::Thread::getAddress() const { return __address__; }

void subSystem::Thread::setName(const char *name) { __name__ = name; }

const char *subSystem::Thread::getName() const { return __name__; }

void subSystem::Thread::setExecutionTime(unsigned long time)
{
  if (time == 0x00)
    __status__ = FALSE;
  __executionTime__ = time;
}

unsigned long subSystem::Thread::getExecutionTime() const { return __executionTime__; }

bool subSystem::Thread::run()
{
  if (__address__ == NULL)
    return FALSE;
  __status__ = TRUE;
  __address__();
  return TRUE;
}

bool subSystem::Thread::pause()
{
  if (__status__ == FALSE)
    return FALSE;
  __pauseExecutionTime__ = __executionTime__;
  __executionTime__ = 0x00;
  __status__ = FALSE;
  return TRUE;
}

bool subSystem::Thread::resume()
{
  if (__status__ == TRUE)
    return FALSE;
  __executionTime__ = __pauseExecutionTime__;
  __pauseExecutionTime__ = 0x00;
  __status__ = TRUE;
  return TRUE;
}

bool subSystem::Thread::status() const { return __status__; }

bool subSystem::Thread::_delete()
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
