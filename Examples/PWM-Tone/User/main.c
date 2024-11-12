/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Schrodinger.Guru
 * Version            : V1.0.0
 * Date               : 2024/09/13
 * Description        : Main program body with PWM tone generation.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *This program combines the USART multiprocessor communication mode and
 *PWM tone generation.
 *
 *USART Configuration:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 115200).
 *
 *Hardware connection:
 *PD5 -- USART1 Rx
 *PD6 -- USART1 Tx
 *PD2 -- Buzzer
 *
 */

#include "debug.h"  // Include necessary headers for debugging and configuration
#include <stdlib.h>  // Include standard library for rand()

#include "AlarmSystem.h"



void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // Enable clock for GPIOD

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;              // Select pin PD2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        // Configure as alternate function push-pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // Set speed to 50 MHz
    GPIO_Init(GPIOD, &GPIO_InitStructure);                 // Initialize GPIOD with the defined settings
}





//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------


int main(void)
{
    SystemCoreClockUpdate();  		// Update system clock
    GPIO_Configuration();     		// Configure GPIO for buzzer output

//    Play_Alarm_Tone_Jingle_Bells();     //(Work in Progress)

//    Play_Alarm_Tone_Happy_Birthday();  //play Happy Birthday tone

//    Play_Alarm_Tone();        		// Play the dynamic alarm tone

//    Play_Alarm_Tone_Slow_Beep();	//Slow Alternating Beep Pattern

	  Play_Alarm_Tone_SOS();		//S.O.S. Alarm Tone

    while (1)
    {
        // Main loop is empty as the alarm tone plays indefinitely
    }
}
