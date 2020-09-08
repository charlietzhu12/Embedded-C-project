//------------------------------------------------------------------------------
//
//  Description: this file contains the interrupt service routine for the 
// switches. 
//
//
//  @author Charles Zhu
//
//  Created: Jan 2020
//  Updated: April 2020
//  Built with IAR Embedded Workbench Version: (7.12.4)
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*
#include  "Macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>

volatile unsigned char Switches_Event;
int Switch_pressed;

volatile unsigned int i;


#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
  // Switch 1
  if (P4IFG & SW1) {
  
    TB0CCTL1 |= CCIE; // CCR1 Enable Interrupt
    TB0CCTL0 &= ~CCIE; // CCR0 Disable Interrupt
    Switches_Event = ALWAYS; // set variable that switch is pressed.
    
    switch (Switch_pressed){
      case 0: 
        SetUpPortNum = ON;
        is_the_index_new = OFF;
        UCA0IE |= UCTXIE;
        //Switch_pressed = ALWAYS;
        
           break;      
        default:break;
    }
  }
  else {}
  P4IE &= ~SW1; // Disable interrupt

  }


#pragma vector = PORT2_VECTOR
__interrupt void switchP2_interrupt(void){ // SW2 interrupt
  if(P2IFG & SW2) {
    P2IFG &= ~SW2; // IFG SW1 Cleared
    TB0CCTL1 |= CCIE; // CCR1 Enable Interrupt
    TB0CCTL0 &= ~CCIE; // CCR0 Disable Interrupt
     //i = RESET_STATE;
    // Switches_Event = ALWAYS; // set variable that switch is pressed.
     
     P2IE &= ~SW2; // Disable interrupt
    // set variable to identify debouncing is occurring
  }
}
*/

