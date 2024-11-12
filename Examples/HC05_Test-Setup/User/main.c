/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Schrodinger.Guru
 * Version            : V1.0.0
 * Date               : 2024/09/13
 * Description        : Main program body for HC-05 Bluetooth Communication.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *This program combines the USART multiprocessor communication mode and
 *USART Configuration:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 9600) via HC05 to a Bluetooth Serial monitoring app/device.
 *
 *Hardware connection:
 *PD5 -- USART1 Tx
 *PD6 -- USART1 Rx
 *
 */

#include "debug.h"

/* Function Prototypes */
void USART1_Init(void);
void USART1_SendChar(char ch);
void USART1_SendString(char *str);

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    /* Initialize USART1 for HC05 Bluetooth communication on PD5 (TX) */
    USART1_Init();

    /* Main loop */
    while (1)
    {
        /* Send data over USART1 (HC05 Bluetooth module) */
        USART1_SendString("Hello  HC05\r\n");

        Delay_Ms(2000);  // 1-second delay
    }
}

/*********************************************************************
 * @fn      USART1_Init
 *
 * @brief   Initializes USART1 for Bluetooth HC05 communication on PD5 (TX).
 *
 * @return  none
 */
void USART1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* Enable GPIO and USART1 clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  // Enable USART1 clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);   // Enable GPIOD clock

    /* Configure PD5 (TX) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* USART1 configuration */
    USART_InitStructure.USART_BaudRate =9600;  // HC05 default baud rate is 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;

    /* Initialize USART1 */
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

/*********************************************************************
 * @fn      USART1_SendChar
 *
 * @brief   Sends a single character over USART1 (HC05 Bluetooth module).
 *
 * @param   ch - The character to send.
 *
 * @return  none
 */
void USART1_SendChar(char ch)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, (uint16_t)ch);
}

/*********************************************************************
 * @fn      USART1_SendString
 *
 * @brief   Sends a null-terminated string over USART1.
 *
 * @param   str - Pointer to the string to send.
 *
 * @return  none
 */
void USART1_SendString(char *str)
{
    while (*str)
    {
        USART1_SendChar(*str++);
    }
}
