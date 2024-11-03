/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Schrodinger.Guru
 * Version            : V1.0.0
 * Date               : 2024/08/3
 * Description        : Toggling an LED using a push-button.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
/*
 *@Note
 * Multiprocessor communication mode routine:
 * This routine demonstrates the LED toggle functionality using a push-button on
 * the CH32V003 (nano) board.
 *
 * Hardware connection:
 * PD6 -- On-board LED
 * PD2 -- Push_Button (configured with a Pull-Down Resistor)
 *
 */

#include "debug.h"  // Include the header file for the standard peripheral library.

/* Global define */

/* Global Variable */
vu8 val;  // Volatile unsigned 8-bit variable to hold button state (not currently used).

/* GPIO Initialization Function for LED and Button */
void GPIO_Toggle_INIT(void)
{
    // Structure to hold GPIO initialization settings
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // Enable clock for the GPIOD peripheral
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    // Configure PD6 as output push-pull for LED
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;                 // Select pin PD6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;          // Set mode to push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         // Set output speed to 50 MHz
    GPIO_Init(GPIOD, &GPIO_InitStructure);                     // Initialize GPIO for LED

    // Configure PD2 as input with pull-down for push button
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                 // Select pin PD2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;             // Set mode to input with pull-down resistor
    GPIO_Init(GPIOD, &GPIO_InitStructure);                     // Initialize GPIO for button
}

int main(void)
{
    // System and delay initialization
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);           // Configure NVIC priority group
    SystemCoreClockUpdate();                                   // Update the system clock
    Delay_Init();                                             // Initialize delay functions

    // Initialize GPIO for LED and button
    GPIO_Toggle_INIT();                                       // Call function to initialize GPIO

    while(1)  // Main loop
    {
        // Check if the button is pressed (PD2 reads high when pressed)
        if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) == Bit_SET)
        {
            GPIO_WriteBit(GPIOD, GPIO_Pin_6, Bit_SET);      // Turn on LED if button is pressed
        }
        else
        {
            GPIO_WriteBit(GPIOD, GPIO_Pin_6, Bit_RESET);    // Turn off LED if button is not pressed
        }
        Delay_Ms(10); // Small delay for debounce to prevent false readings
    }
}
