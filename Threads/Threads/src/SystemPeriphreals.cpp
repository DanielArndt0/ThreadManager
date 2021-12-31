#include "SystemPeriphreals.h"

unsigned char System::GPIO::__aref__ = 0x01;

unsigned char System::GPIO::_port_selector_(volatile unsigned char **reg, unsigned char pin, unsigned char value)
{
  if (pin < 8)
    writeRegister(*reg[0], pin, value);
  else if (pin >= 8 && pin < 14)
    writeRegister(*reg[1], (pin - 8), value);
  else if (pin >= 14 && pin < 20)
    writeRegister(*reg[2], (pin - 14), value);
  return FALSE;
}

unsigned char System::GPIO::_port_selector_(volatile unsigned char **reg, unsigned char pin)
{
  if (pin < 8)
    check(*reg[0], pin);
  else if (pin >= 8 && pin < 14)
    check(*reg[1], (pin - 8));
  else if (pin >= 14 && pin < 20)
    check(*reg[2], (pin - 14));
  return FALSE;
}

unsigned int System::GPIO::analogReadBits(unsigned char pin)
{
  unsigned char __low__, __high__;
  writeRegister(ADCSRA, ADEN, TRUE);
  writeRegister(ADCSRA, ADPS2, TRUE);
  writeRegister(ADCSRA, ADPS1, FALSE);
  writeRegister(ADCSRA, ADPS0, TRUE);
  ADMUX = (__aref__ << 6) | (pin & 0x07);
  writeRegister(DIDR0, pin, TRUE);
  writeRegister(ADCSRA, ADSC, TRUE);
  while (check(ADCSRA, ADSC));
  __low__ = ADCL;
  __high__ = ADCH;
  writeRegister(DIDR0, pin, FALSE);
  return shiftLeft(__high__, 0x08) | __low__;
}

float System::GPIO::analogReadVolts(unsigned char pin) { return ADC_VOLTAGE(analogReadBits(pin)); }

void System::GPIO::pinConfig(unsigned char pin, unsigned char mode)
{
  volatile unsigned char *reg[3] = {&PORTD, &PORTB, &PORTC};
  _port_selector_(reg, pin, mode);
}

void System::GPIO::pinWrite(unsigned char pin, unsigned char value)
{
  volatile unsigned char *reg[3] = {&PORTD, &PORTB, &PORTC};
  _port_selector_(reg, pin, value);
}

unsigned char System::GPIO::pinRead(unsigned char pin)
{
  volatile unsigned char *reg[3] = {&PORTD, &PORTB, &PORTC};
  return _port_selector_(reg, pin);
}
