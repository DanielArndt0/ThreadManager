#include "Com/SystemTWI.h"

void System::Com::TWI::twi_begin(unsigned long freq)
{
  TWSR = 0x00;
  TWBR = ((__SYSTEM_CLOCK / freq) - 16) / 2;
  TWCR = (1 << TWEN);
}

void System::Com::TWI::twi_start(void)
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!__CHECK(TWCR, TWINT))
    ;
}

void System::Com::TWI::twi_restart()
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!__CHECK(TWCR, TWINT))
    ;
}

void System::Com::TWI::twi_write(unsigned char byte)
{
  TWDR = byte;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!__CHECK(TWCR, TWINT))
    ;
}

unsigned char System::Com::TWI::twi_read()
{
  unsigned char data = 0x00;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!__CHECK(TWCR, TWINT))
    ;
  data = TWDR;
  return data;
}

void System::Com::TWI::twi_stop(void) { TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); }

void System::Com::TWI::twi_disable(void) { TWCR = 0x00; }

void System::Com::TWI::Begin(unsigned long frequency) { twi_begin(frequency); }

void System::Com::TWI::Start() { twi_start(); }

void System::Com::TWI::Restart() { twi_restart(); }

void System::Com::TWI::Write(unsigned char byte) { twi_write(byte); }

unsigned char System::Com::TWI::Read() { return twi_read(); }

void System::Com::TWI::Stop() { twi_stop(); }

void System::Com::TWI::Send(unsigned char data, unsigned char addr)
{
  twi_start();
  twi_write((addr & __TWI_ADDR_MASK) | __TWI_WRITE);
  twi_write(data);
  twi_stop();
}

unsigned char System::Com::TWI::Receive(unsigned char addr)
{
  unsigned char data = 0x00;
  twi_start();
  twi_write((addr & __TWI_ADDR_MASK) | __TWI_READ);
  data = twi_read();
  twi_stop();
  return data;
}

void System::Com::TWI::Disable() { twi_disable(); }