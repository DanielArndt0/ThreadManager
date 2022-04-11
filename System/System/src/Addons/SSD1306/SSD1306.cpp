#include "Addons/SSD1306/SSD1306.h"

unsigned char System::Addons::OLED::_begin_()
{
  System::Time::Pause(100);
  _clear_ram_();
  System::Com::TWI::Start();
  System::Com::TWI::Write((__i2c_addr__ & __TWI_ADDR_MASK) | __TWI_WRITE);
  System::Com::TWI::Write(__OLED_CMD_STREAM);
  System::Com::TWI::Write(__OLED_DISPLAY_OFF);
  System::Com::TWI::Write(__OLED_DISPLAY_CLK);
  System::Com::TWI::Write(0x80);
  System::Com::TWI::Write(__OLED_MULTIPLEX_RADIO);
  System::Com::TWI::Write(0x3F);
  System::Com::TWI::Write(__OLED_DISPLAY_OFFSET);
  System::Com::TWI::Write(0x00);
  System::Com::TWI::Write(__OLED_START_LINE);
  System::Com::TWI::Write(__OLED_CHARGE_PUMP_CONFIG);
  System::Com::TWI::Write(__OLED_CHARGE_PUMP_ENABLE);
  System::Com::TWI::Write(__OLED_SEGMENT_REMAP_1);
  System::Com::TWI::Write(__OLED_COM_OUTPUT_SCAN_DIRECTION_1);
  System::Com::TWI::Write(__OLED_COM_PINS_HARDWARE_CONFIG);
  System::Com::TWI::Write(0x12);
  System::Com::TWI::Write(__OLED_CONTRAST);
  System::Com::TWI::Write(0x40);
  System::Com::TWI::Write(__OLED_PRE_CHARGE);
  System::Com::TWI::Write(0xF1);
  System::Com::TWI::Write(__OLED_VCOMH);
  System::Com::TWI::Write(0x30);
  System::Com::TWI::Write(__OLED_ENTIRE_DISPLAY_ON);
  System::Com::TWI::Write(__OLED_INVERT_PIXELS_OFF);
  System::Com::TWI::Write(__OLED_SET_MEMORY_ADDR);
  System::Com::TWI::Write(__OLED_HORIZONTAL_MODE);
  System::Com::TWI::Write(__OLED_DISPLAY_ON);
  System::Com::TWI::Stop();
  return 0x01;
}

void System::Addons::OLED::_ssd_cmd_(unsigned char streamMode, unsigned char *cmdArray, unsigned int nCmd)
{
  System::Com::TWI::Start();
  System::Com::TWI::Write((__i2c_addr__ & __TWI_ADDR_MASK) | __TWI_WRITE);
  System::Com::TWI::Write(streamMode);
  for (unsigned int i = 0; i < nCmd; i++)
    System::Com::TWI::Write(cmdArray[i]);
  System::Com::TWI::Stop();
}

void System::Addons::OLED::_ssd_cmd_(unsigned char streamMode, unsigned char cmd)
{
  System::Com::TWI::Start();
  System::Com::TWI::Write((__i2c_addr__ & __TWI_ADDR_MASK) | __TWI_WRITE);
  System::Com::TWI::Write(streamMode);
  System::Com::TWI::Write(cmd);
  System::Com::TWI::Stop();
}

void System::Addons::OLED::_addr_ctrl_(unsigned char column, unsigned char page)
{
  unsigned char cmd[] = {__OLED_SET_PAGE_ADDR, 0x00, __MAX_PAGES, __OLED_SET_COLUMN_ADDR, 0x00, __MAX_COLUMNS};
  cmd[1] = page;
  cmd[4] = column;
  _ssd_cmd_(__OLED_CMD_STREAM, cmd, 6);
}

void System::Addons::OLED::_clear_ram_()
{
  for (unsigned char i = 0; i < 128; i++)
    for (unsigned char j = 0; j < 8; j++)
    {
      _addr_ctrl_(i, j);
      _ssd_cmd_(__OLED_SINGLE_DATA_BYTE, 0x00);
    }
}

void System::Addons::OLED::_set_cursor_(unsigned char x, unsigned char y) { _addr_ctrl_(x, (y / 8)); }

void System::Addons::OLED::_pixel_(unsigned char x, unsigned char y, unsigned char color)
{

  if ((x < 0) || (x >= __widht__) || (y < 0) || (y >= __height__))
    return;
  _set_cursor_(x, y);
  _ssd_cmd_(__OLED_SINGLE_DATA_BYTE, (color ? (0x01 << (y % 8)) : (0x00 << (y % 8))));
}

void System::Addons::OLED::_line_(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color)
{
  int m_new = 2 * (y2 - y1);
  int slope_error_new = m_new - (x2 - x1);
  for (int x = x1, y = y1; x <= x2; x++)
  {
    _pixel_(x, y, color);
    slope_error_new += m_new;
    if (slope_error_new >= 0)
    {
      y++;
      slope_error_new -= 2 * (x2 - x1);
    }
  }
}

void System::Addons::OLED::_v_line_(unsigned char x1, unsigned char y1, unsigned char y2, unsigned char color)
{
  if ((x1 < 0) || (x1 >= __widht__) || (y1 < 0) || (y1 > __height__) || (y2 > __height__) || (y2 < 0))
    return;
  if (y1 < y2)
    for (unsigned int i = y1; i < y2; i++)
      _pixel_(x1, i, color);
  else if (y1 > y2)
  {
    for (unsigned int i = y1; i > y2; i--)
      _pixel_(x1, i, color);
  }
}

void System::Addons::OLED::_h_line_(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char color)
{
  if ((x1 < 0) || (x1 > __widht__) || (y1 < 0) || (y1 >= __height__) || (x2 > __widht__) || (x2 < 0))
    return;
  if (x1 < x2)
    for (unsigned char i = x1; i < x2; i++)
      _pixel_(i, y1, color);
  else if (x1 > x2)
  {
    for (unsigned char i = x1; i > x2; i--)
      _pixel_(i, y1, color);
  }
}

void System::Addons::OLED::_h_scroll_(unsigned char startPage, unsigned char endPage, unsigned char frames, unsigned char direction)
{
  if (endPage < startPage)
    return;
  unsigned char cmd[] = {__DEACTIVATE_SCROLL, (direction ? (unsigned char)__H_RIGHT_SCROLL : (unsigned char)__H_LEFT_SCROLL),
                         0x00, startPage, frames, endPage, 0x00, 0xFF};
  _ssd_cmd_(__OLED_CMD_STREAM, cmd, 8);
}

void System::Addons::OLED::_print_char_(char chr, unsigned char x, unsigned char y, unsigned char color)
{
  chr -= 0x20;
  if (chr < 0 || chr > 128)
    return;
  _set_cursor_(x, y);
  for (unsigned int i = 0; i < 8; i++)
    _ssd_cmd_(__OLED_SINGLE_DATA_BYTE, (color ? pgm_read_byte(&(font[(unsigned char)chr][i])) : 0x00));
}

System::Addons::OLED::OLED(unsigned char widht, unsigned char height, unsigned char i2c_addr) : __widht__(widht), __height__(height), __i2c_addr__(i2c_addr) {}

unsigned char System::Addons::OLED::Begin() { return _begin_(); }

void System::Addons::OLED::drawPixel(unsigned char x, unsigned char y, unsigned char color) { _pixel_(x, y, color); }

void System::Addons::OLED::drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color) { _line_(x1, y1, x2, y2, color); }

void System::Addons::OLED::drawVLine(unsigned char x1, unsigned char y1, unsigned char y2, unsigned char color) { _v_line_(x1, y1, y2, color); }

void System::Addons::OLED::drawHLine(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char color) { _h_line_(x1, x2, y1, color); }

void System::Addons::OLED::writeString(System::Data::String str, unsigned char x, unsigned char y, unsigned char color)
{
  for (unsigned char i = 0, xs = x, ys = y; i < str.Length(); i++)
  {
    if (!(i % (__widht__ / 8)) && i)
      ys += 8; // 8 e o altura da fonte
    _print_char_(str.At(i), xs, ys, WHITE);
    xs += 8; // 8 e a largura da fonte
  }
}

void System::Addons::OLED::writeChar(unsigned char chr, unsigned char x, unsigned char y, unsigned char color) { _print_char_(chr, x, y, color); }

void System::Addons::OLED::horizontalScrollSetup(unsigned char startPage, unsigned char endPage, unsigned char frames, unsigned char direction) { _h_scroll_(startPage, endPage, frames, direction); }

void System::Addons::OLED::ActivateScroll() { _ssd_cmd_(__OLED_SINGLE_CMD_BYTE, __ACTIVATE_SCROLL); }

void System::Addons::OLED::DeactivateScroll() { _ssd_cmd_(__OLED_SINGLE_CMD_BYTE, __DEACTIVATE_SCROLL); }

void System::Addons::OLED::Clear() { _clear_ram_(); }

void System::Addons::OLED::invertAxis(unsigned char x, unsigned char y)
{
  unsigned char cmd[] = {(x ? (unsigned char)__OLED_SEGMENT_REMAP_0 : (unsigned char)__OLED_SEGMENT_REMAP_1),
                         (y ? (unsigned char)__OLED_COM_OUTPUT_SCAN_DIRECTION_0 : (unsigned char)__OLED_COM_OUTPUT_SCAN_DIRECTION_1)};
  _ssd_cmd_(__OLED_SINGLE_CMD_BYTE, cmd, 2);
}

void System::Addons::OLED::invertColors(unsigned char mode) { _ssd_cmd_(__OLED_SINGLE_CMD_BYTE, (mode ? (unsigned char)__OLED_INVERT_PIXELS_ON : (unsigned char)__OLED_INVERT_PIXELS_OFF)); }

void System::Addons::OLED::Contrast(unsigned char contrast)
{
  unsigned char cmd[] = {__OLED_CONTRAST, contrast};
  _ssd_cmd_(__OLED_CMD_STREAM, cmd, 2);
}

void System::Addons::OLED::On() { _ssd_cmd_(__OLED_SINGLE_CMD_BYTE, __OLED_DISPLAY_ON); }

void System::Addons::OLED::Off() { _ssd_cmd_(__OLED_SINGLE_CMD_BYTE, __OLED_DISPLAY_OFF); }

void System::Addons::OLED::Command(unsigned char streamMode, unsigned char *cmdArray, unsigned int nCmd) { _ssd_cmd_(streamMode, cmdArray, nCmd); }

void System::Addons::OLED::Command(unsigned char streamMode, unsigned char cmd) { _ssd_cmd_(streamMode, cmd); }