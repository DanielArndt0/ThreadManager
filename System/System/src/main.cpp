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
     - Desalocar memoria quando o display for desligado;

*/

using namespace System;
using namespace Memory;
using namespace Data;

#define HEIGHT 64
#define WIDTH 128
#define __DSP_ADDR 0x78

#define LED 13

void task0();
void task1();
void task2();
void task3();
void task4();
void task5();

System::Managers::ThreadManager Manager;
System::Com::UART Serial;
System::Com::TWI I2C;
System::GPIO Hardware;
System::Time Clock;
System::Memory::EEPROM eeprom;
System::Memory::RAM ram;
System::Addons::OLED Display(WIDTH, HEIGHT, __DSP_ADDR);

unsigned char DC = 0x00;

int main(void)
{
  Hardware.pinConfig(LED, OUTPUT);
  Clock.Begin();
  Serial.Begin(9600);
  I2C.Begin(10E4);
  Manager.Begin();

  if (!Display.Begin())
    Serial << "Erro ao inicializar display" << endl;
  Display.Off();

  if (!Manager.Create(task0, "Monitor", 5000))
    Serial << "Erro ao criar task Monitor" << endl;

  if (!Manager.Create(task1, "LED", 2000))
    Serial << "Erro ao criar task LED" << endl;

  if (!Manager.Create(task2, "ReadPin", 2000))
    Serial << "Erro ao criar task ReadPIN" << endl;

  if (!Manager.Create(task3, "RAM", 6000))
    Serial << "Erro ao criar task RAM" << endl;

  if (!Manager.Create(task4, "AnalogRead", 500))
    Serial << "Erro ao criar task AnalogRead" << endl;

  if (!Manager.Create(task5, "DutyCicle", 3000))
    Serial << "Erro ao criar task DutyCicle" << endl;

  Clock.Pause(6500);
  Display.On();

  unsigned char moveAverage = 0x00;
  while (1)
  {
    moveAverage = 0x00;
    for (unsigned int i = 0; i < 10; i++)
      moveAverage += Clock.Ticks() - moveAverage;
    DC = moveAverage / 10;
  }

  return 0;
}

void task0()
{
  Serial << endl;
  for (unsigned int i = 0x00; i < Manager.getTotalThreads(); i++)
    Serial << "Task " << i << ": " << Manager.getName(i) << endl;
}

void task1()
{
  Hardware.pinWrite(LED, !Hardware.pinRead(LED));
}

void task2()
{
  Display.writeString(String("LED: ") += String(Hardware.pinRead(LED) ? "On " : "Off"), 0, 0, WHITE);
}

void task3()
{
  Display.writeString(String("RAM: ") += String(ram.freeRAM()) += String(" Bytes."), 0, 16, WHITE);
}

void task4()
{
  Display.writeString(String("Pin 14: ") += String(Hardware.analogReadVolts(0)) += String('V'), 0, 32, WHITE);
}

void task5()
{
  Display.writeString(String("Execution: ") += String(DC) += String(DC > 99 ? "ms" : "ms "), 0, 48, WHITE);
}