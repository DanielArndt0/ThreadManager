#include "SystemMacros.h"
#include "SystemEnums.h"
#include "SystemInterrupt.h"
#include "SystemErrors.h"
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
   - Desenvolver biblioteca String;

   Afazeres:
   - Alterar função std_thread para retorno de erros;
   - Analisar otimização do sistema de erros usando strings(malloc);
   - Desalocar memória da stackThread;
   - Desenvolver Estrutura de dados
   - Desenvolver StackBuffer Serial;
   - Desenvolver Sistema de erros com stack trace;
   - Desenvolver Funções básicas de I2C;
   - Desenvolver Funções de PWM;
   - Desenvolver programação por interrupções de hardware;
*/

#define LED 0x04
#define BUTTON 0x06

System::UART &operator<<(System::UART &uart, SystemErrors::Error &er);
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

  //Manager.xCreateThread(vTask1, "CtrlLeds", 1);

  vTask1();

  while(1)
  {

  }

  return 0;
}

void vTask1()
{
  REGERR(er);
  Serial << er << endl;
  Hardware.pinWrite(LED, !(Hardware.pinRead(BUTTON)));
}




System::UART &operator<<(System::UART &uart, SystemErrors::Error &er)
{
  uart << "Function name: " << er.getFunction() << endl;
  uart << "File path: " << er.getFilePath() << endl;
  uart << "Line: " << er.getLine() << endl;
  uart << "Date: " << er.getDate() << " - " << er.getTime() << endl;
  return uart;
}