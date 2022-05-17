#include "Interrupt/UART.h"

void CoadjutorSystem::UART_INT::RxEnable()
{
  __WRITE_REG(SREG, SREG_I, __FALSE);
  __WRITE_REG(UCSR0B, RXCIE0, __TRUE);
  __WRITE_REG(SREG, SREG_I, __TRUE);
}

void CoadjutorSystem::UART_INT::RxDisable()
{
  __WRITE_REG(SREG, SREG_I, __FALSE);
  __WRITE_REG(UCSR0B, RXCIE0, __FALSE);
  __WRITE_REG(SREG, SREG_I, __TRUE);
}

unsigned char CoadjutorSystem::UART_INT::RxStatus() { return __CHECK(UCSR0B, RXCIE0); }