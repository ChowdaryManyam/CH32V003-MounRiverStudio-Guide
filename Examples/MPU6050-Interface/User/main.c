/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Schrodinger.Guru
 * Version            : V1.1.0
 * Date               : 2024/09/25
 * Description        : Main program body for MPU6050 accelerometer communication.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
/*
 *@Note
 * Multiprocessor communication mode routine:
 * This routine demonstrates the MPU6050 module integration on
 * the CH32V003 (nano) board.
 *
 * Hardware connection:
 * PC1 -- SDA
 * PC2 -- SCL
 *
 */
/* Includes ------------------------------------------------------------------*/
#include "debug.h"

/* MPU6050 I2C Address */
#define MPU6050_ADDRESS 0x68

/* Register addresses */
#define MPU6050_REG_PWR_MGMT_1 0x6B
#define MPU6050_REG_ACCEL_XOUT_H 0x3B

/* Global Variable */
u8 data_buffer[6] = {0};

/*********************************************************************
 * @fn      IIC_Init
 *
 * @brief   Initializes the I2C peripheral.
 *
 * @param   bound - I2C clock speed, address - 7-bit own address.
 *
 * @return  none
 */
void IIC_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    I2C_InitTypeDef I2C_InitTSturcture = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  // SCL pin
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;  // SDA pin
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitTSturcture);

    I2C_Cmd(I2C1, ENABLE);
}

/*********************************************************************
 * @fn      MPU6050_WriteByte
 *
 * @brief   Write a byte to a specific MPU6050 register.
 *
 * @param   reg_addr - register address, data - byte to write.
 *
 * @return  none
 */
void MPU6050_WriteByte(u8 reg_addr, u8 data)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET);
    I2C_GenerateSTART(I2C1, ENABLE);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, MPU6050_ADDRESS << 1, I2C_Direction_Transmitter);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, reg_addr);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_SendData(I2C1, data);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C1, ENABLE);
}

/*********************************************************************
 * @fn      MPU6050_ReadBytes
 *
 * @brief   Read multiple bytes from a specific MPU6050 register.
 *
 * @param   reg_addr - starting register address, buffer - data buffer, length - number of bytes to read.
 *
 * @return  none
 */
void MPU6050_ReadBytes(u8 reg_addr, u8 *buffer, u8 length)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET);
    I2C_GenerateSTART(I2C1, ENABLE);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, MPU6050_ADDRESS << 1, I2C_Direction_Transmitter);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, reg_addr);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTART(I2C1, ENABLE);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, MPU6050_ADDRESS << 1, I2C_Direction_Receiver);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    while (length--)
    {
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
        *buffer++ = I2C_ReceiveData(I2C1);
    }

    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);
}

/*********************************************************************
 * @fn      MPU6050_Init
 *
 * @brief   Initialize the MPU6050 and set it to measurement mode.
 *
 * @return  none
 */
void MPU6050_Init(void)
{
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT_1, 0x00);  // Wake up the MPU6050
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program to read and display MPU6050 accelerometer data.
 *
 * @return  none
 */
int main(void)
{
    s16 x, y, z;

    SystemCoreClockUpdate();
    Delay_Init();

    USART_Printf_Init(115200);

    printf("SystemClk: %d\r\n", SystemCoreClock);
    printf("ChipID: %08x\r\n", DBGMCU_GetCHIPID());

    IIC_Init(100000, 0x00);
    MPU6050_Init();

    while (1)
    {
        // Read accelerometer data
        MPU6050_ReadBytes(MPU6050_REG_ACCEL_XOUT_H, data_buffer, 6);

        // Combine high and low bytes for each axis
        x = ((s16)data_buffer[0] << 8) | data_buffer[1];
        y = ((s16)data_buffer[2] << 8) | data_buffer[3];
        z = ((s16)data_buffer[4] << 8) | data_buffer[5];

        // Output accelerometer data
        printf("X: %d, Y: %d, Z: %d\r\n", x, y, z);

        Delay_Ms(100);  // Delay for stability
    }
}
