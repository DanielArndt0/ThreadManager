#include "Macros/SystemMacros.h"
#include "CoadjutorSystem/CoadjutorInterrupt.h"
#include "Errors/SystemErrors.h"
#include "Managers/ThreadManager.h"
#include "Time/SystemTime.h"
#include "Com/SystemUART.h"
#include "Memory/SystemEEPROM.h"
#include "Memory/SystemSRAM.h"
#include "Peripherals/SystemPeriphreals.h"
#include "DataTypes/SystemTypes.h"
#include "Properties/PartitionProperties.h"
#include "Addons/EEPROMPartition.h"
#include "Addons/ExternalIO.h"

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
     - Desenvolver um formatador de strings;

    Serial:
     - Desenvolver StackBuffer Serial;

    I2C:
     - Desenvolver Funções básicas de I2C;

    PWM:
     - Desenvolver Funções de PWM;

    Interrupções:
     - Adicionar mais funções para configurar interrupções;

*/

using namespace System;
using namespace Memory;
using namespace Properties;
using namespace Data;

void printMemoryMap(unsigned char *memMap, unsigned row);
void vTask0(void);
void vTask1(void);
void vTask2(void);
void vTask3(void);
void vTask4(void);
void vTask5(void);
void vTask6(void);
void vTask7(void);
void vTask8(void);
void vTask9(void);

System::Managers::ThreadManager Manager;
System::Com::UART Serial;
System::GPIO Hardware;
System::Time Clock;
System::Memory::EEPROM eeprom;
System::Memory::RAM ram;
System::Addons::EEPartition partition;

const unsigned char pinout[9] = {16, 8, 9, 10, 11, 12, 13, 14, 15};
System::Addons::ExternalIO PORT(pinout);

int main(void)
{
  Clock.Begin();

  DDRD = 0xFF;

  PORT.WriteSRAM(57, 0);

  PORT.ReadSRAM(0);

  while (1)
  {
  }
  return 0;
}

void printMemoryMap(unsigned char *memMap, unsigned int row)
{
  unsigned int base = 15; // 15 -> for hexadecimal, 10 -> for decimal, 0 for char
  for (unsigned int i = 0; i < eeprom.Size(); i++)
  {
    if (!(i % row))
      Serial << endl;

    if (base == 15)
    {
      if (memMap[i] > 15)
        Serial << "0x" << String((unsigned char)memMap[i], HEX) << ' ';
      else
        Serial << "0x0" << String((unsigned char)memMap[i], HEX) << ' ';
    }
    else if (base == 10)
    {
      if (memMap[i] < 10)
        Serial << "00" << String(memMap[i]) << ' ';
      else if (memMap[i] < 100 && memMap[i] > 9)
        Serial << "0" << String(memMap[i]) << ' ';
      else
        Serial << String(memMap[i]) << ' ';
    }
    else if (!base)
      Serial << (char)memMap[i];
  }
}