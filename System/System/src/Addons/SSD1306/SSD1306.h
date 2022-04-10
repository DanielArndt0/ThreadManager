#pragma once

#include <stdlib.h>
#include "Addons/SSD1306/macros.h"
#include "Com/SystemTWI.h"
#include "Time/SystemTime.h"

namespace System
{
  namespace Addons
  {
    class OLED
    {
    private:
      unsigned char *__buffer__;
      unsigned char __widht__;
      unsigned char __height__;
      unsigned char __i2c_addr__;

    private:
      unsigned char _begin_();
      void _pixel_(unsigned char x, unsigned char y, unsigned char mode);
      void _line_(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char mode);
      void _v_line_(unsigned char x1, unsigned char y1, unsigned char y2, unsigned char mode);
      void _h_line_(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char mode);

    public:
      OLED(unsigned char widht, unsigned char height, unsigned char i2c_addr);
      ~OLED();

    public:
      unsigned char Begin();

      void drawPixel(unsigned char x, unsigned char y, unsigned char color = 1);
      void drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color = 1);
      void drawVLine(unsigned char x1, unsigned char y1, unsigned char y2, unsigned char color = 1);
      void drawHLine(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char color = 1);

      void invertDisplay(unsigned char mode = __OLED_COM_OUTPUT_SCAN_DIRECTION_1);
      void invertColors(unsigned char mode = __OLED_INVERT_PIXELS_OFF);
      void Contrast(unsigned char contrast = 0x7F);
      void On();
      void Off();
      void Commit();
    };
  }
}