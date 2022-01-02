#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "SystemMacros.h"

#define __BUF_SIZE__(type) ((8 * sizeof(type)) + 1)

#define HEX 16
#define DEC 10
#define OCT 8
#define BIN 2

namespace SystemData
{
  class String
  {
  public:
    // Simple assignment
    String &operator=(const char *cstr);
    String &operator=(const String &str);

    // Concat

    // Get char at
   unsigned char operator[](unsigned int pos);

  private:
    char *__allocated_buffer__;
    unsigned int __len__;

  private:
    inline void _init_();

  private:
    void _validate_(unsigned int slen, char* cstr);
    unsigned char _alloc_(const char *cstr);
    String &_copy_(const char *cstr);
    String &_copy_(const String &str);
    void _get_char_at_(unsigned int pos);

  public:
    String(const char *cstr = "");
    String(const String &cpy);
    explicit String(char value, unsigned char base = 10);
    explicit String(unsigned char value, unsigned char base = 10);
    explicit String(int value, unsigned char base = 10);
    explicit String(unsigned int value, unsigned char base = 10);
    explicit String(long value, unsigned char base = 10);
    explicit String(unsigned long value, unsigned char base = 10);
    explicit String(float value, unsigned char precision = 2);
    explicit String(double value, unsigned char precision = 2);
    ~String(void);

  public:
    const char *c_str() const;
    unsigned int length() const;

    // Adicionar funções de comparação
    
    // Adicionar funções para manipular caracteres e strings

    // Conversions
    char toChar(unsigned char base = 10);
    unsigned char toUChar(unsigned char base = 10);
    int toInt(unsigned char base = 10);
    unsigned int toUInt(unsigned char base = 10);
    long toLong(unsigned char base = 10);
    unsigned long toULong(unsigned char base = 10);
    float toFloat();
    double toDouble();
  };
}
