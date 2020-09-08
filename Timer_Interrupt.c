//------------------------------------------------------------------------------
//
//   This file contains the timer interrupts
//
//
//  Charles Zhu
//  02/2020
//  Built with IAR Embedded Workbench Version: 7.12.4
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include "Macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

//unsigned int IOT_RESET_FLAG = OFF;
unsigned int IOT_RESETING_INDICATOR = OFF;
volatile unsigned int Secs_Timer = OFF;
extern volatile unsigned char update_display;
extern volatile unsigned int Time_Sequence = OFF;


#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------
//...... Add What you need happen in the interrupt ......
TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
Time_Sequence++;
if((Time_Sequence % EVENT_TWENTY) == OFF){
	update_display = YES;
	Secs_Timer++;
	IOT_RESETING_INDICATOR = ON;
}
//----------------------------------------------------------------------------
}
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
// ----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
// ----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,FOURTEENTH)){
case EVENT_ZEROTH: break; // No interrupt
case EVENT_SECOND: // CCR1 unused
TB1CCR1 += TB0CCR1_INTERVAL; // offset
break;
case EVENT_FOURTH:
TB1CCR2 += TB0CCR2_INTERVAL; // Offset
break;
case EVENT_FOURTEENTH:
break;
default: break;
}
// ----------------------------------------------------------------------------
}