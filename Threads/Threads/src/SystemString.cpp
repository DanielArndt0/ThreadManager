#include "SystemString.h"

/*
 *  Private functions
 */
void System::Data::String::_init_()
{
  __allocated_buffer__ = NULL;
  __len__ = 0x00;
}

void System::Data::String::_copy_to_buff_(char *cstr, unsigned int bufLen)
{
  if (this->__allocated_buffer__)
    free(this->__allocated_buffer__);
  this->__len__ = bufLen;
  this->__allocated_buffer__ = cstr;
}

char *System::Data::String::_alloc_(const char *cstr, unsigned int *buffLen)
{
  *buffLen = strlen(cstr) + 1;
  char *temp = (char *)calloc(*buffLen, sizeof(char));
  if (temp == NULL)
    return NULL;
  return temp;
}

System::Data::String &System::Data::String::_copy_(char ch)
{
  if (ch)
  {
    unsigned int newLen = 0x02;
    char *temp = (char *)calloc(newLen, sizeof(char));
    if (temp == NULL)
      return *this;
    temp[0x00] = ch;
    temp[0x01] = 0x00;
    _copy_to_buff_(temp, newLen);
    return *this;
  }
  return *this;
}

System::Data::String &System::Data::String::_copy_(const char *cstr)
{
  if (cstr)
  {
    unsigned int newLen = 0x00;
    char *temp = _alloc_(cstr, &newLen);
    if (temp == NULL)
      return *this;
    strcpy(temp, cstr);
    _copy_to_buff_(temp, newLen);
    return *this;
  }
  return *this;
}

System::Data::String &System::Data::String::_concat_(char ch)
{
}

System::Data::String &System::Data::String::_concat_(const char *cstr)
{
  if (cstr)
  {
    System::Data::String *newStr = (System::Data::String *)calloc(1, sizeof(System::Data::String));
    unsigned int newLen = (strlen(this->__allocated_buffer__) + strlen(cstr)) + 1;
    char *temp = (char *)calloc(newLen, sizeof(char));
    if (temp == NULL)
      return *this;
    strcpy(temp, this->__allocated_buffer__);
    strcat(temp, cstr);
    *newStr = temp;
    return *newStr;
  }
  return *this;
}

System::Data::String &System::Data::String::_attach_(char ch)
{
  if (ch)
  {
    char buff[0x02];
    buff[0x00] = ch;
    buff[0x01] = 0x00;
    unsigned int newLen = (strlen(this->__allocated_buffer__) + 0x02);
    char *temp = (char *)calloc(newLen, sizeof(char));
    if (temp == NULL)
      return *this;
    strcpy(temp, this->__allocated_buffer__);
    strcat(temp, buff);
    _copy_to_buff_(temp, newLen);
    return *this;
  }
  return *this;
}

System::Data::String &System::Data::String::_attach_(const char *cstr) 
{
  if (cstr)
  {
    unsigned int newLen = (strlen(this->__allocated_buffer__) + strlen(cstr)) + 1;
    char *temp = (char *)calloc(newLen, sizeof(char));
    if (temp == NULL)
      return *this;
    strcpy(temp, this->__allocated_buffer__);
    strcat(temp, cstr);
    _copy_to_buff_(temp, newLen);
    return *this;
  }
  return *this;
}

bool System::Data::String::_equal_(const char *cstr) const
{
  if (cstr)
  {
    if (!strcmp(this->__allocated_buffer__, cstr))
      return TRUE;
  }
  return FALSE;
}

bool System::Data::String::_different_(const char *cstr) const
{
  if (cstr)
  {
    if (strcmp(this->__allocated_buffer__, cstr))
      return TRUE;
  }
  return FALSE;
}

bool System::Data::String::_bigger_then_(const char *cstr) const
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) > strlen(cstr))
      return TRUE;
  }
  return FALSE;
}

bool System::Data::String::_bigger_equal_then_(const char *cstr) const
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) >= strlen(cstr))
      return TRUE;
  }
  return FALSE;
}

bool System::Data::String::_less_than_(const char *cstr) const
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) < strlen(cstr))
      return TRUE;
  }
  return FALSE;
}

bool System::Data::String::_less_equal_than_(const char *cstr) const
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) <= strlen(cstr))
      return TRUE;
  }
  return FALSE;
}

char System::Data::String::_get_char_at_(unsigned int pos) const
{
  if (this->__allocated_buffer__)
    return this->__allocated_buffer__[pos];
  return 0x00;
}

/*
 *  Constructors
 */
System::Data::String::String(char ch)
{
  _init_();
  *this = ch;
}

System::Data::String::String(const char *cstr)
{
  _init_();
  *this = cstr;
}

System::Data::String::String(const System::Data::String &cpy)
{
  _init_();
  *this = cpy;
}

System::Data::String::String(unsigned char value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(unsigned char)];
  *this = utoa(value, l_buf, base);
}

System::Data::String::String(int value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(int)];
  *this = itoa(value, l_buf, base);
}

System::Data::String::String(unsigned int value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(unsigned int)];
  *this = utoa(value, l_buf, base);
}

System::Data::String::String(long value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(long)];
  *this = ltoa(value, l_buf, base);
}

System::Data::String::String(unsigned long value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(unsigned long)];
  *this = ultoa(value, l_buf, base);
}

System::Data::String::String(float value, unsigned char precision)
{
  _init_();
  char l_buf[__BUF_SIZE__(float)];
  *this = dtostrf(value, (precision + 1), precision, l_buf);
}

System::Data::String::String(double value, unsigned char precision)
{
  _init_();
  char l_buf[__BUF_SIZE__(double)];
  *this = dtostrf(value, (precision + 1), precision, l_buf);
}

/*
 *  Destructor
 */
System::Data::String::~String(void)
{
  if (__allocated_buffer__)
    free(__allocated_buffer__);
}

/*
 *  Public functions
 */
const char *System::Data::String::c_str() const { return __allocated_buffer__; }

unsigned int System::Data::String::length() const { return __len__ - 1; }

char System::Data::String::charAt(unsigned int pos) const { return _get_char_at_(pos); }

char System::Data::String::toChar(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (char)strtol(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

unsigned char System::Data::String::toUChar(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (unsigned char)strtoul(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

int System::Data::String::toInt(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (int)strtol(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

unsigned int System::Data::String::toUInt(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (unsigned int)strtoul(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

long System::Data::String::toLong(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (long)atol(this->__allocated_buffer__);
  return 0x00;
}

unsigned long System::Data::String::toULong(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (unsigned long)strtoul(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

float System::Data::String::toFloat()
{
  if (this->__allocated_buffer__)
    return (float)atof(this->__allocated_buffer__);
  return 0x00;
}

double System::Data::String::toDouble()
{
  if (this->__allocated_buffer__)
    return (double)atof(this->__allocated_buffer__);
  return 0x00;
}

/*
 * Operators
 */
System::Data::String &System::Data::String::operator=(char ch) { return _copy_(ch); }

System::Data::String &System::Data::String::operator=(const char *cstr) { return _copy_(cstr); }

System::Data::String &System::Data::String::operator=(const System::Data::String &cpy) { return _copy_(cpy.__allocated_buffer__); }

System::Data::String &System::Data::String::operator+(const char *cstr) { return _concat_(cstr); }

System::Data::String &System::Data::String::operator+(const System::Data::String &str) { return _concat_(str.c_str()); }

System::Data::String &System::Data::String::operator+=(char ch) { return _attach_(ch); }

System::Data::String &System::Data::String::operator+=(const char *cstr) { return _attach_(cstr); }

System::Data::String &System::Data::String::operator+=(const System::Data::String &str) { return _attach_(str.__allocated_buffer__); }

bool System::Data::String::operator==(const char *cstr) { return _equal_(cstr); }

bool System::Data::String::operator==(const System::Data::String &str) { return _equal_(str.__allocated_buffer__); }

bool System::Data::String::operator!=(const char *cstr) { return _different_(cstr); }

bool System::Data::String::operator!=(const System::Data::String &str) { return _different_(str.__allocated_buffer__); }

bool System::Data::String::operator>(const char *cstr) { return _bigger_then_(cstr); }

bool System::Data::String::operator>(const System::Data::String &str) { return _bigger_then_(str.__allocated_buffer__); }

bool System::Data::String::operator>=(const char *cstr) { return _bigger_equal_then_(cstr); }

bool System::Data::String::operator>=(const System::Data::String &str) { return _bigger_equal_then_(str.__allocated_buffer__); }

bool System::Data::String::operator<(const char *cstr) { return _less_than_(cstr); }

bool System::Data::String::operator<(const System::Data::String &str) { return _less_than_(str.__allocated_buffer__); }

bool System::Data::String::operator<=(const char *cstr) { return _less_equal_than_(cstr); }

bool System::Data::String::operator<=(const System::Data::String &str) { return _less_equal_than_(str.__allocated_buffer__); }

char System::Data::String::operator[](unsigned int pos)
{
  return _get_char_at_(pos);
}