//------------------------------------------------------------------------------
//
//  Description: This file initializes the interrupts for the ADC
//
//
//  Charles Zhu
//  02/2020
//  Built with IAR Embedded Workbench Version: 7.12.4
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "Macros.h"

volatile unsigned int ADC_Channel;
volatile unsigned int ADC_Right_Detect;
volatile unsigned int ADC_Left_Detect;
volatile unsigned int ADC_Thumb_Detect;


#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
	switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
	case ADCIV_NONE:
	break;
	case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
	//before its previous conversion result was read.
	break;
	case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
	break;
	case ADCIV_ADCHIIFG: // Window comparator interrupt flags
	break;
	case ADCIV_ADCLOIFG: // Window comparator interrupt flag
	break;
	case ADCIV_ADCINIFG: // Window comparator interrupt flag
	break;
	case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
	ADCCTL0 &= ~ADCENC; // Disable ENC bit.
	switch (ADC_Channel++){
	case EVENT_ZEROTH: // Channel A2 Interrupt
		ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
		ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
		ADC_Left_Detect = ADCMEM0; // Move result into Global
		ADC_Left_Detect = ADC_Left_Detect >> Twice; // Divide the result by 4
//		HEXtoBCD(ADC_Left_Detect); // Convert result to String
//		adc_line4(0); // Place String in Display
	break;
	case EVENT_FIRST:
	//Replicate for each channel being read
		ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A2
		ADCMCTL0 |= ADCINCH_5; // Enable Next channel A3
		ADC_Right_Detect = ADCMEM0; // Move result into Global
		ADC_Right_Detect = ADC_Right_Detect >> Twice; // Divide the result by 4
//		HEXtoBCD(ADC_Right_Detect); // Convert result to String
//		adc_line4(0); // Place String in Display
	break;
	case EVENT_SECOND:
		ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A3
		ADCMCTL0 |= ADCINCH_2; // Enable Next channel A5
		ADC_Thumb_Detect = ADCMEM0; // Move result into Global
		ADC_Thumb_Detect = ADC_Thumb_Detect >> Twice; // Divide the result by 4
//		HEXtoBCD(ADC_Thumb_Detect); // Convert result to String
//		adc_line4(0); // Place String in Display
	ADC_Channel=OFF;
	break;
	default:
	break;
	}
	ADCCTL0 |= ADCENC; 
	ADCCTL0 |= ADCSC; // Start next sample
	break;
	default:
	break;
	}
}
