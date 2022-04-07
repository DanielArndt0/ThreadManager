#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "Macros/SystemMacros.h"

namespace System
{
  namespace Memory
  {
    class EEPROM
    {
    private:
      static unsigned char *__mem_buff__;
      static char *__str_buff__;
      static unsigned int __eeprom_size__;

    private:
      inline void _init_();

    protected:
      /**
       * @param selectWriteOp 0x01 for write operation and 0x00 for clear operation.
       */
      static void _eeprom_clear_write_(unsigned char selectWriteOp, unsigned char data, unsigned int addr);

      template <typename T>
      static void _convert_write_(T data, unsigned int addr);

      template <typename T>
      static T _convert_read_(T t, unsigned int addr);

      static void _write_string_(const char *data, unsigned int addr);
      static unsigned char _read_(unsigned int addr);
      static const char *_read_string_(unsigned int addr);
      static unsigned int _used_mem_(unsigned int addr1, unsigned int addr2);
      static unsigned int _free_mem_(unsigned int addr1, unsigned int addr2);
    public:
      EEPROM();

      ~EEPROM();

    public:
      /**
       * @return Returns the memory size.
       */
      static unsigned int Size();

      /**
       * @return Returns the used memory space in bytes.
       */
      static unsigned int Used();

      /**
       * @return Returns the free space in memory in bytes.
       */
      static unsigned int Empty();

      /**
       * @brief Writes data to EEPROM memory.
       *
       * @param data Data to be written.
       *
       * @param addr Memory address to be written.
       */
      static void Write(char data, unsigned int addr);

      /**
       * @brief Writes data to EEPROM memory.
       *
       * @param data Data to be written.
       *
       * @param addr Memory address to be written.
       */
      static void Write(unsigned char data, unsigned int addr);

      /**
       * @brief Writes data to EEPROM memory.
       *
       * @param data Data to be written.
       *
       * @param addr Memory address to be written.
       */
      static void Write(int data, unsigned int addr);

      /**
       * @brief Writes data to EEPROM memory.
       *
       * @param data Data to be written.
       *
       * @param addr Memory address to be written.
       */
      static void Write(unsigned int data, unsigned int addr);

      /**
       * @brief Writes data to EEPROM memory.
       *
       * @param data Data to be written.
       *
       * @param addr Memory address to be written.
       */
      static void Write(long data, unsigned int addr);

      /**
       * @brief Writes data to EEPROM memory.
       *
       * @param data Data to be written.
       *
       * @param addr Memory address to be written.
       */
      static void Write(unsigned long data, unsigned int addr);

      /**
       * @brief Write string to EEPROM memory.
       *
       * @param data String to be written.
       *
       * @param addr Memory address to be written.
       */
      static void Write(const char *data, unsigned int addr);

      /**
       * @brief Read data from EEPROM memory.
       *
       * @param addr Memory address to be read.
       */
      static char ReadChar(unsigned int addr);

      /**
       * @brief Read data from EEPROM memory.
       *
       * @param addr Memory address to be read.
       */
      static unsigned char ReadUChar(unsigned int addr);

      /**
       * @brief Read data from EEPROM memory.
       *
       * @param addr Memory address to be read.
       */
      static int ReadInt(unsigned int addr);

      /**
       * @brief Read data from EEPROM memory.
       *
       * @param addr Memory address to be read.
       */
      static unsigned int ReadUInt(unsigned int addr);

      /**
       * @brief Read data from EEPROM memory.
       *
       * @param addr Memory address to be read.
       */
      static long ReadLong(unsigned int addr);

      /**
       * @brief Read data from EEPROM memory.
       *
       * @param addr Memory address to be read.
       */
      static unsigned long ReadULong(unsigned int addr);

      /**
       * @brief Read string from EEPROM memory.
       *
       * @param addr Memory address to be read.
       */
      static const char *ReadString(unsigned int addr);

      /**
       * @brief Clear EEPROM memory address.
       *
       * @param addr Address to be cleared.
       */
      static void Clean(unsigned int addr);

      /**
       * @brief Clears an address block from the EEPROM memory.
       *
       * @param addr1 Block start address.
       *
       * @param addr2 End address of the block.
       */
      static void Clean(unsigned int addr1, unsigned int addr2);
    };
  }
}