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

/*
   Sistema:
   - Desenvolvido sistema de Threads;
   - Desenvolvido ThreadManager;
   - StackThread automatizado;
   - Configurações de Sistema adicionadas;

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
     - Remodelar classe de Threads (construtor e funções);


    Tipos:
     - Desenvolver tipo Tuple;
     - Desenvolver tipo de dado Array;
     - Desenvolver tipo de dado List;
     - Desenvolver tipo de dado Map;
     - Desenvolver tipo de dado Bitset;
     - Desenvolver tipo Typeof;

    EEPROM:
     - Otimizar sistema de Get partições;
     - Desenvolver sistema de partições;

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
System::Addon::EEPartition partition;

int main(void)
{
  Serial.Begin(9600);
  Clock.Begin();
  Manager.Begin();

  Manager.Create(vTask0, "Daniel", 500);
  Manager.Create(vTask1, "Daniel", 1000);
  Manager.Create(vTask2, "Daniel", 1500);
  Manager.Create(vTask3, "Daniel", 2000);
  Manager.Create(vTask4, "Daniel", 2500);
  Manager.Create(vTask5, "Daniel", 3000);
  Manager.Create(vTask6, "Daniel", 3500);
  Manager.Create(vTask7, "Daniel", 4000);
  Manager.Create(vTask8, "Daniel", 4500);
  Manager.Create(vTask9, "Daniel", 5000);
  while (1);
  return 0;
}

void vTask0() { Serial << "Task 0" << endl; }

void vTask1() { Serial << "Task 1" << endl; }

void vTask2() { Serial << "Task 2" << endl; }

void vTask3() { Serial << "Task 3" << endl; }

void vTask4() { Serial << "Task 4" << endl; }

void vTask5() { Serial << "Task 5" << endl; }

void vTask6() { Serial << "Task 6" << endl; }

void vTask7() { Serial << "Task 7" << endl; }

void vTask8() { Serial << "Task 8" << endl; }

void vTask9() { Serial << "Task 9" << endl; }

/*
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
}*/