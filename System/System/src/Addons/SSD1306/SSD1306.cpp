#include "Addons/SSD1306/SSD1306.h"

unsigned char System::Addons::OLED::_begin_()
{
  if (!__buffer__)
    if ((__buffer__ = (unsigned char *)calloc((__widht__ * __height__) / 8, sizeof(unsigned char))) == NULL)
      return 0x00;
  System::Time::Pause(100);
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
  Commit();
  return 0x01;
}

System::Addons::OLED::OLED(unsigned char widht, unsigned char height, unsigned char i2c_addr) : __widht__(widht), __height__(height), __i2c_addr__(i2c_addr) {}

System::Addons::OLED::~OLED()
{
  if (__buffer__)
    free(__buffer__);
}

unsigned char System::Addons::OLED::Begin() { return _begin_(); }

void System::Addons::OLED::drawPixel(unsigned char x, unsigned char y)
{
  if ((x < 0) || (x >= __widht__) || (y < 0) || (y >= __height__))
    return;
  __buffer__[x + (y / 8) * __widht__] |= 0x01 << (y % 8);
}

void System::Addons::OLED::erasePixel(unsigned char x, unsigned char y)
{
  if ((x < 0) || (x >= __widht__) || (y < 0) || (y >= __height__))
    return;
  __buffer__[x + (y / 8) * __widht__]  &= ~(0x01 << (y % 8));
}

void System::Addons::OLED::drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{
  int m_new = 2 * (y2 - y1);               
  int slope_error_new = m_new - (x2 - x1);
  for (int x = x1, y = y1; x <= x2; x++)
  {
    drawPixel(x, y);          
    slope_error_new += m_new; 
    if (slope_error_new >= 0) 
    {
      y++;                              
      slope_error_new -= 2 * (x2 - x1); 
    }
  }
}

void System::Addons::OLED::eraseLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{
  int m_new = 2 * (y2 - y1);               
  int slope_error_new = m_new - (x2 - x1);
  for (int x = x1, y = y1; x <= x2; x++)
  {
    erasePixel(x, y);          
    slope_error_new += m_new; 
    if (slope_error_new >= 0)
    {
      y++;
      slope_error_new -= 2 * (x2 - x1); 
    }
  }
}

void System::Addons::OLED::drawVLine(unsigned char x1, unsigned char y1, unsigned char y2)
{
  if ((x1 < 0) || (x1 >= __widht__) || (y1 < 0) || (y1 > __height__) || (y2 > __height__) || (y2 < 0))
    return;
  if (y1 < y2)
    for (unsigned int i = y1; i < y2; i++)
      drawPixel(x1, i);
  else if (y1 > y2)
  {
    for (unsigned int i = y1; i > y2; i--)
      drawPixel(x1, i);
  }
}

void System::Addons::OLED::eraseVLine(unsigned char x1, unsigned char y1, unsigned char y2)
{
  if ((x1 < 0) || (x1 >= __widht__) || (y1 < 0) || (y1 > __height__) || (y2 > __height__) || (y2 < 0))
    return;
  if (y1 < y2)
    for (unsigned int i = y1; i < y2; i++)
      erasePixel(x1, i);
  else if (y1 > y2)
  {
    for (unsigned int i = y1; i > y2; i--)
      erasePixel(x1, i);
  }
}

void System::Addons::OLED::drawHLine(unsigned char x1, unsigned char x2, unsigned char y1)
{
  if ((x1 < 0) || (x1 > __widht__) || (y1 < 0) || (y1 >= __height__) || (x2 > __widht__) || (x2 < 0))
    return;
  if (x1 < x2)
    for (unsigned int i = x1; i < x2; i++)
      drawPixel(i, y1);
  else if (x1 > x2)
  {
    for (unsigned int i = x1; i > x2; i--)
      drawPixel(i, y1);
  }
}

void System::Addons::OLED::eraseHLine(unsigned char x1, unsigned char x2, unsigned char y1)
{
  if ((x1 < 0) || (x1 > __widht__) || (y1 < 0) || (y1 >= __height__) || (x2 > __widht__) || (x2 < 0))
    return;
  if (x1 < x2)
    for (unsigned int i = x1; i < x2; i++)
      erasePixel(i, y1);
  else if (x1 > x2)
  {
    for (unsigned int i = x1; i > x2; i--)
      erasePixel(i, y1);
  }
}

void System::Addons::OLED::invertDisplay(unsigned char mode)
{
  System::Com::TWI::Start();
  System::Com::TWI::Write((__i2c_addr__ & __TWI_ADDR_MASK) | __TWI_WRITE);
  System::Com::TWI::Write(__OLED_SINGLE_CMD_BYTE);
  System::Com::TWI::Write((mode ? __OLED_COM_OUTPUT_SCAN_DIRECTION_0 : __OLED_COM_OUTPUT_SCAN_DIRECTION_1));
  System::Com::TWI::Stop();
}

void System::Addons::OLED::invertColors(unsigned char mode)
{
  System::Com::TWI::Start();
  System::Com::TWI::Write((__i2c_addr__ & __TWI_ADDR_MASK) | __TWI_WRITE);
  System::Com::TWI::Write(__OLED_SINGLE_CMD_BYTE);
  System::Com::TWI::Write((mode ? __OLED_INVERT_PIXELS_ON : __OLED_INVERT_PIXELS_OFF));
  System::Com::TWI::Stop();
}

void System::Addons::OLED::Contrast(unsigned char contrast)
{
  System::Com::TWI::Start();
  System::Com::TWI::Write((__i2c_addr__ & __TWI_ADDR_MASK) | __TWI_WRITE);
  System::Com::TWI::Write(__OLED_CMD_STREAM);
  System::Com::TWI::Write(__OLED_CONTRAST);
  System::Com::TWI::Write(contrast);
  System::Com::TWI::Stop();
}

void System::Addons::OLED::On()
{
  System::Com::TWI::Start();
  System::Com::TWI::Write((__i2c_addr__ & __TWI_ADDR_MASK) | __TWI_WRITE);
  System::Com::TWI::Write(__OLED_CMD_STREAM);
  System::Com::TWI::Write(__OLED_DISPLAY_ON);
  System::Com::TWI::Stop();
}

void System::Addons::OLED::Off()
{
  System::Com::TWI::Start();
  System::Com::TWI::Write((__i2c_addr__ & __TWI_ADDR_MASK) | __TWI_WRITE);
  System::Com::TWI::Write(__OLED_CMD_STREAM);
  System::Com::TWI::Write(__OLED_DISPLAY_OFF);
  System::Com::TWI::Stop();
}

void System::Addons::OLED::Commit()
{
  System::Com::TWI::Start();
  System::Com::TWI::Write((__i2c_addr__ & __TWI_ADDR_MASK) | __TWI_WRITE);
  System::Com::TWI::Write(__OLED_DATA_STREAM);
  for (unsigned int i = 0; i < ((__widht__ * __height__) / 8); i++)
    System::Com::TWI::Write(__buffer__[i]);
  System::Com::TWI::Stop();
}