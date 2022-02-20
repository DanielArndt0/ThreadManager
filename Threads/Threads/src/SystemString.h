#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdarg.h>
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
      // Copy
      String &operator=(char ch);
      // Copy
      String &operator=(const char *cstr);
      // Copy
      String &operator=(const String &str);

      // Move
      String &operator=(String &&_move);

      // Attach
      String &operator+=(char ch);
      // Attach
      String &operator+=(const char *cstr);
      // Attach
      String &operator+=(const String &str);

      // Concat
      String &operator+(char ch);
      // Concat
      String &operator+(const char *cstr);
      // Concat
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
      char *operator[](unsigned int pos);

    private:
      char *__allocated_buffer__;
      unsigned int __len__;

    private:
      inline void _init_();

    private:
      // Primitives
      void _copy_to_buff_(char *cstr, unsigned int bufLen);
      char *_alloc_(const char *cstr, unsigned int *buffLen);

      // Operator assistant - Copy
      String &_copy_(char ch);
      String &_copy_(const char *cstr);

      // Operator assistant - Move
      String &_move_(String &&move);

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

      // Others
      bool _exists_in_the_range_(char pos, char min, char max) const;
      void _shift_str_(unsigned int cursor);

    public:
      /**********************************************/
      /**************** Constructors ****************/
      /**********************************************/

      String(const String &cpy);
      String(String &&move);
      ~String(void);

      /******************************************************/
      /**************** Convert Constructors ****************/
      /******************************************************/

      String(char ch);
      String(const char *cstr = "");
      String(unsigned char value, unsigned char base = 10);
      String(int value, unsigned char base = 10);
      String(unsigned int value, unsigned char base = 10);
      String(long value, unsigned char base = 10);
      String(unsigned long value, unsigned char base = 10);
      String(float value, unsigned char precision = 2);
      String(double value, unsigned char precision = 2);

    public:
      /*****************************************************/
      /**************** String Manipulation ****************/
      /*****************************************************/

      /**
       * @return Returns the string in C format.
       */
      const char *C_str() const;

      /**
       * @return Returns the length of the string without '\0'.
       */
      unsigned int Length() const;

      /**
       * @brief Counts how many times the character appears in the string.
       *
       * @param ch Character to be counted.
       *
       * @return Returns how many times the character appeared in the string.
       */
      unsigned int Count(char ch) const;

      /**
       * @param pos Character position in the string.
       *
       * @return Returns the character at position. Returns 0 if the position is invalid.
       */
      char At(unsigned int pos) const;

      /**
       * @brief Find character position in string.
       *
       * @param ch Character to be found.
       *
       * @return Returns the position of the character found. Returns -1 if not found.
       */
      int Find(char ch) const;

      /**
       * @brief Find the character position in the string from one position.
       *
       * @param ch Character to be found.
       *
       * @param pos From the given position.
       *
       * @return Returns the position of the character found. Returns -1 if not found.
       */
      int Find(char ch, unsigned int pos) const;

      /**
       * @brief Check if character is in Uppercase.
       *
       * @param pos Character position in the string.
       *
       * @return Returns true if the character is in Uppercase. Otherwise, it returns false.
       */
      bool isUpper(unsigned int pos) const;

      /**
       * @brief Check if character is in Lowercase.
       *
       * @param pos Character position in the string.
       *
       * @return Returns true if the character is in Lowercase. Otherwise, it returns false.
       */
      bool isLower(unsigned int pos) const;

      /**
       * @brief Checks if the character is a letter.
       *
       * @param pos Character position in the string.
       *
       * @return Returns true if the character is a letter. Otherwise, it returns false.
       */
      bool isAlpha(unsigned int pos) const;

      /**
       * @brief Checks if the character is a number.
       *
       * @param pos Character position in the string.
       *
       * @return Returns true if the character is a number. Otherwise, it returns false.
       */
      bool isNumber(unsigned int pos) const;

      /**
       * @brief Checks if the character is a punctation.
       *
       * @param pos Character position in the string.
       *
       * @return Returns true if the character is a punctation. Otherwise, it returns false.
       */
      bool isPunctation(unsigned int pos) const;

      /**
       * @brief Checks if the character is printable.
       *
       * @param pos Character position in the string.
       *
       * @return Returns true if the character is printable. Otherwise, it returns false.
       */
      bool isPrint(unsigned int pos) const;

      /**
       * @brief Checks if the character is a control.
       *
       * @param pos Character position in the string.
       *
       * @return Returns true if the character is a control. Otherwise, it returns false.
       */
      bool isControl(unsigned int pos) const;

      /**
       * @brief Convert character to uppercase.
       *
       * @param pos Character position in the string.
       */
      void toUpper(unsigned int pos);

      /**
       * @brief Convert string to uppercase.
       */
      void toUpper();

      /**
       * @brief Convert character to lowercase.
       *
       * @param pos Character position in the string.
       */
      void toLower(unsigned int pos);

      /**
       * @brief Convert string to lowercase.
       */
      void toLower();

      /**
       * @brief Remove the character from the first position where it was found.
       *
       * @param ch Character to be removed.
       */
      void Remove(char ch);

      /**
       * @brief This function looks for the character of the given position and thus will remove it.
       *
       * @param ch Character to be removed.
       *
       * @param pos From the given position.
       */
      void Remove(char ch, unsigned int pos);

      /**
       * @brief Remove the character from the given position.
       *
       * @param pos Character position in the string.
       */
      void Remove(unsigned int pos);

      /**
       * @brief Remove the character from all positions where it was found.
       *
       * @param ch Character to be removed.
       */
      void absRemove(char ch);

      /**
       * @brief Replace at all found character the character with the new given character.
       *
       * @param ch Character to be replaced.
       *
       * @param ch1 New character.
       */
      void Replace(char ch, char ch1);

      /*********************************************/
      /**************** Conversions ****************/
      /*********************************************/

      /**
       * @brief Convert convert number found in string to Char.
       *
       * @param base Numerical base.
       *
       * @return Number found in string. In case of error, 0 will be returned.
       */
      char toChar(unsigned char base = 10);

      /**
       * @brief Convert convert number found in string to Unsigned Char.
       *
       * @param base Numerical base.
       *
       * @return Number found in string. In case of error, 0 will be returned.
       */
      unsigned char toUChar(unsigned char base = 10);

      /**
       * @brief Convert convert number found in string to Int.
       *
       * @param base Numerical base.
       *
       * @return Number found in string. In case of error, 0 will be returned.
       */
      int toInt(unsigned char base = 10);

      /**
       * @brief Convert convert number found in string to Unsigned Int.
       *
       * @param base Numerical base.
       *
       * @return Number found in string. In case of error, 0 will be returned.
       */
      unsigned int toUInt(unsigned char base = 10);

      /**
       * @brief Convert convert number found in string to Long.
       *
       * @param base Numerical base.
       *
       * @return Number found in string. In case of error, 0 will be returned.
       */
      long toLong(unsigned char base = 10);

      /**
       * @brief Convert convert number found in string to Unsigned Long.
       *
       * @param base Numerical base.
       *
       * @return Number found in string. In case of error, 0 will be returned.
       */
      unsigned long toULong(unsigned char base = 10);

      /**
       * @brief Convert convert number found in string to Float.
       *
       * @param base Numerical base.
       *
       * @return Number found in string. In case of error, 0 will be returned.
       */
      float toFloat();

      /**
       * @brief Convert convert number found in string to Double.
       *
       * @param base Numerical base.
       *
       * @return Number found in string. In case of error, 0 will be returned.
       */
      double toDouble();
    };
  }
}