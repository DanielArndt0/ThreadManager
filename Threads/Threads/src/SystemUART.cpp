#include "SystemUART.h"

void System::UART::Begin(unsigned int baudRate)
{
  unsigned int __ubrr__ = (systemClock / 0x08 / baudRate) - 0x01;
  UBRR0H = (unsigned char)high(__ubrr__);
  UBRR0L = (unsigned char)__ubrr__;
  writeRegister(UCSR0A, U2X0, TRUE);
  writeRegister(UCSR0B, RXEN0, TRUE);
  writeRegister(UCSR0B, TXEN0, TRUE);
  writeRegister(UCSR0B, UCSZ02, FALSE);
  writeRegister(UCSR0C, USBS0, FALSE);
  __uart_status__ = TRUE;
}

/*
 *   Sender
 */

System::UART *System::UART::__uart_send__(unsigned char data)
{
  if (__uart_status__ == FALSE)
    return this;
  while (!(check(UCSR0A, UDRE0)));
  UDR0 = data;
  while (!(check(UCSR0A, TXC0)));
  return this;
}

System::UART *System::UART::__uart_send__(const char *data)
{
  if (data)
  {
    if (__uart_status__ == FALSE)
      return this;
    for (register unsigned int i = 0x00; i < (unsigned int)strlen(data); i++)
      __uart_send__(data[i]);
    return this;
  }
  return this;
}

System::UART &System::UART::operator<<(const char *data) { return *this->__uart_send__(data); }

System::UART &System::UART::operator<<(const SystemData::String &data) { return *this->__uart_send__(data.c_str()); }

System::UART &System::UART::operator<<(char command) { return *this->__uart_send__(command); }

System::UART &System::UART::operator<<(unsigned char command) { return *this->__uart_send__(command); }

System::UART &System::UART::operator<<(int data) { return *this->__uart_send__(SystemData::String(data).c_str()); }

System::UART &System::UART::operator<<(unsigned int data) { return *this->__uart_send__(SystemData::String(data).c_str()); }

System::UART &System::UART::operator<<(long data) { return *this->__uart_send__(SystemData::String(data).c_str()); }

System::UART &System::UART::operator<<(unsigned long data) { return *this->__uart_send__(SystemData::String(data).c_str()); }

System::UART &System::UART::operator<<(float data) { return *this->__uart_send__(SystemData::String(data).c_str()); }

System::UART &System::UART::operator<<(double data) { return *this->__uart_send__(SystemData::String(data).c_str()); }

/*
 *   Receiver
 */
unsigned char System::UART::__uart_receive__()
{
  if (__uart_status__ == FALSE)
    return 0x00;
  while (!(check(UCSR0A, RXC0)));
  if (check(UCSR0A, DOR0) || check(UCSR0A, FE0))
  {
    UDR0;
    writeRegister(UCSR0B, RXEN0, FALSE);
    writeRegister(UCSR0B, RXEN0, TRUE);
    return 0x00;
  }
  return UDR0;
}

System::UART &System::UART::operator>>(unsigned char &data)
{
  data = __uart_receive__();
  return *this;
}

/*
 *   Flush RX buffer
 */
void System::UART::Flush(void)
{
  unsigned char f = 0x00;
  while (check(UCSR0A, RXC0))
    if (!f)
      f = UDR0;
}