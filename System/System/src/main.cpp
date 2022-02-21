#include "Macros/SystemMacros.h"
#include "CoadjutorSystem/CoadjutorInterrupt.h"
#include "Errors/SystemErrors.h"
#include "Managers/ThreadManager.h"
#include "Time/SystemTime.h"
#include "Com/SystemUART.h"
#include "Memory/SystemEEPROM.h"
#include "Peripherals/SystemPeriphreals.h"
#include "DataTypes/SystemTypes.h"

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
     - Adicionar mais funções para configurar TIMERs;

*/
using namespace System;
using namespace Data;

// EEPROM Features.
#define Atual (i)
#define Nome(ptr) mem[ptr]
#define Tamanho(ptr) mem[ptr + 1]
#define Verificador(ptr) mem[ptr + mem[ptr + 1] + 2]
#define nomeUltimo(ptr) mem[ptr + mem[ptr + 1] + 3]

bool isPartition(unsigned int pos);
void partition(unsigned char name, unsigned int pos1, unsigned int pos2);
void readPartition();
void printMemoryMap(unsigned char *memMap, unsigned row);
// End EEPROM Features.

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

System::ThreadManager Manager;
System::UART Serial;
System::GPIO Hardware;
System::EEPROM Memory;
System::Time Clock;

unsigned char uintToUchar(unsigned int c) { return c; }

int main(void)
{
  Serial.Begin(9600);

  Memory.Write(41243241, 5);

  Serial << Memory.ReadULong(5) << endl;

  Serial << endl;
  Serial << endl;
  Serial << endl;
  //printMemoryMap(Memory.Array(), 32);

  while (1);
  return 0;
}

bool isPartition(unsigned int pos)
{
}

void partition(unsigned char name, unsigned int pos1, unsigned int pos2)
{
  if (!name && pos1 >= pos2)
    return;

  unsigned int _diff_ = pos2 - pos1;
  unsigned int _check_digit_ = name + _diff_;
  bool _is_upper_ = _diff_ > 255 || _check_digit_ > 255;
  if (_is_upper_)
  {
    Memory.Write(name, pos1 - 3);
    Memory.Write(0xFF, pos1 - 2);
    Memory.Write(uintToUchar(_diff_), pos1 - 1);

    Memory.Write(uintToUchar(_check_digit_), pos2);
    Memory.Write(0xFF, pos2 + 1);
    Memory.Write(name, pos2 + 2);
  }
  else
  {
    Memory.Write(name, pos1 - 2);
    Memory.Write(_diff_, pos1 - 1);
    Memory.Write(_check_digit_, pos2);
    Memory.Write(name, pos2 + 1);
  }

  for (unsigned int i = pos1; i < pos2; i++)
    Memory.Write((unsigned char)0x00, i);
}

void printMemoryMap(unsigned char *memMap, unsigned int row)
{
  unsigned int base = 15; // 15 -> for hexadecimal
  for (unsigned int i = 0; i < Memory.Size(); i++)
  {
    if (!(i % row))
      Serial << endl;
    if (memMap[i] > base)
      Serial << "0x" << String((unsigned char)memMap[i], HEX) << ' ';
    else
      Serial << "0x0" << String((unsigned char)memMap[i], HEX) << ' ';
  }
}
