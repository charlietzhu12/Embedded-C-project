//------------------------------------------------------------------------------
//
//  Description: This file is the baud for serial communication
//
//
//  Charles Zhu
//  02/2020
//  Built with IAR Embedded Workbench Version: 7.12.4
//------------------------------------------------------------------------------


#include  "Macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>

volatile unsigned char character;
void out_character_UCA0(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
while (!(UCA0IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
UCA0TXBUF = character;
//------------------------------------------------------------------------------
}

void out_character_UCA1(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
while (!(UCA1IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
UCA1TXBUF = character;
//------------------------------------------------------------------------------
}