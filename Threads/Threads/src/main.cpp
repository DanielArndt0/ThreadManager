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
    - Otimizado funções da EEPROM;

   Afazeres:
    Sistema:
     - Organizar software no geral;
     - Desenvolver gerenciador de memória;
     - Desenvolver programação por eventos de hardware;
     - Desenvolver Sistema de erros com stack trace;
     - Remodelar classe de Threads (construtor e funções);

    EEPROM:
     - Adicionar funções para escrita de dados primitivos maiores de 1 byte;

    Tipos:
     - Desenvolver função Swap.
     - Desenvolver tipo Tuple;
     - Desenvolver tipo de dado Array;
     - Desenvolver tipo de dado List;
     - Desenvolver tipo de dado Map;
     - Desenvolver tipo de dado Bitset;
     - Desenvolver tipo Typeof;

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

void printMemoryMap(char *memMap, unsigned row);
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

int main(void)
{
  Serial.Begin(9600);

  while (1);
  return 0;
}

void printMemoryMap(char *memMap, unsigned int row)
{
  for (unsigned int i = 0; i < Memory.Size(); i++)
  {
    if (!(i % row))
      Serial << endl;
    Serial << memMap[i] << " ";
  }
}
