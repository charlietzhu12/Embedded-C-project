//------------------------------------------------------------------------------
//
//  Description: This file initialze the adc
//
//
//  Charles Zhu
//  02/2020
//  Built with IAR Embedded Workbench Version: 7.12.4
//------------------------------------------------------------------------------

#include "Macros.h"
#include "msp430.h"
#include <string.h>
#include "functions.h"

// static volatile unsigned int ADC_Thumb;
// static volatile unsigned int ADC_detect_L;
// static volatile unsigned int ADC_detect_R;
volatile unsigned char adc_char[FOURTH];
//extern char display_line[FOUR_LINES][TEN_CHARS];
extern volatile unsigned char display_changed;


void Init_ADC(void){
//------------------------------------------------------------------------------
// V_DETECT_L (0x04) // Pin 2 A2
// V_DETECT_R (0x08) // Pin 3 A3
// V_THUMB (0x20) // Pin 5 A5
//------------------------------------------------------------------------------
// ADCCTL0 Register
 ADCCTL0 = OFF; // Reset
 ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
 ADCCTL0 |= ADCMSC; // MSC
 ADCCTL0 |= ADCON; // ADC ON
// ADCCTL1 Register
 ADCCTL1 = OFF; // Reset
 ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
 ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
 ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
 ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
 ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
 ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
// ADCCTL1 & ADCBUSY identifies a conversion is in process
// ADCCTL2 Register
 ADCCTL2 = OFF; // Reset
 ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
 ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
 ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
 ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
// ADCMCTL0 Register
 ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
 ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
 ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
 ADCCTL0 |= ADCENC; // ADC enable conversion.
 ADCCTL0 |= ADCSC; // ADC start conversion.
}

// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor

// ------------------------------------------------------------------------------
void HEXtoBCD(int hex_value){
	int added_value;
	adc_char[EVENT_ZEROTH] =      '0';
	adc_char[EVENT_FIRST] =       '0';
	adc_char[EVENT_SECOND] =      '0';
	adc_char[EVENT_THIRD] =       '0';
	added_value = ZERO;
	while (hex_value >=  Thousands){
		hex_value = hex_value - Thousands;
		added_value = added_value + Ones;
		adc_char[ZERO] = ADC_Addition + added_value;
	}
	added_value = ZERO;
	while (hex_value >= Hundreds){
		hex_value = hex_value - Hundreds;
		added_value = added_value + Ones;
		adc_char[EVENT_FIRST] = ADC_Addition + added_value;
	}
	added_value = ZERO;
	while (hex_value >= Tens){
		hex_value = hex_value - Tens;
		added_value = added_value + Ones;
		adc_char[EVENT_SECOND] = ADC_Addition + added_value;
	}
	adc_char[EVENT_THIRD] = ADC_Addition + hex_value;
}
