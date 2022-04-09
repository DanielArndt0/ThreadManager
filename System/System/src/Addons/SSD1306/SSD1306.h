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
      void _erase_pixel_(unsigned char x, unsigned char y);

    public:
      OLED(unsigned char widht, unsigned char height, unsigned char i2c_addr);
      ~OLED();

    public:
      unsigned char Begin();
      void drawPixel(unsigned char x, unsigned char y);
      void erasePixel(unsigned char x, unsigned char y);
      void drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
      void eraseLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
      void drawVLine(unsigned char x1, unsigned char y1, unsigned char y2);
      void eraseVLine(unsigned char x1, unsigned char y1, unsigned char y2);
      void drawHLine(unsigned char x1, unsigned char x2, unsigned char y1);
      void eraseHLine(unsigned char x1, unsigned char x2, unsigned char y1);
      void invertDisplay(unsigned char mode = __OLED_COM_OUTPUT_SCAN_DIRECTION_1);
      void invertColors(unsigned char mode = __OLED_INVERT_PIXELS_OFF);
      void Contrast(unsigned char contrast = 0x7F);
      void On();
      void Off();
      void Commit();
    };
  }
}