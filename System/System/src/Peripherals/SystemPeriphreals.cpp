#include "Peripherals/SystemPeriphreals.h"

unsigned char System::GPIO::__aref__ = 0x01;

unsigned char System::GPIO::_port_selector_(volatile unsigned char **reg, unsigned char pin, unsigned char value)
{
  if (pin < 8)
    __WRITE_REG(*reg[0], pin, value);
  else if (pin >= 8 && pin < 14)
    __WRITE_REG(*reg[1], (pin - 8), value);
  else if (pin >= 14 && pin < 20)
    __WRITE_REG(*reg[2], (pin - 14), value);
  return __FALSE;
}

unsigned char System::GPIO::_port_selector_(volatile unsigned char **reg, unsigned char pin)
{
  if (pin < 8)
  {
    if (__CHECK(*reg[0], pin))
      return 0x01;
    else if (pin >= 8 && pin < 14)
    {
      if (__CHECK(*reg[1], (pin - 8)))
        return 0x01;
    }
    else if (pin >= 14 && pin < 20)
    {
      if (__CHECK(*reg[2], (pin - 14)))
        return 0x01;
    }
  }
  return __FALSE;
}

unsigned int System::GPIO::_analog_read_(unsigned char pin)
{
  unsigned char __low__, __high__;
  __WRITE_REG(ADCSRA, ADEN, __TRUE);
  __WRITE_REG(ADCSRA, ADPS2, __TRUE);
  __WRITE_REG(ADCSRA, ADPS1, __FALSE);
  __WRITE_REG(ADCSRA, ADPS0, __TRUE);
  ADMUX = (__aref__ << 6) | (pin & 0x07);
  __WRITE_REG(DIDR0, pin, __TRUE);
  __WRITE_REG(ADCSRA, ADSC, __TRUE);
  while (__CHECK(ADCSRA, ADSC))
    ;
  __low__ = ADCL;
  __high__ = ADCH;
  __WRITE_REG(DIDR0, pin, __FALSE);
  return __SHIFTL(__high__, 0x08) | __low__;
}

unsigned int System::GPIO::analogReadBits(unsigned char pin) { return _analog_read_(pin); }

float System::GPIO::analogReadVolts(unsigned char pin) { return __ADC_VOLTAGE(_analog_read_(pin)); }

void System::GPIO::pinConfig(unsigned char pin, unsigned char mode)
{
  volatile unsigned char *reg[3] = {&DDRD, &DDRB, &DDRC};
  _port_selector_(reg, pin, mode);
}

void System::GPIO::pinWrite(unsigned char pin, unsigned char value)
{
  volatile unsigned char *reg[3] = {&PORTD, &PORTB, &PORTC};
  _port_selector_(reg, pin, value);
}

unsigned char System::GPIO::pinRead(unsigned char pin)
{
  volatile unsigned char *reg[3] = {&PIND, &PINB, &PINC};
  return _port_selector_(reg, pin);
}
