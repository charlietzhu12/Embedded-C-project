//------------------------------------------------------------------------------
//
//  Description: This file contains the serial interrupts
//
//
//  @author Charles Zhu
//
//  Created: Jan 2020
//  Updated: April 2020
//  Built with IAR Embedded Workbench Version: (7.12.4)
//-----------------------------------------------------------------------------


#include "Macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

//extern volatile unsigned int movement_progress;

//extern volatile unsigned int Time_Sequence = OFF;

extern volatile unsigned int interrupt_count;
extern volatile unsigned char display_changed;
extern char display_line[EVENT_FOURTH][EVENT_TENTH];

//volatile unsigned int Secs_Timer = OFF;

extern unsigned int usb_rx_ring_wr;

extern char USB_Char_Rx[SMALL_RING_SIZE];

extern char IOT_Char_Rx[LARGE_RING_SIZE];

extern unsigned int IOT_rx_ring_wr;

volatile unsigned int UCA0_index;

volatile unsigned int UCA1_index;

//char test_command[SMALL_RING_SIZE] = "$ NCSU  #1234 ";

// char test_command[SMALL_RING_SIZE];
// strcpy(test_command, "$NCSU  #1  ");

volatile unsigned int x = OFF;
extern volatile unsigned int transmission_state;

extern volatile unsigned int Serial_event_1;
extern volatile unsigned int Serial_event_0;

char temp_2;
char temp_3;
//unsigned int IOT_RESET_FLAG = OFF;
unsigned int SetUpPortNum = OFF;
unsigned int SetUpSSID = OFF;
unsigned int is_the_index_new = OFF;
//unsigned int rollingindex_1 = OFF;
// unsigned char portarray[SMALL_RING_SIZE] = "AT+NSTCP=1919,1";
// unsigned char NSTATarray[11] = "AT+NSTAT=?";





#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
unsigned int temp;

switch(__even_in_range(UCA0IV,Transmission_interrupt_num)){
case ZEROTH: break;// Vector 0 - no interrupt

case SECOND: // Vector 2 - RXIFG
temp = IOT_rx_ring_wr++;
IOT_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
if (IOT_rx_ring_wr >= (sizeof(IOT_Char_Rx))){
IOT_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
}

if (IOT_Char_Rx[temp] == '\n') {
	Serial_event_0 = ON;
}
temp_3 = IOT_Char_Rx[temp];
UCA1TXBUF = temp_3;
//ReadSSIDandIP(temp);


break;

case FOURTH: // Vector 4 – TXIFG

break;
}
}

#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
unsigned int temp;
switch(__even_in_range(UCA1IV,Transmission_interrupt_num)){
case ZEROTH: // Vector 0 - no interrupt
break;
case SECOND: // Vector 2 - RXIFG
temp = usb_rx_ring_wr++;

USB_Char_Rx[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character

if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
}
if (USB_Char_Rx[temp] == '\n') {
	Serial_event_1 = ON;
}



	temp_2 = USB_Char_Rx[temp];
          
            
	UCA0TXBUF = temp_2;
        
break;

case FOURTH: // Vector 4 – TXIFG

break;
}
}



