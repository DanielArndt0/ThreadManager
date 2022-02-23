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
     - Desenvolver tipo Temporary;

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
#define Tamanho2(ptr) mem[ptr + 2]
#define nomeUltimo mem[(i + 3) + (len + 2)]

#define name_addr 0x03
#define len_1 0x02
#define len_2 0x01

void partition(unsigned char name, unsigned int pos1, unsigned int pos2);
void readPartition();
void printMemoryMap(unsigned char *memMap, unsigned row);
bool isPartition(unsigned int pos);
bool isPontaInicial(unsigned int pos);
bool isPontaFinal(unsigned int pos);
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

int main(void)
{
  Serial.Begin(9600);

 //partition('E');
  readPartition();
  Memory.Empty();
  Memory.Used();

  while (1);
  return 0;
}

/*
    Criação de uma partição:
    - O Nome de uma partição é um caractere que não pode ser nulo.
    - O endereço 1 não pode ser maior ou igual que o endereço 2.
    - Ponta inicial (Inicio da partição) -> bloco 3 bytes antes do valor passado ao endereço 1.
      - Byte 1 -> Nome da partição.
      - Byte 2 -> Endereço de tamanho partição 1.
      - Byte 3 -> Endereço de tamanho partição 2.
    - Ponta final (Fim da partição) -> bloco 3 bytes depois do valor passado ao endereço 2.
      - Byte 1 -> Endereço de verificação 1.
      - Byte 2 -> Endereço de verificação 2.
      - Byte 3 -> Nome da partição.
    - O Nome será alocado na ponta inicial.
    - A diferença entre o endereço 1 e o endereço 2 é o Tamanho disponível na partição.
    - O tamanho é alocado na ponta inicial.
    - O valor do tamanho será dividido em 2 bytes e alocados respectivamente após a alocação do Nome.
    - O endereço de verificação ficará alocado na ponta final da partição.
    - O valor no endereço de verificação é a soma entre o Tamanho e o Nome.
    - Por fim, o Nome é alocado novamente na ponta final. Sendo o último byte.

    Verificação de ponta inicial à ponta final (inicio ao fim da partição):
    - O inicio da partição SEMPRE começa 3 bytes antes do endereço passado como parâmetro. Tendo assim um offset de 3 bytes.
    - Valor do Offset: 3;
    - Acesso ao endereço do Nome: mem[i];
    - Acesso ao endereço 1 do Tamanho: mem[Nome + 1];
    - Acesso ao endereço 2 do Tamanho: mem[Nome + 2];
    - A concatenação dos valores nos endereços dos tamanhos, retornarão um inteiro com o TamanhoReal.
    - Acesso ao endereço 1 do byte de verificação: mem[(Nome + Offset) + TamanhoReal];
    - Acesso ao endereço 2 do byte de verificação: mem[(Nome + Offset) + (TamanhoReal + 1)];
    - A concatenação dos valores nos endereços dos bytes de verificação, retornarão um inteiro
    com o VerificadorReal.
    - Acesso ao endereço do Nome final: mem[(Nome + Offset) + (TamanhoReal + 2)];
    - O final da partição SEMPRE termina 3 bytes depois do TamanhoReal da da partição;
    - A primeira etapa verifica se a soma entre o Nome e o TamanhoReal correspondem com o valor
    do VerificadorReal.
    - A segunda etapa se o Nome encontrado no final da partição corresponde com o nome no início da partição.

    Verificação de ponta final à ponta inicial(fim ao inicio da partição)
    - Acesso ao endereço 1 do byte de verificação: mem[pos];
    - Acesso ao endereço 2 do byte de verificação: mem[pos + 1];
    - Acesso ao endereço do Nome final: mem[pos + 2];
    - Acesso ao endereço do Nome inicial: mem[((VerificadorReal - Nome) - i) - 3]
    - Acesso ao endereço 1 do Tamanho: mem[((VerificadorReal - Nome) - i) - 2]
    - Acesso ao endereço 2 do Tamanho: mem[((VerificadorReal - Nome) - i) - 1]
    - A concatenação dos valores nos endereços dos bytes de verificação, retornarão um inteiro
    com o VerificadorReal.
    - A concatenação dos valores nos endereços dos tamanhos, retornarão um inteiro com o TamanhoReal.
    - A primeira etapa verifica se a diferença entre o VerificadorReal e o Nome final correspondem com o valor
    do TamanhoReal.
    - A segunda etapa se o Nome encontrado no final da partição corresponde com o nome no início da partição.
  */

bool isPartition(unsigned int pos) { return isPontaInicial(pos) || isPontaFinal(pos) ? true : false; }

bool isPontaInicial(unsigned int pos)
{
  unsigned int offset_ = 3;
  unsigned int part_pos_ = pos - offset_;
  unsigned char *mem = Memory.Array();

  bool firstCheck = 0x00;  // Verifica se o tamanho mais o nome é igual o digito verificador
  bool secondCheck = 0x00; // Verifica se o nome do inicio da partição é o mesmo nome após o digito verificador

  unsigned int size = 0x00;    // Usado para concatenar dois endereços do tamanho
  unsigned int checker = 0x00; // Usado para concatenar dois endereços do digito verificador

  if (mem[part_pos_] && mem[part_pos_ + 1] && mem[part_pos_ + 2])
  {
    size = mem[part_pos_ + 1] | mem[part_pos_ + 2] << 8;
    checker = mem[(part_pos_ + offset_) + size] | mem[(part_pos_ + offset_) + (size + 1)] << 8;
    firstCheck = (mem[part_pos_] + size) == checker;
    secondCheck = mem[part_pos_] == mem[(part_pos_ + offset_) + (size + 2)];
    if (firstCheck && secondCheck)
    {
      Serial << "Endereço: " << part_pos_ << " | Nome: '" << (char)mem[part_pos_] << ":' | Digito verificador: " << checker << " | Tamanho: " << size << " bytes."
             << " | Inicio: " << (part_pos_ + offset_) << " | Fim: " << (part_pos_ + offset_) + size << endl;
      return true;
    }
  }
  Serial << "Nenhuma partição encontrada." << endl;
  return false;
}

bool isPontaFinal(unsigned int pos)
{
  unsigned char *mem = Memory.Array();

  bool firstCheck = 0x00;  // Verifica se o tamanho mais o nome é igual o digito verificador
  bool secondCheck = 0x00; // Verifica se o nome do inicio da partição é o mesmo nome após o digito verificador

  unsigned int size = 0x00;    // Usado para concatenar dois endereços do tamanho
  unsigned int checker = 0x00; // Usado para concatenar dois endereços do digito verificador

  if (mem[pos] && mem[pos + 1] && mem[pos + 2])
  {
    checker = mem[pos] | mem[pos + 1] << 8;
    size = mem[(pos - (checker - mem[pos + 2])) - 2] | mem[(pos - (checker - mem[pos + 2])) - 1] << 8;
    firstCheck = (checker - mem[pos + 2]) == size;
    secondCheck = mem[pos + 2] == mem[(pos - size) - 3];
    if (firstCheck && secondCheck)
    {
      Serial << "Ponta final encontrada: '" << (char)mem[pos + 2] << ":' | Tamanho: " << size << " bytes." << endl;
      return true;
    }
  }
  Serial << "Nenhuma ponta final encontrada." << endl;
  return false;
}

void readPartition()
{
  unsigned char *mem = Memory.Array();

  unsigned int part = 0x00; // Conta número de partições encontradas
  unsigned int cand = 0x00; // Conta número de candidatos à partições

  bool firstCheck = 0x00;  // Verifica se o tamanho mais o nome é igual o digito verificador
  bool secondCheck = 0x00; // Verifica se o nome do inicio da partição é o mesmo nome após o digito verificador

  unsigned int size = 0x00;    // Usado para concatenar dois endereços do tamanho
  unsigned int checker = 0x00; // Usado para concatenar dois endereços do digito verificador

  for (unsigned int i = 0x00; i < Memory.Size(); i++)
  {
    if (mem[i] != 0x00 && mem[(i) + 1] != 0x00 && mem[(i) + 1])
    {
      cand++;
      size = mem[i + 1] | mem[i + 2] << 8;
      checker = mem[(i + 3) + size] | mem[(i + 3) + (size + 1)] << 8;
      firstCheck = (mem[i] + size) == checker;
      secondCheck = mem[i] == mem[(i + 3) + (size + 2)];
      if (firstCheck && secondCheck)
      {
        Serial << "Endereço: " << i << " | Nome: '" << (char)Nome(Atual) << ":' | Digito verificador: " << checker << " | Tamanho: " << size << " bytes."
               << " | Inicio: " << (i + 3) << " | Fim: " << (i + 3) + size << endl;
        part++;
      }
    }
  }
  Memory.FreeArray();
  Serial << endl
         << "Partições encontradas: " << part << " de " << cand << " candidatos." << endl;
}

void partition(unsigned char name, unsigned int pos1, unsigned int pos2)
{
  if (!name && pos1 >= pos2 && pos1 < 2)
    return;
  unsigned int _diff_ = pos2 - pos1;
  unsigned int _check_digit_ = name + _diff_;
  Memory.Write(name, pos1 - 3);
  Memory.Write(_diff_, pos1 - 2);
  Memory.Write(_check_digit_, pos2);
  Memory.Write(name, pos2 + 2);
  for (unsigned int i = pos1; i < pos2; i++)
    Memory.Write((unsigned char)0x00, i);
}

void printMemoryMap(unsigned char *memMap, unsigned int row)
{
  unsigned int base = 15; // 15 -> for hexadecimal, 10 -> for decimal, 0 for char
  for (unsigned int i = 0; i < Memory.Size(); i++)
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
