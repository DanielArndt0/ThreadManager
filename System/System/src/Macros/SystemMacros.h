#pragma once

// System
#define __SYSTEM_CLOCK 16E6

// EEPROM
#define __EEPROM_SIZE 0x400

// SRAM
#define __START_ADDR_SRAM 0x0100
#define __END_ADDR_SRAM 0x08FF

// Addressing
#define __OFFSET (0x20)
#define __MEMIO_ADDR(addr) (*(volatile unsigned char *)(addr))
#define __IO_ADDR(addr) (*((volatile unsigned char *)(addr) + __OFFSET))

// Registers
#define __SET(byte, bit) ((byte) |= (0x01 << (bit)))
#define __CLEAR(byte, bit) ((byte) &= ~(0x01 << (bit)))
#define __CHECK(byte, bit) ((byte) & (0x01 << (bit)))
#define __FLIP(byte, bit) ((byte) ^= (0x01 << (bit)))
#define __WRITE_REG(byte, bit, value) ((value) == __TRUE ? __SET((byte), (bit)) : __CLEAR((byte), (bit)))
#define __SHIFTR(byte, shift) ((byte) >> shift)
#define __SHIFTL(byte, shift) ((byte) << shift)
#define __HIGH(byte) ((byte) >> (0x08))
#define __LOW(byte) ((byte) & (0xFF))

// Analog-Digital
#define __ADC_VOLTAGE(x) (x * (5.0 / 1024.0))

// Math
#define __ABSOLUTE(x) (x >= 0x00 ? x : (x * (-0x01)))

// Boolean
#define __FALSE 0x00
#define __TRUE 0x01

// Serial macros
#define cmd(comma) (char)(comma)
#define endl cmd(0x0A) << cmd(0x0D)