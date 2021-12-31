#include "SystemInterrupt.h"

subSystem::Timer0 System::Settings::Interrupts::__timer_0__;
subSystem::Timer1 System::Settings::Interrupts::__timer_1__;

ISR(TIMER0_OVF_vect) { System::ThreadManager::xManager(); }

unsigned long __system_tick_counter__ = 0x00;
ISR(TIMER1_OVF_vect)
{
  __system_tick_counter__++;
  System::Settings::Interrupts::TIMER1()->Reset();
}

subSystem::Timer0 *System::Settings::Interrupts::TIMER0() { return &__timer_0__; }

subSystem::Timer1 *System::Settings::Interrupts::TIMER1() { return &__timer_1__; }
