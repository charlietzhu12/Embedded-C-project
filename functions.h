//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  @author Charles Zhu
//  Jan 2020
//  Built with IAR Embedded Workbench Version: 7.12.4
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);

// Clocks
void Init_Clocks(void);

// LED Configurations
void Init_LEDs(void);
void Init_ADC(void);

  // LCD
void Display_Process(void);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_BIG_mid(void);
void lcd_4line(void);

//ports

void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(unsigned int);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

//Car movements
void all_wheels_off(void);
void left_wheel_forward_on(void);
void left_wheel_reverse_on(void);
void left_wheels_off(void);
void right_wheel_forward_on(void);
void right_wheel_reverse_on(void);
void right_wheels_off(void);
void wheels(void);


//ADC VALUES
void HEXtoBCD(int hex_value);

//DETECTING LINE
void Detecting_the_line(void);

//HEX TO BCD CONVERSION DISPLAY ON LCD
void HEXtoBCD_Display(void);

//switches
void Turn_on_Button_for_connection_to_wifi(void);
void Turn_on_Button_for_sending_information_to_iot(void);

// serial communication 
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);


void out_character_UCA0(char cha);
void out_character_UCA1(char chb);

// IOT MODULE 


void Read_the_network_name(int index_a);

void Show_the_Network(int index_b);

void ReadCommand(int index_c);

void readNetwork(void);



void readtheNetwork();

void Sending_vital_info_IOT(char* order);

	
	
	
