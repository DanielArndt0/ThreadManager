#include "SystemString.h"

/*
 *  Private functions
 */
void SystemData::String::_init_()
{
  __allocated_buffer__ = NULL;
  __len__ = 0x00;
}

void SystemData::String::_validate_(unsigned int slen, char *cstr)
{
  if (this->__allocated_buffer__)
    free(this->__allocated_buffer__);
  this->__len__ = slen;
  this->__allocated_buffer__ = cstr;
}

unsigned char SystemData::String::_alloc_(const char *cstr)
{
  if (cstr)
  {
    int newLen = strlen(cstr) + 1;
    char *temp = (char *)calloc(newLen, sizeof(char));
    if (temp == NULL)
      return 0x00;
    strcpy(temp, cstr);
    _validate_(newLen, temp);
    return 0x01;
  }
  return 0x00;
}

SystemData::String &SystemData::String::_copy_(const char *cstr)
{
  _alloc_(cstr);
  return *this;
}

SystemData::String &SystemData::String::_copy_(const String &str)
{
  _alloc_(str.__allocated_buffer__);
  return *this;
}

/*
 *  Constructors
 */
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

SystemData::String::String(char value, unsigned char base)
{
  _init_();
  char l_buf[__BUF_SIZE__(char)];
  *this = itoa(value, l_buf, base);
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
SystemData::String &SystemData::String::operator=(const char *cstr) { return _copy_(cstr); }

SystemData::String &SystemData::String::operator=(const SystemData::String &cpy) { return _copy_(cpy); }

unsigned char SystemData::String::operator[](unsigned int pos) { return this->__allocated_buffer__[pos]; }