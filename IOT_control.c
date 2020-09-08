//------------------------------------------------------------------------------
//
//  Description: This file contains instructions to control car via wifi
//
//
//  Charles Zhu
//  04/2020
//  Built with IAR Embedded Workbench Version: 7.12.4
//------------------------------------------------------------------------------


#include "Macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

extern char display_line[EVENT_FOURTH][ELEVENTH];

extern volatile unsigned char display_changed;

unsigned int index_a = OFF;


unsigned int index_b = OFF;

unsigned int index_c = OFF;


char Network_holder[ELEVEN_NUMBERS];

unsigned int readingSSID = OFF;


unsigned int gonext = OFF;

unsigned int command = OFF;

extern char IOT_Char_Rx[LARGE_RING_SIZE];

extern volatile unsigned int Time_Sequence;

unsigned int receiving_command = OFF;

unsigned int looking_for_network = ON;

unsigned int second_command = OFF;

char Command_Line[CommandIsEight];

unsigned int command_range_1st = 0;
unsigned int command_range_2nd = 0;
unsigned int command_range_3rd =0;



unsigned int command_length = OFF;

extern unsigned int happens_one_time;

unsigned int station_num = 10;



extern unsigned int IOT_Course_Driving;




void Read_the_network_name(int index_a){
switch(gonext){
	case EVENT_ZEROTH:
	if(IOT_Char_Rx[index_a] == ' ') gonext = FIRST;
	break;
	
	case EVENT_FIRST:
	if(IOT_Char_Rx[index_a] == 'S') gonext = SECOND;
	else gonext = OFF;
	break;
	
	case EVENT_SECOND:
	if(IOT_Char_Rx[index_a] == 'S') gonext = THIRD;
	else gonext = OFF;
	break;
	
	case EVENT_THIRD:
	if(IOT_Char_Rx[index_a] == 'I') gonext= FOURTH;
	else gonext= OFF;
	break;
	
	case EVENT_FOURTH:
	if(IOT_Char_Rx[index_a] == 'D') gonext= FIFTH;
	else gonext = OFF;
	break;
	
	case EVENT_FIFTH:
	gonext = SIXTH;
	break;
	
	case EVENT_SIXTH:
	gonext = SEVENTH;
	break;
	
	case EVENT_SEVENTH:
	Network_holder[ZERO] = IOT_Char_Rx[index_a];
	gonext = EIGHTH;
	break;
	
	case EVENT_EIGHTH:
	Network_holder[FIRST] = IOT_Char_Rx[index_a];
	gonext = NINETH;
	break;
	
	case EVENT_NINETH:
	Network_holder[SECOND] = IOT_Char_Rx[index_a];
	gonext = TENTH;
	break;
	
	case EVENT_TENTH:
	Network_holder[THIRD] = IOT_Char_Rx[index_a];
	gonext = ELEVENTH;
	break;
	
	case EVENT_ELEVENTH:
	Network_holder[FOURTH] = IOT_Char_Rx[index_a];
	gonext = TWELVETH;
	break;
	
	case EVENT_TWELVETH:
	Network_holder[FIFTH] = IOT_Char_Rx[index_a];
	gonext = THIRTEENTH;
	break;
	
	case EVENT_THIRTEENTH:
	Network_holder[SIXTH] = IOT_Char_Rx[index_a];
	gonext = FOURTEENTH;
	break;
	
	case EVENT_FOURTEENTH:
	Network_holder[SEVENTH] = IOT_Char_Rx[index_a];
	gonext = FIFTEENTH;
	break;
	
	case EVENT_FIFTEENTH:
	Network_holder[EIGHTH] = IOT_Char_Rx[index_a];
	gonext = SIXTEENTH;
	break;
	
	case EVENT_SIXTEENTH:
	Network_holder[NINETH] = IOT_Char_Rx[index_a];
	gonext = SEVENTEENTH;
	break;
	
	case EVENT_SEVENTEENTH:
	

	display_line[ZERO][ZERO] = Network_holder[ZERO];
	display_line[ZERO][FIRST] = Network_holder[FIRST];
	display_line[ZERO][SECOND] = Network_holder[SECOND];
	display_line[ZERO][THIRD] = Network_holder[THIRD];
	display_line[ZERO][FOURTH] = Network_holder[FOURTH];
	display_line[ZERO][FIFTH] = Network_holder[FIFTH];
	display_line[ZERO][SIXTH] = Network_holder[SIXTH];
	display_line[ZERO][SEVENTH] = Network_holder[SEVENTH];
	display_line[ZERO][EIGHTH] = Network_holder[EIGHTH];
	display_line[ZERO][NINETH] = Network_holder[NINETH];
	display_changed = YES;
	gonext = OFF;
//}
	
	
	
	break;
	default:
	break;
	
}	
}


void Show_the_Network(int index_b){
	strcpy(display_line[FIRST], "  192.168  ");
	update_string(display_line[FIRST], FIRST);
	strcpy(display_line[SECOND], "   01.7   ");
	update_string(display_line[SECOND], SECOND);
	enable_display_update();
	display_changed = YES;
}

void readNetwork(void){
	strcpy(display_line[ZERO], "  TPLINK  ");
	update_string(display_line[ZERO], ZERO);
	enable_display_update();
	display_changed = YES;
	looking_for_network = OFF;
}
	
void ReadCommand(int index_c){
	switch(command){
	case EVENT_ZEROTH:
	if(IOT_Char_Rx[index_c] == escKEY) command = FIRST;
	break;
	
	case EVENT_FIRST:
	if(IOT_Char_Rx[index_c] == 'S') command = SECOND;
	else command = OFF;
	break;
	
	case EVENT_SECOND:
	command = THIRD;
	break;
	
	case EVENT_THIRD:
	if(IOT_Char_Rx[index_c] != '^') command = OFF;
	else command = FOURTH;
	break;
	
	case EVENT_FOURTH:
	if(IOT_Char_Rx[index_c] != '1') command = OFF;
	else command = FIFTH;
	break;
	
	case EVENT_FIFTH:
	if(IOT_Char_Rx[index_c] != '2') command = OFF;
	else command = SIXTH;
	break;
	
	case EVENT_SIXTH:
	if(IOT_Char_Rx[index_c] != '3') command = OFF;
	else command = SEVENTH;
	break;
	
	case EVENT_SEVENTH:
	if(IOT_Char_Rx[index_c] != '4') command = OFF;
	else command = EIGHTH;
	break;
	
	case EVENT_EIGHTH:
	Command_Line[ZEROTH] = IOT_Char_Rx[index_c];
	command = NINETH;
	break;
	
	case EVENT_NINETH:
	Command_Line[FIRST] = IOT_Char_Rx[index_c];
	command = TENTH;
	break;
	
	case EVENT_TENTH:
	Command_Line[SECOND] = IOT_Char_Rx[index_c];
	command = ELEVENTH;
	break;
	
	case EVENT_ELEVENTH:
	Command_Line[THIRD] = IOT_Char_Rx[index_c];
	command = TWELVETH;
	
	break;
	
	case EVENT_TWELVETH:
	Command_Line[FOURTH] = IOT_Char_Rx[index_c];
	
		command = THIRTEENTH;
	
	break;
	
	case EVENT_THIRTEENTH:
	Command_Line[FIFTH] = IOT_Char_Rx[index_c];
	command = FOURTEENTH;
	break;
	
	case EVENT_FOURTEENTH:
	Command_Line[SIXTH] = IOT_Char_Rx[index_c];
	command = FIFTEENTH;
	break;
	
	case EVENT_FIFTEENTH:
	Command_Line[SEVENTH] = IOT_Char_Rx[index_c];
	command = SIXTEENTH;
	receiving_command = ON;
	break;
	
	case EVENT_SIXTEENTH:
	Time_Sequence = OFF;
	
        
                LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
	
	

	
	display_line[ZERO][THIRD] = Command_Line[ZERO];
	display_line[ZERO][FOURTH] = Command_Line[FIRST];
	display_line[ZERO][FIFTH] = Command_Line[SECOND];
	display_line[ZERO][SIXTH] = Command_Line[THIRD];
	display_changed = YES;
	
	command_range_1st = Command_Line[FIRST] - FOURTYEIGHT_CONVERSION;
	command_range_1st = command_range_1st * Event_One_Hundred;
	command_range_2nd = Command_Line[SECOND] - FOURTYEIGHT_CONVERSION;
	command_range_2nd = command_range_2nd* TENTH;
	command_range_3rd = Command_Line[THIRD] - FOURTYEIGHT_CONVERSION;
	command_length = command_range_1st + command_range_2nd + command_range_3rd;

	if(Command_Line[ZERO] == 'F'){
		command = going_forwards;
	}
	else if(Command_Line[ZERO] == 'B'){
		command = going_backwards;
	}		
	else if(Command_Line[ZERO] == 'L'){
		command = going_left;
	}		
	else if(Command_Line[ZERO] == 'R'){
		command = going_right;
	}
	else if(Command_Line[ZERO] == 'S'){
          
          
		LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
		
		Time_Sequence = OFF;
		receiving_command = OFF;
		command = OFF;
	}
	
	else if(Command_Line[ZERO] == 'P'){
		receiving_command = OFF;
		switch(station_num){
		case EVENT_ZEROTH:
			IOT_Course_Driving = going;
			strcpy(display_line[ZERO], " STARTING  ");
			update_string(display_line[ZERO], ZERO);
			display_changed = YES;
			command = OFF;
			station_num = FIRST;
		break;
		case EVENT_FIRST:
			strcpy(display_line[ZERO], "ARRIVED 01");
			update_string(display_line[ZERO], ZERO);
			display_changed = YES;
			command = OFF;
			station_num = SECOND;
		break;
		case EVENT_SECOND:
			strcpy(display_line[ZERO], "ARRIVED 02");
			update_string(display_line[ZERO], ZERO);
			display_changed = YES;
			command = OFF;
			station_num = THIRD;
		break;
		case EVENT_THIRD:
			strcpy(display_line[ZERO], "ARRIVED 03");
			update_string(display_line[ZERO], ZERO);
			display_changed = YES;
			command = OFF;
			station_num = FOURTH;
		break;
		case EVENT_FOURTH:
			strcpy(display_line[ZERO], "ARRIVED 04");
			update_string(display_line[ZERO], ZERO);
			display_changed = YES;
			command = OFF;
			station_num = FIFTH;	
		break;
		case EVENT_FIFTH:
			strcpy(display_line[ZERO], "ARRIVED 05");
			update_string(display_line[ZERO], ZERO);
			display_changed = YES;
			command = OFF;
			station_num = SIXTH;
		break;
		case EVENT_SIXTH:
			strcpy(display_line[ZERO], "ARRIVED 06");
			update_string(display_line[ZERO], ZERO);
			display_changed = YES;
			command = OFF;
			station_num = SEVENTH;
		break;
		case EVENT_SEVENTH:
			strcpy(display_line[ZERO], "ARRIVED 07");
			update_string(display_line[ZERO], ZERO);
			display_changed = YES;
			command = OFF;
			station_num = EIGHTH;
		break;
		case EVENT_EIGHTH:
			IOT_Course_Driving = OFF;
			strcpy(display_line[ZERO], "ARRIVED 08");
			update_string(display_line[ZERO], ZERO);
			display_changed = YES;
			command = OFF;
			station_num = NINETH;
		break;
	         default:
		break;
		}
	}
	else{
		receiving_command = OFF;
		command = OFF;
	}
	
	break;
	
	case going_forwards:  
	RIGHT_FORWARD_SPEED = wheel_less_than_half;
	LEFT_FORWARD_SPEED = wheel_half_speed;
        
	if(Time_Sequence >= command_length){
                LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
		
		command = TWENTYFIRST;
	}
	break;
	
	case going_backwards:  
	RIGHT_REVERSE_SPEED = wheel_half_speed;
	LEFT_REVERSE_SPEED = wheel_fastest_speed ;
	if(Time_Sequence >= command_length){
		LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
		command = Screen_Change;
		HEXtoBCD_Display();
	}
	break;
	
	case going_left:  
	RIGHT_FORWARD_SPEED = wheel_half_speed;
	LEFT_REVERSE_SPEED = wheel_more_than_half;
	if(Time_Sequence >= command_length){
		LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
		
	}
	break;
	
	case going_right:  
	LEFT_FORWARD_SPEED = wheel_half_speed;
	RIGHT_REVERSE_SPEED = wheel_more_than_half;
	if(Time_Sequence >= command_length){
                LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
		
	}
	break;
	
	case Screen_Change:
	Time_Sequence = OFF;
	display_line[FIRST][THIRD] = Command_Line[FOURTH];
	display_line[FIRST][FOURTH] = Command_Line[FIFTH];
	display_line[FIRST][FIFTH] = Command_Line[SIXTH];
	display_line[FIRST][SIXTH] = Command_Line[SEVENTH];
	display_changed = YES;
	
	command_range_1st = Command_Line[FIFTH] - FOURTYEIGHT_CONVERSION;
	command_range_1st = command_range_1st * Event_One_Hundred;
	command_range_2nd = Command_Line[SIXTH] - ASCIItoDEC;
	command_range_2nd = command_range_2nd * TENTH;
	command_range_3rd = Command_Line[SEVENTH] - FOURTYEIGHT_CONVERSION;
	command_length = command_range_1st + command_range_2nd + command_range_3rd;

	if(Command_Line[FOURTH] == 'F'){
		command = Forward_Vroom;
	}		
	else if(Command_Line[FOURTH] == 'B'){
		command = Backward_Vroom;
	}		
	else if(Command_Line[FOURTH] == 'L'){
		command = Left_Vroom;
	}		
	else if(Command_Line[FOURTH] == 'R'){
		command = Right_Vroom;
	}
	else{
		receiving_command = OFF;
		
		Show_the_Network(index_c);
		command = OFF;
	}
	break;
	
	case Forward_Vroom:  //Forward
	RIGHT_FORWARD_SPEED = wheel_less_than_half;
	LEFT_FORWARD_SPEED = wheel_half_speed;
	if(Time_Sequence >= command_length){
		LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
		receiving_command = OFF;
		
		Show_the_Network(index_c);
		command = OFF;
	}
	break;
	
	case Backward_Vroom:  //Backward
	RIGHT_REVERSE_SPEED = wheel_half_speed;
	LEFT_REVERSE_SPEED = wheel_fastest_speed;
	if(Time_Sequence >= command_length){
		LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
		receiving_command = OFF;
			Show_the_Network(index_c);
		command = OFF;
	}
	break;
	
	case Left_Vroom:  //Left
        LEFT_REVERSE_SPEED = wheel_fastest_speed;
	RIGHT_FORWARD_SPEED = wheel_half_speed;
	
	if(Time_Sequence >= command_length){
          
		 LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
		receiving_command = OFF;
		Show_the_Network(index_c);
		command = OFF;
	}
	break;
	
	case Right_Vroom:  
	LEFT_FORWARD_SPEED = wheel_half_speed;
	RIGHT_REVERSE_SPEED = wheel_half_speed;
	if(Time_Sequence >= command_length){
		LEFT_REVERSE_SPEED = no_wheels_go;
		RIGHT_REVERSE_SPEED = no_wheels_go;
		LEFT_FORWARD_SPEED = no_wheels_go;
		RIGHT_FORWARD_SPEED = no_wheels_go;
		receiving_command = OFF;
		Show_the_Network(index_c);
		command = OFF;
	}
	break;	
	default:
	break;
	}
}
	
	
	
	