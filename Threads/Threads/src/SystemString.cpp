#include "SystemString.h"

/*
 *  Private functions
 */
void SystemData::String::_init_()
{
  __allocated_buffer__ = NULL;
  __len__ = 0x00;
}

void SystemData::String::_copy_to_buff_(char *cstr, unsigned int bufLen)
{
  if (this->__allocated_buffer__)
    free(this->__allocated_buffer__);
  this->__len__ = bufLen;
  this->__allocated_buffer__ = cstr;
}

char *SystemData::String::_alloc_(const char *cstr, unsigned int *buffLen)
{
  *buffLen = strlen(cstr) + 1;
  char *temp = (char *)calloc(*buffLen, sizeof(char));
  if (temp == NULL)
    return NULL;
  return temp;
}

SystemData::String &SystemData::String::_alloc_copy_(char ch)
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

SystemData::String &SystemData::String::_alloc_copy_(const char *cstr)
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
SystemData::String &SystemData::String::_alloc_attach_(char ch)
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

SystemData::String &SystemData::String::_alloc_attach_(const char *cstr)
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

SystemData::String &SystemData::String::_copy_(char ch) { return _alloc_copy_(ch); }

SystemData::String &SystemData::String::_copy_(const char *cstr) { return _alloc_copy_(cstr); }

SystemData::String &SystemData::String::_attach_(char ch) { return _alloc_attach_(ch); }

SystemData::String &SystemData::String::_attach_(const char *cstr) { return _alloc_attach_(cstr); }

bool SystemData::String::_equal_(const char *cstr)
{
  if (cstr)
  {
    if (!strcmp(this->__allocated_buffer__, cstr))
      return TRUE;
  }
  return FALSE;
}

bool SystemData::String::_different_(const char *cstr)
{
  if (cstr)
  {
    if (strcmp(this->__allocated_buffer__, cstr))
      return TRUE;
  }
  return FALSE;
}

bool SystemData::String::_bigger_then_(const char *cstr)
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) > strlen(cstr))
      return TRUE;
  }
  return FALSE;
}

bool SystemData::String::_bigger_equal_then_(const char *cstr)
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) >= strlen(cstr))
      return TRUE;
  }
  return FALSE;
}

bool SystemData::String::_less_than_(const char *cstr)
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) < strlen(cstr))
      return TRUE;
  }
  return FALSE;
}

bool SystemData::String::_less_equal_than_(const char *cstr)
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) <= strlen(cstr))
      return TRUE;
  }
  return FALSE;
}

char SystemData::String::_get_char_at_(unsigned int pos)
{
  if (this->__allocated_buffer__)
    return this->__allocated_buffer__[pos];
  return 0x00;
}

/*
 *  Constructors
 */
SystemData::String::String(char ch)
{
  _init_();
  *this = ch;
}

SystemData::String::String(const char *cstr)
{
  _init_();
  *this = cstr;
}

SystemData::String::String(const SystemData::String &cpy)
{
  _init_();
  *this = cpy;
}

SystemData::String::String(unsigned char value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(unsigned char)];
  *this = utoa(value, l_buf, base);
}

SystemData::String::String(int value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(int)];
  *this = itoa(value, l_buf, base);
}

SystemData::String::String(unsigned int value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(unsigned int)];
  *this = utoa(value, l_buf, base);
}

SystemData::String::String(long value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(long)];
  *this = ltoa(value, l_buf, base);
}

SystemData::String::String(unsigned long value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(unsigned long)];
  *this = ultoa(value, l_buf, base);
}

SystemData::String::String(float value, unsigned char precision)
{
  _init_();
  char l_buf[__BUF_SIZE__(float)];
  *this = dtostrf(value, (precision + 1), precision, l_buf);
}

SystemData::String::String(double value, unsigned char precision)
{
  _init_();
  char l_buf[__BUF_SIZE__(double)];
  *this = dtostrf(value, (precision + 1), precision, l_buf);
}

/*
 *  Destructor
 */
SystemData::String::~String(void)
{
  if (__allocated_buffer__)
    free(__allocated_buffer__);
}

/*
 *  Public functions
 */
const char *SystemData::String::c_str() const { return __allocated_buffer__; }

unsigned int SystemData::String::length() const { return __len__ - 1; }

char SystemData::String::charAt(unsigned int pos) { return _get_char_at_(pos); }

char SystemData::String::toChar(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (char)strtol(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

unsigned char SystemData::String::toUChar(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (unsigned char)strtoul(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

int SystemData::String::toInt(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (int)strtol(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

unsigned int SystemData::String::toUInt(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (unsigned int)strtoul(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

long SystemData::String::toLong(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (long)atol(this->__allocated_buffer__);
  return 0x00;
}

unsigned long SystemData::String::toULong(unsigned char base)
{
  if (this->__allocated_buffer__)
    return (unsigned long)strtoul(this->__allocated_buffer__, NULL, base);
  return 0x00;
}

float SystemData::String::toFloat()
{
  if (this->__allocated_buffer__)
    return (float)atof(this->__allocated_buffer__);
  return 0x00;
}

double SystemData::String::toDouble()
{
  if (this->__allocated_buffer__)
    return (double)atof(this->__allocated_buffer__);
  return 0x00;
}

/*
 * Operators
 */
SystemData::String &SystemData::String::operator=(char ch) { return _copy_(ch); }

SystemData::String &SystemData::String::operator=(const char *cstr) { return _copy_(cstr); }

SystemData::String &SystemData::String::operator=(const SystemData::String &cpy) { return _copy_(cpy.__allocated_buffer__); }

SystemData::String &SystemData::String::operator+=(char ch) { return _attach_(ch); }

SystemData::String &SystemData::String::operator+=(const char *cstr) { return _attach_(cstr); }

SystemData::String &SystemData::String::operator+=(const SystemData::String &str) { return _attach_(str.__allocated_buffer__); }

bool SystemData::String::operator==(const char *cstr) { return _equal_(cstr); }

bool SystemData::String::operator==(const SystemData::String &str) { return _equal_(str.__allocated_buffer__); }

bool SystemData::String::operator!=(const char *cstr) { return _different_(cstr); }

bool SystemData::String::operator!=(const SystemData::String &str) { return _different_(str.__allocated_buffer__); }

bool SystemData::String::operator>(const char *cstr) { return _bigger_then_(cstr); }

bool SystemData::String::operator>(const SystemData::String &str) { return _bigger_then_(str.__allocated_buffer__); }

bool SystemData::String::operator>=(const char *cstr) { return _bigger_equal_then_(cstr); }

bool SystemData::String::operator>=(const SystemData::String &str) { return _bigger_equal_then_(str.__allocated_buffer__); }

bool SystemData::String::operator<(const char *cstr) { return _less_than_(cstr); }

bool SystemData::String::operator<(const SystemData::String &str) { return _less_than_(str.__allocated_buffer__); }

bool SystemData::String::operator<=(const char *cstr) { return _less_equal_than_(cstr); }

bool SystemData::String::operator<=(const SystemData::String &str) { return _less_equal_than_(str.__allocated_buffer__); }

char SystemData::String::operator[](unsigned int pos)
{
  return _get_char_at_(pos);
}