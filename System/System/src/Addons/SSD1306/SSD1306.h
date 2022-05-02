#pragma once

#include <stdlib.h>
#include "DataTypes/SystemTypes.h"
#include "Addons/SSD1306/macros.h"
#include "Addons/SSD1306/font.h"
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

    protected:
      unsigned char _begin_();
      void _ssd_cmd_(unsigned char streamMode, unsigned char *cmdArray, unsigned int nCmd);
      void _ssd_cmd_(unsigned char streamMode, unsigned char cmd);
      void _addr_ctrl_(unsigned char column, unsigned char page);
      void _clear_ram_();
      void _set_cursor_(unsigned char x, unsigned char y);
      void _pixel_(unsigned char x, unsigned char y, unsigned char color);
      void _line_(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color);
      void _v_line_(unsigned char x1, unsigned char y1, unsigned char y2, unsigned char color);
      void _h_line_(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char color);
      void _h_scroll_(unsigned char startPage, unsigned char endPage, unsigned char frames, unsigned char direction);
      void _write_char_(char chr, unsigned char x, unsigned char y, unsigned char color);
      void _write_str_(Data::String str, unsigned char x, unsigned char y, unsigned char color = WHITE);

    public:
      OLED(unsigned char widht, unsigned char height, unsigned char i2c_addr);

    public:
      unsigned char Begin();

      void setCursor(unsigned char x, unsigned char y);
      void drawPixel(unsigned char x, unsigned char y, unsigned char color = WHITE);
      void drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color = WHITE);
      void drawVLine(unsigned char x1, unsigned char y1, unsigned char y2, unsigned char color = WHITE);
      void drawHLine(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char color = WHITE);

      void writeString(Data::String str, unsigned char x, unsigned char y, unsigned char color = WHITE);
      void writeChar(unsigned char chr, unsigned char x, unsigned char y, unsigned char color = WHITE);

      void horizontalScrollSetup(unsigned char startPage, unsigned char endPage, unsigned char frames, unsigned char direction);
      void ActivateScroll();
      void DeactivateScroll();

      void On();
      void Off();
      void Clear();
      void invertAxis(unsigned char x = __OLED_SEGMENT_REMAP_1, unsigned char y = __OLED_COM_OUTPUT_SCAN_DIRECTION_1);
      void invertColors(unsigned char mode = __OLED_INVERT_PIXELS_OFF);
      void Contrast(unsigned char contrast = 0x7F);

      void Command(unsigned char streamMode, unsigned char *cmdArray, unsigned int nCmd);
      void Command(unsigned char streamMode, unsigned char cmd);
    };
  }
}