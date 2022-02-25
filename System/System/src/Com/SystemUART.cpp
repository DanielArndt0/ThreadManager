#include "Com/SystemUART.h"

void System::Com::UART::Begin(unsigned int baudRate)
{
  unsigned int __ubrr__ = (__SYSTEM_CLOCK / 0x08 / baudRate) - 0x01;
  UBRR0H = (unsigned char)__HIGH(__ubrr__);
  UBRR0L = (unsigned char)__ubrr__;
  __WRITE_REG(UCSR0A, U2X0, __TRUE);
  __WRITE_REG(UCSR0B, RXEN0, __TRUE);
  __WRITE_REG(UCSR0B, TXEN0, __TRUE);
  __WRITE_REG(UCSR0B, UCSZ02, __FALSE);
  __WRITE_REG(UCSR0C, USBS0, __FALSE);
  __uart_status__ = __TRUE;
}

/*
 *   Sender
 */

System::Com::UART *System::Com::UART::__uart_send__(unsigned char data)
{
  if (__uart_status__ == __FALSE)
    return this;
  while (!(__CHECK(UCSR0A, UDRE0)));
  UDR0 = data;
  while (!(__CHECK(UCSR0A, TXC0)));
  return this;
}

System::Com::UART *System::Com::UART::__uart_send__(const char *data)
{
  if (data)
  {
    if (__uart_status__ == __FALSE)
      return this;
    for (register unsigned int i = 0x00; i < (unsigned int)strlen(data); i++)
      __uart_send__(data[i]);
    return this;
  }
  return this;
}

System::Com::UART &System::Com::UART::operator<<(const char *data) { return *this->__uart_send__(data); }

System::Com::UART &System::Com::UART::operator<<(const System::Data::String &data) { return *this->__uart_send__(data.C_str()); }

System::Com::UART &System::Com::UART::operator<<(char command) { return *this->__uart_send__(command); }

System::Com::UART &System::Com::UART::operator<<(int data) { return *this->__uart_send__(System::Data::String(data).C_str()); }

System::Com::UART &System::Com::UART::operator<<(unsigned int data) { return *this->__uart_send__(System::Data::String(data).C_str()); }

System::Com::UART &System::Com::UART::operator<<(long data) { return *this->__uart_send__(System::Data::String(data).C_str()); }

System::Com::UART &System::Com::UART::operator<<(unsigned long data) { return *this->__uart_send__(System::Data::String(data).C_str()); }

System::Com::UART &System::Com::UART::operator<<(float data) { return *this->__uart_send__(System::Data::String(data).C_str()); }

System::Com::UART &System::Com::UART::operator<<(double data) { return *this->__uart_send__(System::Data::String(data).C_str()); }

/*
 *   Receiver
 */
unsigned char System::Com::UART::__uart_receive__()
{
  if (__uart_status__ == __FALSE)
    return 0x00;
  while (!(__CHECK(UCSR0A, RXC0)));
  if (__CHECK(UCSR0A, DOR0) || __CHECK(UCSR0A, FE0))
  {
    UDR0;
    __WRITE_REG(UCSR0B, RXEN0, __FALSE);
    __WRITE_REG(UCSR0B, RXEN0, __TRUE);
    return 0x00;
  }
  return UDR0;
}

System::Com::UART &System::Com::UART::operator>>(unsigned char &data)
{
  data = __uart_receive__();
  return *this;
}

/*
 *   Flush RX buffer
 */
void System::Com::UART::Flush(void)
{
  unsigned char f = 0x00;
  while (__CHECK(UCSR0A, RXC0))
    if (!f)
      f = UDR0;
}