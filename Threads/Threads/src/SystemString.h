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

namespace System
{
  namespace Data
  {
    class String
    {
    public:
      // Simple assignment
      String &operator=(char ch);
      String &operator=(const char *cstr);
      String &operator=(const String &str);

      // Attach
      String &operator+=(char ch);
      String &operator+=(const char *cstr);
      String &operator+=(const String &str);

      // Concat
      String &operator+(char ch);
      String &operator+(const char *cstr);
      String &operator+(const String &str);

      // Compare
      bool operator==(const char *cstr);
      bool operator==(const String &str);

      bool operator!=(const char *cstr);
      bool operator!=(const String &str);

      bool operator>(const char *cstr);
      bool operator>(const String &str);

      bool operator>=(const char *cstr);
      bool operator>=(const String &str);

      bool operator<(const char *cstr);
      bool operator<(const String &str);

      bool operator<=(const char *cstr);
      bool operator<=(const String &str);

      // Get char
      char operator[](unsigned int pos);

    private:
      char *__allocated_buffer__;
      unsigned int __len__;

    private:
      inline void _init_();

    private:
      // Primitives
      void _copy_to_buff_(char *cstr, unsigned int bufLen);
      char *_alloc_(const char *cstr, unsigned int *buffLen);

      // Operator assistant - Simple assignment
      String &_copy_(char ch);
      String &_copy_(const char *cstr);

      // Operator assistant - Concat
      String &_concat_(char ch);
      String &_concat_(const char *cstr);

      // Operator assistant - Attach
      String &_attach_(char ch);
      String &_attach_(const char *cstr);

      // Operator assistant - Compare
      bool _equal_(const char *cstr) const;
      bool _different_(const char *cstr) const;
      bool _bigger_then_(const char *cstr) const;
      bool _bigger_equal_then_(const char *cstr) const;
      bool _less_than_(const char *cstr) const;
      bool _less_equal_than_(const char *cstr) const;

      // Operator assistant - Get char
      char _get_char_at_(unsigned int pos) const;

    public:
      // Constructors
      String(const String &cpy);
      ~String(void);

      // Convert constructors
      String(char ch);
      String(const char *cstr = "");
      explicit String(unsigned char value, unsigned char base = 10);
      explicit String(int value, unsigned char base = 10);
      explicit String(unsigned int value, unsigned char base = 10);
      explicit String(long value, unsigned char base = 10);
      explicit String(unsigned long value, unsigned char base = 10);
      explicit String(float value, unsigned char precision = 2);
      explicit String(double value, unsigned char precision = 2);

    public:
      // Public Functions
      const char *c_str() const;
      unsigned int length() const;

      // Adicionar funções para manipular caracteres e strings
      char charAt(unsigned int pos) const;
      bool removeChar(char ch);

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
}