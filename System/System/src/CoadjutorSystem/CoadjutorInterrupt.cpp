#include "CoadjutorSystem/CoadjutorInterrupt.h"

CoadjutorSystem::Timer0 System::Settings::Interrupts::__timer_0__;
CoadjutorSystem::Timer1 System::Settings::Interrupts::__timer_1__;

ISR(TIMER0_OVF_vect) { System::Managers::ThreadManager::Manager(); }

unsigned long __system_tick_counter__ = 0x00;
ISR(TIMER1_OVF_vect)
{
  __system_tick_counter__++;
  System::Settings::Interrupts::TIMER1()->Reset();
}

CoadjutorSystem::Timer0 *System::Settings::Interrupts::TIMER0() { return &__timer_0__; }

CoadjutorSystem::Timer1 *System::Settings::Interrupts::TIMER1() { return &__timer_1__; }
