#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "Macros/SystemMacros.h"

namespace System
{
  class EEPROM
  {
  private:
    unsigned char *__mem_buff__;
    char *__str_buff__;
    unsigned int __eeprom_size__;

  private:
    inline void _init_();

  private:
    /**
     * @param selectWriteOp 0x01 for write operation and 0x00 for clear operation.
     */
    void _eeprom_clear_write_(unsigned char selectWriteOp, unsigned char data, unsigned int addr);
    
    template<typename T>
    void _convert_write_(T data, unsigned int addr);

    template<typename T>
    T _convert_read_(T t, unsigned int addr);
    
    void _write_string_(const char *data, unsigned int addr);
    unsigned char _read_(unsigned int addr);
    const char *_read_string_(unsigned int addr);
    unsigned int _used_mem_(unsigned int addr1, unsigned int addr2);
    unsigned int _free_mem_(unsigned int addr1, unsigned int addr2);
    unsigned char *_get_mem_();
    void _release_array_();


  public:
    EEPROM();
    
    ~EEPROM();

  public:
    /**
     * @return Returns the memory size.
     */
    unsigned int Size();

    /**
     * @return Returns the used memory space in bytes.
     */
    unsigned int Used();

    /**
     * @return Returns the free space in memory in bytes.
     */
    unsigned int Empty();

    /**
     * @brief Writes data to EEPROM memory.
     *
     * @param data Data to be written.
     *
     * @param addr Memory address to be written.
     */
    void Write(char data, unsigned int addr);

    /**
     * @brief Writes data to EEPROM memory.
     *
     * @param data Data to be written.
     *
     * @param addr Memory address to be written.
     */
    void Write(unsigned char data, unsigned int addr);

    /**
     * @brief Writes data to EEPROM memory.
     *
     * @param data Data to be written.
     *
     * @param addr Memory address to be written.
     */
    void Write(int data, unsigned int addr);

    /**
     * @brief Writes data to EEPROM memory.
     *
     * @param data Data to be written.
     *
     * @param addr Memory address to be written.
     */
    void Write(unsigned int data, unsigned int addr);

    /**
     * @brief Writes data to EEPROM memory.
     *
     * @param data Data to be written.
     *
     * @param addr Memory address to be written.
     */
    void Write(long data, unsigned int addr);

    /**
     * @brief Writes data to EEPROM memory.
     *
     * @param data Data to be written.
     *
     * @param addr Memory address to be written.
     */
    void Write(unsigned long data, unsigned int addr);

    /**
     * @brief Write string to EEPROM memory.
     *
     * @param data String to be written.
     *
     * @param addr Memory address to be written.
     */
    void Write(const char *data, unsigned int addr);

    /**
     * @brief Read data from EEPROM memory.
     *
     * @param addr Memory address to be read.
     */
    char ReadChar(unsigned int addr);

    /**
     * @brief Read data from EEPROM memory.
     *
     * @param addr Memory address to be read.
     */
    unsigned char ReadUChar(unsigned int addr);

    /**
     * @brief Read data from EEPROM memory.
     *
     * @param addr Memory address to be read.
     */
    int ReadInt(unsigned int addr);

    /**
     * @brief Read data from EEPROM memory.
     *
     * @param addr Memory address to be read.
     */
    unsigned int ReadUInt(unsigned int addr);

    /**
     * @brief Read data from EEPROM memory.
     *
     * @param addr Memory address to be read.
     */
    long ReadLong(unsigned int addr);

    /**
     * @brief Read data from EEPROM memory.
     *
     * @param addr Memory address to be read.
     */
    unsigned long ReadULong(unsigned int addr);

    /**
     * @brief Read string from EEPROM memory.
     *
     * @param addr Memory address to be read.
     */
    const char *ReadString(unsigned int addr);

    /**
     * @brief Clear EEPROM memory address.
     *
     * @param addr Address to be cleared.
     */
    void Clear(unsigned int addr);

    /**
     * @brief Clears an address block from the EEPROM memory.
     *
     * @param addr1 Block start address.
     *
     * @param addr2 End address of the block.
     */
    void Clear(unsigned int addr1, unsigned int addr2);

    /**
     * @brief Copy all data in EEPROM memory to an array in Heap memory.
     *
     * @return Returns all data from EEPROM memory in array format.
     */
    unsigned char *Array();

    /**
     * @brief Frees data allocated on the memory heap. It will only take effect if the Array() method is invoked previously.
     */
    void FreeArray();
  };
}