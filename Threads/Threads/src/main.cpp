#include "SystemMacros.h"
#include "SystemEnums.h"
#include "SystemInterrupt.h"
#include "SystemThreadManager.h"
#include "SystemTime.h"
#include "SystemUART.h"
#include "SystemEEPROM.h"
#include "SystemPeriphreals.h"
#include "SystemString.h"

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

   Afazeres:
   - Desenvolver biblioteca de conversão de dados;
   - Desenvolver StackBuffer Serial;
   - Desenvolver Sistema de erros com stack trace;
   - Desenvolver Funções básicas de I2C;
   - Desenvolver Funções de PWM;
   - Desenvolver programação por interrupções de hardware;
*/

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
using namespace SystemData;

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
  while (1);
  return 0;
}