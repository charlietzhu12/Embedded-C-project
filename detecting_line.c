//  This is where the car detects line with the 2 emitters and ir emitter
//
//
//  @author Charles Zhu
//
//  Created: Jan 2020
//  Updated: April 2020
//  Built with IAR Embedded Workbench Version: (7.12.4)
//------------------------------------------------------------------------------
#include "Macros.h"
#include "msp430.h"
#include <string.h>
#include "functions.h"





extern char display_line[FOURTH][ELEVENTH];

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int ADC_Thumb_Detect;

extern volatile unsigned char adc_char[EVENT_FOURTH];


extern volatile unsigned int Time_Sequence;



void Detecting_the_line(void){ 
  {
  if (Time_Sequence > 30) {
    
      RIGHT_FORWARD_SPEED = 5000;
      LEFT_FORWARD_SPEED = 5000;
      RIGHT_REVERSE_SPEED = no_wheels_go;
      LEFT_REVERSE_SPEED = no_wheels_go;
      
      if((ADC_Left_Detect >= 650) || (ADC_Right_Detect >= 650)){
           
        RIGHT_FORWARD_SPEED = no_wheels_go;
        LEFT_FORWARD_SPEED = no_wheels_go;
        RIGHT_REVERSE_SPEED = no_wheels_go;
        LEFT_REVERSE_SPEED = no_wheels_go;
        Time_Sequence = RESET_STATE;
        
      }
      }

      
      
      if (Time_Sequence > 70) {
      RIGHT_FORWARD_SPEED = no_wheels_go;
      LEFT_FORWARD_SPEED = no_wheels_go;
      RIGHT_REVERSE_SPEED = no_wheels_go;
      LEFT_REVERSE_SPEED = no_wheels_go;
        } 
      
     // break;
      
     // case 4:
  if((ADC_Left_Detect <= 650) && (ADC_Right_Detect >= 400)) {
        
      RIGHT_FORWARD_SPEED = no_wheels_go;
      LEFT_FORWARD_SPEED = 1000;
      RIGHT_REVERSE_SPEED = no_wheels_go;
      LEFT_REVERSE_SPEED = no_wheels_go;
      //break;
  }
    //case 5:
      if((ADC_Left_Detect >= 650) && (ADC_Right_Detect <= 400))
      RIGHT_FORWARD_SPEED = 1000;
      LEFT_FORWARD_SPEED = no_wheels_go;
      RIGHT_REVERSE_SPEED = no_wheels_go;
      LEFT_REVERSE_SPEED = no_wheels_go;
      
    
      if ((ADC_Left_Detect >= 650) && (ADC_Right_Detect >= 650))
      RIGHT_FORWARD_SPEED = 2000;
      LEFT_FORWARD_SPEED = 2000;
      RIGHT_REVERSE_SPEED = no_wheels_go;
      LEFT_REVERSE_SPEED = no_wheels_go;
      
 }
}

	
 
void HEXtoBCD_Display(void){
	HEXtoBCD(ADC_Left_Detect);
	display_line[ZERO][ZERO]=adc_char[ZERO];
	display_line[ZEROTH][FIRST]=adc_char[FIRST];
	display_line[ZEROTH][SECOND]=adc_char[SECOND];
	display_line[ZEROTH][THIRD]=adc_char[THIRD];
	display_changed = YES;
	
	HEXtoBCD(ADC_Right_Detect);
	display_line[ZERO][SIXTH]=adc_char[ZERO];
	display_line[ZERO][SEVENTH]=adc_char[FIRST];
	display_line[ZERO][EIGHTH]=adc_char[SECOND];
	display_line[ZERO][NINETH]=adc_char[THIRD];
	display_changed = YES;
	
	HEXtoBCD(ADC_Thumb_Detect);
	display_line[FIRST][THIRD]=adc_char[ZERO];
	display_line[FIRST][FOURTH]=adc_char[FIRST];
	display_line[FIRST][FIFTH]=adc_char[SECOND];
	display_line[FIRST][SIXTH]=adc_char[THIRD];
	display_changed = YES;
	}



