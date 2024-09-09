/*

 * filename: CourseWork_JESSE.c

 * Author: jesse

 * Date: 10 November 2021, 12:40

 * Revision Number: 

 * Target Device: PIC18F452

 * Compiler: XC8

 * Summary: Final Coursework.

*/


//Configuration statements

// PIC18F452 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will cause RESET)
#pragma config LVP = OFF         // Low Voltage ICSP Enable bit (Low Voltage ICSP enabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.



//Included Files

#include <xc.h>     // XC8 compiler specifics

#include <stdio.h> // standard C I/O library

#include <stdlib.h> // standard C library



/* Connection information- Cathodes

 * Leftmost 7-seg, RA4
 * 7-seg 2, RA3
 * 7-seg 3, RA2
 * Rightmost 7-seg, RA1
 * Red and Green LEDs, RA5

 * Anodes PIC18F252

 * 7-seg Led a, RC0
 * 7-seg Led b, RC1
 * 7-seg Led c, RC2
 * 7-seg Led d, RC3
 * 7-seg Led e, RC4
 * 7-seg Led f, RC5
 * 7-seg Led g, RC6
 * 7-seg decimal points. RC7
 * Red LED, RC1
 * Green LED, RC0
  
 * Anodes PIC18F452
 
 * 7-seg Led a, RD0
 * 7-seg Led b, RD1
 * 7-seg Led c, RD2
 * 7-seg Led d, RD3
 * 7-seg Led e, RD4
 * 7-seg Led f, RD5
 * 7-seg Led g, RD6
 * 7-seg decimal points. RD7
 * Red LED, RD1
 * Green LED, RD0

 * Switches

 * Left RB1
 * Right RB0

*/

//Definitions

#define _XTAL_FREQ 24000000

// The Cathode drives for each 7 seg display
#define CATHODE_4 PORTAbits.RA1
#define CATHODE_3 PORTAbits.RA2
#define CATHODE_2 PORTAbits.RA3
#define CATHODE_1 PORTAbits.RA4
#define CATHODE_L PORTAbits.RA5

//byte-wise access to cathode port
#define CATHODES PORTA

//cathode port set-up
#define CATHODES_CFG TRISA

//Switch pin names. Note that if using as interrupt sources, these can be named as such
#define SWITCH_0 PORTBbits.RB0
#define SWITCH_1 PORTBbits.RB1

//byte-wise access to switches
#define SWITCHES PORTB

//Switch port setup
#define SWITCHES_CFG TRISB

//7 seg disp anode drive. Note drives all four in parallel, cathode drive selects which is on for PIC18F252 comment out one not used
//#define ANODE_A PORTCbits.RC0
//#define ANODE_B PORTCbits.RC1
//#define ANODE_C PORTCbits.RC2
//#define ANODE_D PORTCbits.RC3
//#define ANODE_E PORTCbits.RC4
//#define ANODE_F PORTCbits.RC5
//#define ANODE_G PORTCbits.RC6
//#define ANODE_DP PORTCbits.RC7

//7 seg disp anode drive. Note drives all four in parallel, cathode drive selects which is on for PIC18F452 comment out one not used
#define ANODE_A PORTDbits.RD0
#define ANODE_B PORTDbits.RD1
#define ANODE_C PORTDbits.RD2
#define ANODE_D PORTDbits.RD3
#define ANODE_E PORTDbits.RD4
#define ANODE_F PORTDbits.RD5
#define ANODE_G PORTDbits.RD6
#define ANODE_DP PORTDbits.RD7

//byte-wise access to port on PIC18F252 comment out if using 452
//#define ANODES PORTC

//byte-wise access to port on PIC18F452 comment out is using 252
#define ANODES PORTD

//port set up PIC18F252 comment out on 452
//#define ANODES_CFG TRISC 

//port set up PIC18F452 comment out on 252
#define ANODES_CFG TRISD 

//Global Variables

    int timer[7] = {0,0,0,0,0,0}; //to display the digits
    int dig[5] = {0,0,0,0}; // stored values for the lap
    int p = 0; // to move from ss.msms to mm:ss
    int d = 0; // Loop variables
    int a[10]; //used for the maths involving the anodes
    int c[6]; // used for the maths involving the cathodes
    int stopwatch = 0;
    int lap = 0; // Lap variable
    int b[10] = {0,1,2,3,4,5,6,7,8,9};
    int j; // Loop variables
    int x = 0; // Loop variables
    int k; // Loop variables
    int count = 0; //Stops the lap from being overused
    int stop = 0; //Helps with the reset
    int reset = 0; //start at the beginning
    
//Functions

void setup(void);

//Interrupt Functions (if used)

void __interrupt() HighInt(void);

//Main Function

void main(void)
{

    //Local Variables
        
    //Call initialisation function if used

    setup();

    //Local default set-up parameters

    //anode outputs
    a[0]=0b10111111; //Port A value to illuminate value "0"
    a[1]=0b10000110; //Port A value to illuminate value "1"
    a[2]=0b11011011; //Port A value to illuminate value "2"
    a[3]=0b11001111; //Port A value to illuminate value "3"
    a[4]=0b11100110; //Port A value to illuminate value "4"
    a[5]=0b11101101; //Port A value to illuminate value "5"
    a[6]=0b11111101; //Port A value to illuminate value "6"
    a[7]=0b10000111; //Port A value to illuminate value "7"
    a[8]=0b11111111; //Port A value to illuminate value "8"
    a[9]=0b11101111; //Port A value to illuminate value "9"

    //cathode outputs
    c[1]=0b00000001; //Port C value to enable rightmost 7-segment
    c[2]=0b00000010; //Port C value to enable second right 7-segment
    c[3]=0b00000100; //Port C value to enable second left 7-segment
    c[4]=0b00001000; //Port C value to enable leftmost 7-segment
    c[5]=0b00010000; //Port C value to enable red and green LEDs
    
    //The actual code
    
    while (1) //shows the 00:00
    {
	if (reset == 0)
	{
            CATHODES = c[1];
            ANODES = a[1];  //my stopwatch just won't respond unless there is a value of 1 in the digit.
            CATHODES = c[2];
            ANODES = a[0];
            CATHODES = c[3];
            ANODES = a[0];
            CATHODES = c[4];
            ANODES = a[0];
	}

        if (stopwatch == 1) //if the start button is pressed.
        {
            if (p == 0 && lap == 0)
        {
            CATHODES = c[4];
            ANODES = a[timer[0]];
            CATHODES = c[1];
            ANODES = a[timer[1]];
            CATHODES = c[2];
            ANODES = a[timer[2]];
            CATHODES = c[3];
            ANODES = a[timer[3]];
        }
        if (p == 0 && lap == 1)
        {
            CATHODES = c[1];
            ANODES = a[dig[0]];
            CATHODES = c[2];
            ANODES = a[dig[1]];
            CATHODES = c[3];
            ANODES = a[dig[2]]; 
            CATHODES = c[4];
            ANODES = a[dig[3]];
        }
        if (count == 2 && p == 0 && lap == 1)
        {
            lap = 0;
            count = 0;
        }
	if (p == 1 && lap == 0) //for once it reaches 1 minute it stops the lights from covering the main lights.
        {
            CATHODES = c[4];
            ANODES = a[timer[2]]; 
            CATHODES = c[1];
            ANODES = a[timer[3]];
            CATHODES = c[2];
            ANODES = a[timer[4]];
            CATHODES = c[3];
            ANODES = a[timer[5]];
        }
        if (p == 1 && lap == 1)//lap
        {
            CATHODES = c[1];
            ANODES = a[dig[2]];
            CATHODES = c[2];
            ANODES = a[dig[3]];
            CATHODES = c[3];
            ANODES = a[dig[4]]; 
            CATHODES = c[4];
            ANODES = a[dig[5]];
        }
        if (count == 2 && p == 1 && lap == 1)
        {
            lap = 0;
            count = 0;
        }
	if (reset == 2)
	{
		reset = 0;
	}
        }
    }

    while (1)
    {
        if (p == 1 && lap == 0) //for once it reaches 1 minute it stops the lights from covering the main lights.
        {
            CATHODES = c[4];
            ANODES = a[timer[2]]; 
            CATHODES = c[1];
            ANODES = a[timer[3]];
            CATHODES = c[2];
            ANODES = a[timer[4]];
            CATHODES = c[3];
            ANODES = a[timer[5]];
        }
        else //lap
        {
            CATHODES = c[1];
            ANODES = a[dig[2]];
            CATHODES = c[2];
            ANODES = a[dig[3]];
            CATHODES = c[3];
            ANODES = a[dig[4]]; 
            CATHODES = c[4];
            ANODES = a[dig[5]];
        }
        if (count == 2)
        {
            lap = 0;
            count = 0;
        }
	if (reset == 2)
	{
		reset = 0;
		break;
	}
    }
} //End of the main function

//The setup function. May be OTT here but included to show process

void setup(void) 
{

    // Port configuration
    ANODES_CFG = 0b00000000; // 0 = output, 1 = input - Anodes (Resistor chip))
    CATHODES_CFG = 0b00000000; // Cathodes (Transistor chip))
    SWITCHES_CFG = 0b00000011; // RB0 & RB1 as inputs (active low)
    ADCON1bits.PCFG = 0b0111; //Configures all Port A bits as digital
    //TRISB = 1;

    // Switches Set-up
    INTCON2bits.RBPU = 0; // Port B inputs all have weak pull-ups, thus turn them all on
    INTCON2bits.INTEDG0 = 1;//Set the external interrupt to be rising edge triggered
    INTCON = 0b11000000; //Sets the global and peripheral enable.
    
    RCONbits.IPEN = 1; // Set IPEN to 1.
    INTCONbits.GIEH = 1; //Set High level global interrupt enable.
    INTCONbits.INT0IE = 1; // Set RB0
    INTCON3bits.INT1IE = 1; //Set RB1
    INTCON2bits.INTEDG0 = 0; //Set INT0 onto "falling"
    INTCON2bits.INTEDG1 = 0; //Set INT1 onto "falling"
    INTCON3bits.INT1IP = 1; //Set to high priority.
    
    //Timer 2 Set-up
    IPR1bits.TMR2IP = 1; //Timer 2 high Priority interrupt flag
    PIE1bits.TMR2IE = 1; //Timer 2 interrupt enable
    TMR2 = 0; //Timer2 Set to output.
    PR2 = 0b11111001; //249 value for PR2
    T2CONbits.T2CKPS = 0b11; //Timer 2 Multiplier A (16) for pre-scale
    T2CONbits.TOUTPS = 0b1110; //Timer 2 Multiplier B (15) for pre-scale
}

void __interrupt() HighInt(void)
{   
    
    if(PIE1bits.TMR2IE && PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0; //reset interrupt flag
        if (stopwatch == 1)
        {
            timer[0]++; //timer [0] = 0 will keep being added until the if statement below is true. ss.d9
            if (timer[0] > 9)
            {
                timer[1]++; // Display mm:ss:msms (00:00:ms0)
                timer[0] = 0; //Displays a zero once timer[] is greater than 9.
            }
            if (timer[1] > 9)
            {
                timer[2]++; // Display mm:ss:msms (00:0s:00)
                timer[1] = 0; 
            }
            if (timer[2] > 9)
            {
                timer[3]++; // Display mm:ss:msms (00:s0:00)
                timer[2] = 0;
            }
            if (timer[3] > 5)
            {
                timer[4]++; // Display mm:ss:msms (0m:00:00)
                timer[3] = 0;
                p = 1;
            }
            if (timer[4] > 9)
            {
                timer[5]++; // Display mm:ss:msms (m0:00:00)
                timer[4] = 0;
            }
            if (timer[5] > 5)
            {
                timer[5] = 0; // Display mm:ss:msms (00:00:00)
            }
        }
    }

    if (INTCONbits.INT0IF) //test for external 0 flag
    {                  
        INTCONbits.INT0IF = 0; //Resets the interrupt flag
        if (SWITCH_0 == 0) // if the button has been pressed and the stopwatch is running
        {
	if (lap == 1)
	{
		return;
	}
            if (stopwatch == 1)
            {
                SWITCH_0 =~ SWITCH_0;
                T2CONbits.TMR2ON =~ T2CONbits.TMR2ON; //Pause Timer 2
                stopwatch = 1; //stopwatch (off)
                stop = 1;
            }
            else //if stopwatch is 0. the start button
            {
                T2CONbits.TMR2ON = 1;
                SWITCH_0 =~ SWITCH_0;
                stopwatch = 1;
                reset = 1;
            }
        }
    }

    if (INTCON3bits.INT1IF) //Test for external 1 flag
    {
        INTCON3bits.INT1IF = 0; //Resets the interrupt flag
        if (SWITCH_1 == 0) // if the button has been pressed and the stopwatch is running
        {
            if (stopwatch == 1 && stop == 0)
            {
                count++;
                if (count == 2)
                {
                    return;
                }
                SWITCH_1 =~ SWITCH_1;
                lap = 1;
                for (j = 0; j < 6; j++)
                {
                    while (b[k] != timer[j])
                    {
                        k++;
                        for (k = 0; k < 9; k++)
                        {
                            if (timer[j] == b[k]) //checks through code to find the
                            {
                                dig[x] = timer[j]; //correct//takes values from active timer
                                x++;
                                break;
                            }
                        }
                    }
                }
            }
            if (stopwatch == 1 && stop == 1)
            {
                for (d = 0; d > 6; d++)
                {
                    timer[d] = 0;
                }
                SWITCH_1 =~ SWITCH_1;
		stop = 0;
		count = 0;
		x = 0;
		lap = 0;
        reset = 2;
		stopwatch = 0;
		T2CONbits.TMR2ON = 0; //Reset Timer 2
		p = 0;
		SWITCH_0 = 1;
		SWITCH_1 = 1;
            }
        }
    }
    return;
}
