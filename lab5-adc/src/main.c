/***********************************************************************
 * 
 * Use Analog-to-digital conversion to read push buttons on LCD keypad
 * shield and display it on LCD screen.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2018 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and start ADC conversion every 100 ms.
 *           When AD conversion ends, send converted value to LCD screen.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize display
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(1, 0); lcd_puts("value:");
    lcd_gotoxy(3, 1); lcd_puts("key:");
    lcd_gotoxy(8, 0); lcd_puts("a");  // Put ADC value in decimal
    lcd_gotoxy(13,0); lcd_puts("b");  // Put ADC value in hexadecimal
    lcd_gotoxy(8, 1); lcd_puts("c");  // Put button name here

    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"

    ADMUX = ADMUX | (1<<REFS0);
    // Select input channel ADC0 (voltage divider pin) 
    ADMUX = ADMUX & ~(1<<MUX3 | 1<<MUX2 | 1<<MUX1 | 1<<MUX0);   //firstly all bit need to be set to 0
    // Enable ADC module
    ADCSRA = ADCSRA | (1<<ADEN); // ADCSARA is the register name and ADEn the bits name.
    // Enable conversion complete interrupt
    ADCSRA = ADCSRA | (1<<ADIE);
    // Set clock prescaler to 128, frequency must be between 50/200kHz, we use 128, in this way it is 125000Hz, it is in the middle
    ADCSRA = ADCSRA | (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0);

    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Set prescaler to 33 ms and enable overflow interrupt

    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Use single conversion mode and start conversion every 100 ms.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    static uint8_t no_of_overflows = 0;

    no_of_overflows ++;
    if (no_of_overflows >= 3){
        no_of_overflows = 0;
        ADCSRA = ADCSRA | (1 << ADSC);
    }
    
    // Else do nothing and exit the ISR
    // Start ADC conversion
}

/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Display converted value on LCD screen.
 **********************************************************************/
ISR(ADC_vect)
{
    uint16_t value;

    char string[4];  // String for converted numbers by itoa()

    // Read converted value
    // Note that, register pair ADCH and ADCL can be read as a 16-bit value ADC
    value = ADC;
    // Convert "value" to "string" and display it
    itoa(value, string, 10 ); // int_redix= wich value you want to obtain ( decimal=10, binary=2...)
    lcd_gotoxy(8, 0);
    lcd_puts("    "); // clean 4 spaces, clear the value, if not some could be sobreescribido
    lcd_gotoxy(8, 0);
    lcd_puts(string);  

    // write string in hexa, in position of b
    itoa(value, string, 16 ); // int_redix= wich value you want to obtain ( decimal=10, binary=2...)
    lcd_gotoxy(13, 0);
    lcd_puts("   "); // clean 3 spaces, clear the value, if not some could be sobreescribido
    lcd_gotoxy(13, 0);
    lcd_puts(string);

    itoa(value, string, 10 );
    if (80<string< 110){
        lcd_gotoxy(8, 1);
        lcd_puts("     "); 
        lcd_gotoxy(8, 1);
        lcd_puts("up");
    }
    if (240<string< 260){ 
        lcd_gotoxy(8, 1);
        lcd_puts("     ");
        lcd_gotoxy(8, 1);
        lcd_puts("down");
    } 
    if (400<string< 420){
        lcd_gotoxy(8, 1);
        lcd_puts("     "); 
        lcd_gotoxy(8, 1);
        lcd_puts("left");
    } 
    if (630<string< 650){ 
        lcd_gotoxy(8, 1);
        lcd_puts("     ");
        lcd_gotoxy(8, 1);
        lcd_puts("right");
    }
    if (string == 1023){ 
        lcd_gotoxy(8, 1);
        lcd_puts("     ");
        lcd_gotoxy(8, 1);
        lcd_puts("none");
    }  
    
}