/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Schrodinger.Guru
 * Version            : V1.0.0
 * Date               : 2024/08/2
 * Description        : On-Board_PD4_LED-Blink
 *********************************************************************************
 * Copyright (c)
 * Attention: This software (modified or not) and binary are used for 
 * CH32V003 microcontroller.
 *******************************************************************************/

/*
 *@Note
 *Multiprocessor communication mode routine:
 *This routine demonstrates a "Hello World" (LED Blinking) on CH32V003 board.
 *
 *Hardware connection: PD4 -- On-board LED
 *
 */

#include "debug.h"  // Include debug library for delay and system configuration functions

/* Global Variables */
vu8 val;  // Declare a volatile unsigned 8-bit variable

/**
 * @brief  GPIO Toggle Initialization
 * @note   Configures the GPIO pin (PD4) as an output for LED blinking.
 * @param  None
 * @retval None
 */

void GPIO_Toggle_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};  // Initialize GPIO structure to default values

    // Enable the clock for GPIOD peripheral
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    // Configure PD4 as Push-Pull Output at 10 MHz
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;          // Set GPIO pin to PD4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // Set mode to push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  // Set output speed to 10 MHz
    GPIO_Init(GPIOD, &GPIO_InitStructure);             // Initialize PD4 with these settings
}

/**
 * @brief  Main Program Entry
 * @note   Main function toggles the LED at regular intervals.
 * @param  None
 * @retval int
 */
int main(void)
{
    u8 i = 0;  // Toggle state variable (initially 0)

    // Configure NVIC priority group for interrupt management
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    // Update the system core clock and initialize delay functions
    SystemCoreClockUpdate();
    Delay_Init();

    /* Debug Configuration (Commented out by default)
    #if (SDI_PRINT == SDI_PR_OPEN)
        SDI_Printf_Enable();     // Enable Serial Debug Interface Printf if enabled
    #else
        USART_Printf_Init(115200);  // Initialize USART for printing at 115200 baud rate
    #endif
    printf("SystemClk:%d\r\n",SystemCoreClock);  // Print system clock speed
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );  // Print unique Chip ID
    printf("GPIO Toggle TEST\r\n");  // Print test message
    */

    // Initialize GPIO for LED toggle
    GPIO_Toggle_INIT();

    // Main loop: Toggle LED at regular intervals
    while(1)
    {
        Delay_Ms(150);  // Delay for 150 milliseconds

        // Toggle PD4 state: set to HIGH if `i` is 0, else set to LOW
        GPIO_WriteBit(GPIOD, GPIO_Pin_4, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
    }
}
