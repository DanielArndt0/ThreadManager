#include "Threads.h"

subSystem::Thread::Thread()
{
  __name__ = "";
  __address__ = NULL;
  __executionTime__ = 0x00;
  __pauseExecutionTime__ = 0x00;
  __status__ = TRUE;
}

bool subSystem::Thread::pin(__std_thread__ *thread, const char *threadName, unsigned long loopRuntime)
{
  if (thread == NULL)
    return false;
  if (!setAddress(thread))
    return false;
  setExecutionTime(loopRuntime);
  setName(threadName);
  return true;
}

bool subSystem::Thread::setAddress(__std_thread__ *address)
{
  if (__address__ != NULL || address == NULL)
    return false;
  __address__ = address;
  return true;
}

__std_thread__ *subSystem::Thread::getAddress() const { return __address__; }

void subSystem::Thread::setName(const char *name) { __name__ = name; }

const char *subSystem::Thread::getName() const { return __name__; }

void subSystem::Thread::setExecutionTime(unsigned long time)
{
  if (time == 0x00)
    __status__ = TRUE;
  __executionTime__ = time;
}

unsigned long subSystem::Thread::getExecutionTime() const { return __executionTime__; }

bool subSystem::Thread::run()
{
  if (__address__ == NULL)
    return false;
  __status__ = TRUE;
  __address__();
  return true;
}

bool subSystem::Thread::pause()
{
  if (__status__ == TRUE)
    return false;
  __pauseExecutionTime__ = __executionTime__;
  __executionTime__ = 0x00;
  __status__ = TRUE;
  return true;
}

bool subSystem::Thread::resume()
{
  if (__status__ == FALSE)
    return false;
  __executionTime__ = __pauseExecutionTime__;
  __pauseExecutionTime__ = 0x00;
  __status__ = FALSE;
  return true;
}

bool subSystem::Thread::status() const { return __status__; }

bool subSystem::Thread::_delete()
{
  if (__address__ == NULL)
    return false;
  __name__ = "";
  __address__ = NULL;
  __executionTime__ = 0x00;
  __pauseExecutionTime__ = 0x00;
  __status__ = 0x00;
  return true;
}
