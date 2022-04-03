#pragma once

namespace System
{
  namespace Properties
  {
    class EEProperties
    {
    private:
      char __name__;
      unsigned long __size__;
      unsigned long __start__;
      unsigned long __final__;

    public:
      EEProperties();
      EEProperties(char name, unsigned long addr_start, unsigned long addr_final);

    public:
      char getName();
      unsigned long getSize();
      unsigned long getStartAddr();
      unsigned long getEndAddr();
    };
  }
}