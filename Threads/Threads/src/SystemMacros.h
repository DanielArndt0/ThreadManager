#pragma once

// System
#define systemClock 16000000

// Boolean
#define FALSE 0x00
#define TRUE 0x01

// Address 0
//#define NULL ((void *)0)

// Registers
#define set(byte, bit) ((byte) |= (0x01 << (bit)))
#define clear(byte, bit) ((byte) &= ~(0x01 << (bit)))
#define check(byte, bit) ((byte) & (0x01 << (bit)))
#define flip(byte, bit) ((byte) ^= (0x01 << (bit)))
//#define writeRegister(byte, bit, value) ((value) == TRUE ? ((byte) |= (0x01 << (bit))) : ((byte) &= ~(0x01 << (bit))))
#define writeRegister(byte, bit, value) ((value) == TRUE ? set((byte), (bit)) : clear((byte), (bit)))
#define shiftRight(byte, shift) ((byte) >> shift)
#define shiftLeft(byte, shift) ((byte) << shift)
#define high(byte) ((byte) >> (0x08))
#define low(byte) ((byte) & (0xFF))

// Analog-Digital
#define ADC_VOLTAGE(x) (x * (5.0 / 1024.0))

// Power
#define E1 10
#define E2 100
#define E3 1000
#define E4 10000
#define E5 100000
#define E6 1000000
#define E7 10000000
#define E8 100000000
#define E9 1000000000