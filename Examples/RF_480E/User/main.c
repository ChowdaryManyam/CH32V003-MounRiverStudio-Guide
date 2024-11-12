/********************************** (C) COPYRIGHT *******************************
 * File Name          : RF-433MHz_Remote data display
 * Author             : Schrodinger-Guru
 * Version            : V1.0.0
 * Date               : 2024/09/20
 * Description        : Main program body for RF-433MHZ data read, to identify the corresponding button press.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *This program configures USART1 (TX: PD5) to send messages over
 *serial communication. Additionally, it monitors the states of four GPIO pins
 *(PC1, PC2, PC3, PC4) to detect input changes. When the state of any pin
 *transitions from low to high (representing a press event), the program sends
 *a corresponding message to the serial terminal.
 *
 *Pin Connections:
 *- PD5: USART1 Receive (Rx)
 *- PD6: USART1 Transmit (Tx)
 *- PC3, PC5, PC6, PC7: Input pins connected to external signals
 *
 *Functionality:
 *- Monitors the input states of PC3, PC5, PC6, and PC7.
 *- On detecting a change in state from low to high, sends a "PCx pressed" message
 *  via USART1.
 *
 *USART Configuration:
 *- Baud Rate: 115200
 *- Word Length: 8 bits
 *- Stop Bits: 1
 *- Parity: None
 *
 */


#include "debug.h"


/* Global define */


/* Global Variable */
vu8 val;

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART1 peripheral.
 *
 * @return  none
 */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    /* Enable clocks for GPIOD and USART1 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* Enable clock for GPIOC */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Configure RX480E data pins as input floating (PC1 to PC4) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* USART1 Configuration */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    uint8_t pc3_state, pc5_state, pc6_state, pc7_state;
    uint8_t pc3_prev_state, pc5_prev_state, pc6_prev_state, pc7_prev_state;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
#if (SDI_PRINT == SDI_PR_OPEN)
    SDI_Printf_Enable();
#else
    USART_Printf_Init(115200);
#endif
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());

    /* Initialize previous states with the current state of the pins */
    pc3_prev_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);
    pc5_prev_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5);
    pc6_prev_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
    pc7_prev_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7);

    USARTx_CFG();

    while(1)
    {
        /* Read GPIOC pin states (PC1 to PC4) */
        pc3_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);
        pc5_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5);
        pc6_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
        pc7_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7);

        /* Check if PC3 state has changed */
        if(pc3_state != pc3_prev_state)
        {
            if(pc3_state == 1)
                printf("Button: C pressed\n");
            pc3_prev_state = pc3_state;  // Update previous state
        }

        /* Check if PC5 state has changed */
        if(pc5_state != pc5_prev_state)
        {
            if(pc5_state == 1)
                printf("Button: A pressed\n");
            pc5_prev_state = pc5_state;  // Update previous state
        }

        /* Check if PC6 state has changed */
        if(pc6_state != pc6_prev_state)
        {
            if(pc6_state == 1)
                printf("Button: D pressed\n");
            pc6_prev_state = pc6_state;  // Update previous state
        }

        /* Check if PC7 state has changed */
        if(pc7_state != pc7_prev_state)
        {
            if(pc7_state == 1)
                printf("Button: B pressed\n");
            pc7_prev_state = pc7_state;  // Update previous state
        }

        /* Add a small delay */
        //Delay_Ms(500);  // Delay for half a second before the next check
    }
}
