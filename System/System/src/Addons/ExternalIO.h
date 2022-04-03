#pragma once
#include "Macros/SystemMacros.h"
#include "Peripherals/SystemPeriphreals.h"

#define __READ_EX_SRAM  (0x20 & 0x60)
#define __WRITE_EX_SRAM  (0x00 & 0x60)
#define __SAVE_EX_SRAM  (0x60 & 0x60)

#define __PORTA_SRAM 1
#define __PORTB_SRAM 2

#define __HIGH_ 1
#define __LOW_ 0

#define __CTRL 0
#define __D0 1
#define __D1 2
#define __D2 3
#define __D3 4
#define __D4 5
#define __D5 6
#define __D6 7
#define __D7 8

/*
  ---- Control bits ----
  __pin__[0]  -> Control Pin

  ---- Data bits ----
  __pin__[1]  -> D0
  __pin__[2]  -> D1
  __pin__[3]  -> D2
  __pin__[4]  -> D3
  __pin__[5]  -> D4
  __pin__[6]  -> D5
  __pin__[7]  -> D6
  __pin__[8] -> D7
*/

namespace System
{
  namespace Addons
  {
    class ExternalIO
    {
    private:
      const unsigned char *__pin__;

    private:
      // Config
      void _ctrl_bits_setting_();
      void _ctrl_clock_(unsigned char mode);
      //void _select_port_(unsigned char port);
      
      // Write to data bus
      void _load_data_bus_(unsigned char value);
      
      // Write SRAM Address
      void _write_in_port_(unsigned char value, unsigned char port);
      
      // Write SRAM
      void _write_in_sram_(unsigned char value, unsigned char addr);

      // Read Data Bus;
      unsigned char _read_data_bus_();

      // Read SRAM
      unsigned char _read_sram_(unsigned char addr);

    public:
      ExternalIO(const unsigned char *pinoutArray);

    public:
      void WriteSRAM(unsigned char value, unsigned char addr);
      unsigned char ReadSRAM(unsigned char addr);
    };
  }
}
