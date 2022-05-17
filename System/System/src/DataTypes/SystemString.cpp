#include "DataTypes/SystemString.h"

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
  if (ch)
  {
    char buff[0x02];
    buff[0x00] = ch;
    buff[0x01] = 0x00;
    System::Data::String *newStr = (System::Data::String *)calloc(1, sizeof(System::Data::String));
    unsigned int newLen = (strlen(this->__allocated_buffer__) + 0x02);
    char *temp = (char *)calloc(newLen, sizeof(char));
    if (temp == NULL)
      return *this;
    strcpy(temp, this->__allocated_buffer__);
    strcat(temp, buff);
    *newStr = temp;
    return *newStr;
  }
  return *this;
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
      return true;
  }
  return false;
}

bool System::Data::String::_different_(const char *cstr) const
{
  if (cstr)
  {
    if (strcmp(this->__allocated_buffer__, cstr))
      return true;
  }
  return false;
}

bool System::Data::String::_bigger_then_(const char *cstr) const
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) > strlen(cstr))
      return true;
  }
  return false;
}

bool System::Data::String::_bigger_equal_then_(const char *cstr) const
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) >= strlen(cstr))
      return true;
  }
  return false;
}

bool System::Data::String::_less_than_(const char *cstr) const
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) < strlen(cstr))
      return true;
  }
  return false;
}

bool System::Data::String::_less_equal_than_(const char *cstr) const
{
  if (cstr)
  {
    if (strlen(this->__allocated_buffer__) <= strlen(cstr))
      return true;
  }
  return false;
}

char System::Data::String::_get_char_at_(unsigned int pos) const
{
  if (pos < __len__)
  {
    if (this->__allocated_buffer__)
      return this->__allocated_buffer__[pos];
  }
  return -1;
}

bool System::Data::String::_exists_in_the_range_(char pos, char min, char max) const { return _get_char_at_(pos) >= min && _get_char_at_(pos) <= max ? true : false; }

void System::Data::String::_shift_str_(unsigned int cursor)
{
  for (register unsigned int i = cursor; i < __len__; i++)
    __allocated_buffer__[i] = __allocated_buffer__[i + 1];
}

/*
 *  Constructors
 */

System::Data::String::String(const System::Data::String &cpy)
{
  _init_();
  *this = cpy;
}

System::Data::String::String(const System::Data::String &&move)
{
  _init_();
  *this = move;
}

System::Data::String::~String(void)
{
  if (__allocated_buffer__)
    free(__allocated_buffer__);
}

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
 *  Public functions
 */
const char *System::Data::String::C_str() const { return __allocated_buffer__; }

unsigned int System::Data::String::Length() const { return __len__ - 1; }

unsigned int System::Data::String::Count(char ch) const
{
  unsigned int counter = 0;
  for (register unsigned int i = 0; i < __len__; i++)
    if (_get_char_at_(i) == ch)
      counter++;
  return counter;
}

char System::Data::String::At(unsigned int pos) const { return _get_char_at_(pos); }

int System::Data::String::Find(char ch) const { return this->Find(ch, 0); }

int System::Data::String::Find(char ch, unsigned int pos) const
{
  for (register unsigned int i = pos; i < __len__; i++)
    if (_get_char_at_(i) == ch)
      return i;
  return -1;
}

bool System::Data::String::Equals(System::Data::String &str) const { return _equal_(str.__allocated_buffer__); }

bool System::Data::String::Equals(const char *str) const { return _equal_(str); }

bool System::Data::String::Different(System::Data::String &str) const { return _different_(str.__allocated_buffer__); }

bool System::Data::String::Different(const char *str) const { return _different_(str); }

bool System::Data::String::BiggerThen(System::Data::String &str) const { return _bigger_then_(str.__allocated_buffer__); }

bool System::Data::String::BiggerThen(const char *str) const { return _bigger_then_(str); }

bool System::Data::String::BiggerEqualThen(System::Data::String &str) const { return _bigger_equal_then_(str.__allocated_buffer__); }

bool System::Data::String::BiggerEqualThen(const char *str) const { return _bigger_equal_then_(str); }

bool System::Data::String::LessThen(System::Data::String &str) const { return _less_than_(str.__allocated_buffer__); }

bool System::Data::String::LessThen(const char *str) const { return _less_than_(str); }

bool System::Data::String::LessEqualThen(System::Data::String &str) const { return _less_equal_than_(str.__allocated_buffer__); }

bool System::Data::String::LessEqualThen(const char *str) const { return _less_equal_than_(str); }

bool System::Data::String::isUpper(unsigned int pos) const { return _exists_in_the_range_(pos, 0x41, 0x5A); }

bool System::Data::String::isLower(unsigned int pos) const { return _exists_in_the_range_(pos, 0x61, 0x7A); }

bool System::Data::String::isAlpha(unsigned int pos) const { return this->isUpper(pos) || this->isLower(pos) ? true : false; }

bool System::Data::String::isNumber(unsigned int pos) const { return _exists_in_the_range_(pos, 0x30, 0x39); }

bool System::Data::String::isPunctation(unsigned int pos) const { return _exists_in_the_range_(pos, 0x21, 0x2F) || _exists_in_the_range_(pos, 0x3A, 0x40) || _exists_in_the_range_(pos, 0x5B, 0x60) || _exists_in_the_range_(pos, 0x7B, 0x7E) ? true : false; }

bool System::Data::String::isPrint(unsigned int pos) const { return _exists_in_the_range_(pos, 0x20, 0x7E); }

bool System::Data::String::isControl(unsigned int pos) const { return _exists_in_the_range_(pos, 0x00, 0x1F) || _exists_in_the_range_(pos, 0x7F, 0x7F) ? true : false; }

void System::Data::String::toUpper(unsigned int pos)
{
  if (this->isAlpha(pos))
    if (!this->isUpper(pos))
      this->__allocated_buffer__[pos] -= 0x20;
}

void System::Data::String::toUpper()
{
  for (register unsigned int i = 0; i < __len__; i++)
    this->toUpper(i);
}

void System::Data::String::toLower(unsigned int pos)
{
  if (this->isAlpha(pos))
    if (!this->isLower(pos))
      this->__allocated_buffer__[pos] += 0x20;
}

void System::Data::String::toLower()
{
  for (register unsigned int i = 0; i < __len__; i++)
    this->toLower(i);
}

void System::Data::String::Remove(char ch) { this->Remove(ch, 0); }

void System::Data::String::Remove(unsigned int pos)
{
  if (pos < __len__)
  {
    String str;
    _shift_str_(pos);
    str = *this;
    *this = str;
  }
}

void System::Data::String::Remove(char ch, unsigned int pos)
{
  if (pos < __len__)
  {
    char _pos_ = this->Find(ch, pos);
    if (_pos_ < 0)
      return;
    String str;
    _shift_str_(_pos_);
    str = *this;
    *this = str;
  }
}

void System::Data::String::Remove(unsigned int pos, unsigned int pos2)
{
  if (pos < __len__ && pos2 < __len__)
  {
    for (unsigned int i = pos; i < pos2; i++)
      Remove(i);
  }
}

void System::Data::String::absRemove(char ch)
{
  char pos = this->Find(ch);
  if (pos < 0)
    return;
  unsigned int cntr = 0;
  while ((pos = this->Find(ch)) != -1)
  {
    _shift_str_(pos);
    cntr++;
  }
  __len__ -= cntr;
  __allocated_buffer__ = (char *)realloc(__allocated_buffer__, __len__);
}

void System::Data::String::Replace(char ch, unsigned int pos)
{
  if (pos < __len__)
    __allocated_buffer__[pos] = ch;
}

void System::Data::String::Replace(char ch, unsigned int pos, unsigned int pos2)
{
  if (pos < __len__ && pos2 < __len__)
  {
    for (unsigned int i = pos; i < pos2; i++)
      Replace(ch, i);
  }
}

void System::Data::String::absReplace(char ch, char ch1)
{
  int pos = 0;
  while ((pos = this->Find(ch)) != -1)
    this->__allocated_buffer__[pos] = ch1;
}

void System::Data::String::Delete()
{
  if (__allocated_buffer__)
  {
    free(__allocated_buffer__);
    __allocated_buffer__ = nullptr;
    __len__ = 0x00;
  }
}

bool System::Data::String::New()
{
  if (__allocated_buffer__ == nullptr)
  {
    char *temp = (char *)calloc(0x01, sizeof(char));
    if (temp == NULL)
      return 0x00;
    temp[0x00] = 0x00;
    _copy_to_buff_(temp, 0x01);
    return 0x01;
  }
  return 0x00;
}

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

System::Data::String &System::Data::String::operator=(System::Data::String &&move)
{
  if (this->__allocated_buffer__)
    delete[] this->__allocated_buffer__;
  this->__allocated_buffer__ = move.__allocated_buffer__;
  this->__len__ = move.__len__;
  move.__allocated_buffer__ = nullptr;
  move.__len__ = 0x00;
  return *this;
}

System::Data::String &System::Data::String::operator=(char ch) { return _copy_(ch); }

System::Data::String &System::Data::String::operator=(const char *cstr) { return _copy_(cstr); }

System::Data::String &System::Data::String::operator=(const System::Data::String &cpy) { return _copy_(cpy.__allocated_buffer__); }

System::Data::String &System::Data::String::operator+(char ch) { return _concat_(ch); }

System::Data::String &System::Data::String::operator+(const char *cstr) { return _concat_(cstr); }

System::Data::String &System::Data::String::operator+(const System::Data::String &str) { return _concat_(str.C_str()); }

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

char *System::Data::String::operator[](unsigned int pos)
{
  if (pos < __len__)
    return &__allocated_buffer__[pos];
  return nullptr;
}