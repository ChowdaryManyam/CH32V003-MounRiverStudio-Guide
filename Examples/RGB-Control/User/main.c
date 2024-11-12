/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Schrodinger.Guru
 * Version            : V1.0.0
 * Date               : 2024/09/13
 * Description        : Main program body for WS2812 RGB LED control.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *This program combines the USART multiprocessor communication mode and
 *alarm tone generation for an antitheft device.
 *
 *USART Configuration:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 115200).
 *
 *Hardware connection:
 *PD5 -- USART1 Rx
 *PD6 -- USART1 Tx
 *PC4 -- Din of RGB LED (strip) // Pin Configuration in GD_WS2812_DRIVER.h
 *
 */

// For SWIO programming
#include "debug.h"

// Define the number of LEDs in the strip
#define num_leds 1

// Include the sine and rand lookup tables
#include "lookups.h"

// Include the Green Dragon Bitbanging driver
#include "GD_WS2812_DRIVER.h"

// Include the colour and animation functios
#include "LED_functions.h"



// The main function initialises the Delay and GPIO, sets the initial color values of the LED strip to off
int main(void)
    {
    // Initialise delay
    Delay_Init();
    // configures GPIOC pin 4 as Output Push/Pull for data out
    GPIO_INITZ();
    Delay_Ms(5);
    // Send initial LED colour values to the LED strip
    LED_OFF();
    SHOWTIME(BUFFER_LEDS);
    Delay_Ms(200);

  // Loop
    while (1) {  
            
                /*Uncomment the following functions to execute*/
        
//            LED_COLD_WHITE();
//            LED_WARM_WHITE();
          LED_RAINBOWS(50,1); // variables are delay speed in mS and width (number of leds)
//            LED_BLUEFIRE(30); // variable is speed in mS delay
//            LED_STATIC_RANDOM();
//            LED_RED(255); // variable is brightness 0-255
    //        LED_GREEN(255); // variable is brightness 0-255
//            LED_BLUE(10); // variable is brightness 0-255
//            LED_CUSTOM(255,255,255); // set custom clour (red, green, blue) 0-255 RGB
//            LED_RGB_FLASH(200, 2); // variables are speed in mS delay and brightness
//            LED_WHITE_FLASH(50, 10); // variables are max and min flash speed
//            LED_WHITE_FADE(4); // variable is speed in mS delay


    } // end of while
} // end of Main
