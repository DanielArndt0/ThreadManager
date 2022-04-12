#include "Macros/SystemMacros.h"
#include "CoadjutorSystem/CoadjutorInterrupt.h"
#include "Errors/SystemErrors.h"
#include "Managers/ThreadManager.h"
#include "Time/SystemTime.h"
#include "Com/SystemUART.h"
#include "Com/SystemTWI.h"
#include "Memory/SystemEEPROM.h"
#include "Memory/SystemSRAM.h"
#include "Peripherals/SystemPeriphreals.h"
#include "DataTypes/SystemTypes.h"
#include "Addons/SSD1306/SSD1306.h"

/*
   Sistema:
   - Desenvolvido sistema de Threads;
   - Desenvolvido ThreadManager;
   - ThreadStack automatizada;
   - Configurações de Sistema adicionadas;
   - ThreadManager e Threads remodelados;

   Periféricos:
    - Desenvolvidas Funções básicas de Tempo;
    - Desenvolvidas Funções básicas de Comunicação serial;
    - Desenvolvidas Funções básicas de Protocolo I2C;
    - Desenvolvidas Funções básicas de EEPROM;
    - Desenvolvidas Funções de Leitura analógica;

   Tipos:
    - Desenvolvido tipo de dado String;
    - Desenvolvido tipo de dado Vector;
    - Desenvolvido tipo de dado Duet;
    - Desenvolvido tipo de dado LIFO;
    - Desenvolvido tipo de dado FIFO;

   EEPROM:
    - Desenvolvido funções WriteString, ReadString e outras para controle de memória.
    - Adicionado funções para escrita de dados primitivos maiores de 1 byte.
    - Otimizado funções da EEPROM;

   RAM:
    - Desenvolvido classe para monitorar consumo da RAM;
    - Adicionado metodo para vizualizar stackFrame;

   Afazeres:
    Sistema:
     - Organizar software no geral;
     - Desenvolver gerenciador de memória;
     - Desenvolver programação por eventos de hardware;
     - Desenvolver Sistema de erros com stack trace;


    Tipos:
    - Desenvolver tipo Typeof;
     - Desenvolver tipo Tuple;
     - Desenvolver tipo de dado Array;
     - Desenvolver tipo de dado List;
     - Desenvolver tipo de dado Map;
     - Desenvolver tipo de dado Bitset;
     - Desenvolver tipo de dado UniqueSet;

    EEPROM:
     - Otimizar sistema de Get partições;
     - Desenvolver sistema de partições;
     - Arrumar biblioteca de partições;

    String:
     - Corrigir vazamento de memória na função _concat_()
     - Desenvolver um formatador de strings;

    Serial:
     - Desenvolver StackBuffer Serial;

    I2C:
     - Otimizar Funções de I2C, adicionando verificações contra erros e buffers virtuais;

    PWM:
     - Desenvolver Funções de PWM;

    Interrupções:
     - Adicionar mais funções para configurar interrupções;

    SSD1306:
     - Adicionar classe fonte;
     - Organizar bibliotecas graficas;
     - Desenvolver funções praticas para posicionamento de strings;

*/

using namespace System;
using namespace Memory;
using namespace Data;

#define HEIGHT 64
#define WIDTH 128
#define __DSP_ADDR 0x78

System::Managers::ThreadManager Manager;
System::Com::UART Serial;
System::Com::TWI I2C;
System::GPIO Hardware;
System::Time Clock;
System::Memory::EEPROM eeprom;
System::Memory::RAM ram;
System::Addons::OLED Display(WIDTH, HEIGHT, __DSP_ADDR);

int main(void)
{
  Clock.Begin();
  I2C.Begin(400000);
  Serial.Begin(9600);
  Display.Begin();

  Display.drawHLine(0, 127, 0);
  Display.drawHLine(0, 127, 63);
  Display.drawVLine(0, 0, 63);
  Display.drawVLine(127, 0, 63);

  while (1)
  {
  }

  return 0;
}