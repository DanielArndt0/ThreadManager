#include "SystemUART.h"

unsigned int System::UART::__uart_status__ = FALSE;
System::UART *System::UART::__buff__;

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
    return __buff__;
  while (!(check(UCSR0A, UDRE0)));
  UDR0 = data;
  while (!(check(UCSR0A, TXC0)));
  return __buff__;
}

System::UART *System::UART::__uart_send__(const char *data)
{
  if (__uart_status__ == FALSE)
    return __buff__;
  for (register unsigned int i = 0x00; i < (unsigned int)strlen(data); i++)
    __uart_send__(data[i]);
  return __buff__;
}

System::UART &System::operator<<(System::UART &buff, const char *data)
{
  buff.__uart_send__(data);
  return buff;
}

/*
 *   Receiver
 */
unsigned char System::UART::__uart_receive__()
{
  if (__uart_status__ == FALSE)
    return 0x00;
  while (!(check(UCSR0A, RXC0)))
    ;
  if (check(UCSR0A, DOR0) || check(UCSR0A, FE0))
  {
    UDR0;
    writeRegister(UCSR0B, RXEN0, FALSE);
    writeRegister(UCSR0B, RXEN0, TRUE);
    return 0x00;
  }
  return UDR0;
}

System::UART &System::operator>>(System::UART &buff, unsigned char data)
{
  data = buff.__uart_receive__();
  return buff;
}

/*
 *   Flush RX buffer
 */
void System::UART::Flush(void)
{
  while (check(UCSR0A, RXC0))
    UDR0;
}