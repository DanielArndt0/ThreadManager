#include "SystemMacros.h"
#include "SystemInterrupt.h"
#include "SystemErrors.h"
#include "SystemThreadManager.h"
#include "SystemTime.h"
#include "SystemUART.h"
#include "SystemEEPROM.h"
#include "SystemPeriphreals.h"
#include "SystemTypes.h"

/*
   Feitos:
   - Desenvolver Threads;
   - Desenvolver ThreadManager;
   - Desenvolver Funções básicas de Tempo;
   - Desenvolver Funções básicas de Comunicação serial;
   - Desenvolver Funções básicas de EEPROM;
   - Desenvolver Funções de Leitura analógica;
   - Adicionar Configurações de Sistema;
   - Automatizar StackThread;
   - Desenvolver tipo de dado String;
   - Desenvolver tipo de dado Vector;

   Em desenvolvimento:
   - Adicionar mais funções para configurar TIMER0;

   Afazeres:
   - Desenvolver StackBuffer Serial;
   - Desenvolver Sistema de erros com stack trace
   - Desenvolver Funções básicas de I2C;
   - Desenvolver Funções de PWM;
   - Desenvolver programação por eventos de hardware;
*/

#define LED 0x04
#define BUTTON 0x06

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

using namespace System;

System::ThreadManager Manager;
System::UART Serial;
System::GPIO Hardware;
System::EEPROM EEprom;
System::Time Clock;

int main(void)
{
  Serial.Begin(9600);
  Clock.Begin();

  vTask1();

  while (1)
  {
  }

  return 0;
}

void vTask1()
{
  System::Data::Vector<subSystem::Thread> vetor;
}