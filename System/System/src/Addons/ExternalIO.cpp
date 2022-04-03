#include "ExternalIO.h"

#include "Time/SystemTime.h"
extern System::Time Clock;

System::Addons::ExternalIO::ExternalIO(const unsigned char *pinoutArray) : __pin__(pinoutArray) {}

void System::Addons::ExternalIO::_ctrl_bits_setting_()
{
  System::GPIO::pinConfig(__pin__[__CTRL], OUTPUT);
  _ctrl_clock_(__LOW_);
}

void System::Addons::ExternalIO::_ctrl_clock_(unsigned char mode) { System::GPIO::pinWrite(__pin__[__CTRL], mode); }

void System::Addons::ExternalIO::_load_data_bus_(unsigned char value)
{
  for (unsigned int i = __D0; i <= __D7; i++)
  {
    System::GPIO::pinConfig(__pin__[i], OUTPUT);
    System::GPIO::pinWrite(__pin__[i], (__CHECK(value, i - __D0) ? 0x01 : 0x00));
  }
}

void System::Addons::ExternalIO::_write_in_port_(unsigned char value, unsigned char port)
{
  // Carrega o endereço do port no barramento de dados
  _load_data_bus_(port);
  _ctrl_clock_(__HIGH_);

  // Carrega o valor do endereço da memória no barramento de dados
  _load_data_bus_(value);
  _ctrl_clock_(__LOW_);
}

void System::Addons::ExternalIO::_write_in_sram_(unsigned char value, unsigned char addr)
{
  // Configura pino de controle;
  _ctrl_bits_setting_();

  // Escreve no port 1
  _write_in_port_(__LOW(addr), __PORTA_SRAM);

  // Escreve no port 2
  _write_in_port_(__HIGH(addr) | __WRITE_EX_SRAM, __PORTB_SRAM);

  // Carrega os dados a serem escritos na SRAM no barramento.
  _ctrl_clock_(__HIGH_);
  _load_data_bus_(value);
  _ctrl_clock_(__LOW_);

  // Limpa barramento de dados
  _load_data_bus_(0x00);
}

unsigned char System::Addons::ExternalIO::_read_data_bus_()
{
  unsigned char temp = 0x00;
  // Configura o GPIO para input
  for (unsigned int i = __D0; i <= __D7; i++)
    System::GPIO::pinConfig(__pin__[i], INPUT);

  // Ativa leitura da SRAM
  _ctrl_clock_(__HIGH_);
  DDRD = 0xFF;
  // Escreve os dados lidos em uma variavel temporária
  for (unsigned int i = __D0; i <= __D7; i++)
  {
    if (System::GPIO::pinRead(__pin__[i]))
      PORTD |= 0x01 << (i - __D0);//__SET();//__SET(PORTD, (i - __D0));
    else
      __CLEAR(PORTD, (i - __D0));
  }
  // Desabilita fluxo de dados da SRAM
  _ctrl_clock_(__LOW_);
  
  //
  for (unsigned int i = __D0; i <= __D7; i++)
    System::GPIO::pinConfig(__pin__[i], OUTPUT);

  return temp;
}

unsigned char System::Addons::ExternalIO::_read_sram_(unsigned char addr)
{
  // Configura pino de controle;
  _ctrl_bits_setting_();

  // Escreve no port 1
  _write_in_port_(__LOW(addr), __PORTA_SRAM);

  // Escreve no port 2
  _write_in_port_(__HIGH(addr) | __READ_EX_SRAM, __PORTB_SRAM);

  // Limpa barramento de dados
  _load_data_bus_(0x00);

  return _read_data_bus_();
}

void System::Addons::ExternalIO::WriteSRAM(unsigned char value, unsigned char addr) { _write_in_sram_(value, addr); }

unsigned char System::Addons::ExternalIO::ReadSRAM(unsigned char addr) { return _read_sram_(addr); }