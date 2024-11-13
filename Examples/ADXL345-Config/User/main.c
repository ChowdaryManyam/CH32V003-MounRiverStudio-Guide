/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Schrodinger.Guru
 * Version            : V1.1.0
 * Date               : 2024/09/20
 * Description        : Main program body for ADXL345 accelerometer communication.
 *********************************************************************************/
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
/*
 *@Note
 * Multiprocessor communication mode routine:
 * This routine demonstrates the ADXL345 module integration on
 * the CH32V003 (nano) board.
 *
 * Hardware connection:
 * PC1 -- SDA
 * PC2 -- SCL
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "debug.h"

/*
 *@Note
 *I2C interface routine to operate ADXL345 accelerometer:
 *I2C1_SCL(PC2)\I2C1_SDA(PC1).
 *This example uses the ADXL345 accelerometer to read X, Y, Z axis data.
 *Display data on USART with TX on (PD5)
 *Steps:
 *READ ADXL345:
 *  1. Start Condition.
 *  2. Send Device Address (0xA6 for Read, 0xA7 for Write).
 *  3. Send the Register Address (e.g., DATAX0 to start reading X-axis data).
 *  4. Repeat Start Condition (to initiate read).
 *  5. Send Device Address with Read bit (0xA7).
 *  6. Read 6 bytes of data (X0, X1, Y0, Y1, Z0, Z1).
 *  7. Stop Condition.
 *
 *WRITE ADXL345:
 *  1. Start Condition.
 *  2. Send Device Address (0xA6 for Write).
 *  3. Send the Register Address (e.g., DATA_FORMAT to configure the sensor).
 *  4. Write Data (e.g., configuration data like +/-2g range).
 *  5. Stop Condition.
 *
 *Initial Setup:
 *  1. Initialize I2C communication.
 *  2. Set up ADXL345 in Measurement Mode.
 *
 */

/* ADXL345 I2C Address (when ALT ADDRESS pin is grounded) */
#define ADXL345_ADDRESS 0x53
/* Register addresses */
#define ADXL345_REG_DEVID 0x00
#define ADXL345_REG_POWER_CTL 0x2D
#define ADXL345_REG_DATA_FORMAT 0x31
#define ADXL345_REG_DATAX0 0x32
#define ADXL345_REG_DATAX1 0x33
#define ADXL345_REG_DATAY0 0x34
#define ADXL345_REG_DATAY1 0x35
#define ADXL345_REG_DATAZ0 0x36
#define ADXL345_REG_DATAZ1 0x37

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
 * @fn      ADXL345_WriteByte
 *
 * @brief   Write a byte to a specific ADXL345 register.
 *
 * @param   reg_addr - register address, data - byte to write.
 *
 * @return  none
 */
void ADXL345_WriteByte(u8 reg_addr, u8 data)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET);
    I2C_GenerateSTART(I2C1, ENABLE);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, ADXL345_ADDRESS << 1, I2C_Direction_Transmitter);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, reg_addr);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_SendData(I2C1, data);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C1, ENABLE);
}

/*********************************************************************
 * @fn      ADXL345_ReadBytes
 *
 * @brief   Read multiple bytes from a specific ADXL345 register.
 *
 * @param   reg_addr - starting register address, buffer - data buffer, length - number of bytes to read.
 *
 * @return  none
 */
void ADXL345_ReadBytes(u8 reg_addr, u8 *buffer, u8 length)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET);
    I2C_GenerateSTART(I2C1, ENABLE);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, ADXL345_ADDRESS << 1, I2C_Direction_Transmitter);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, reg_addr);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTART(I2C1, ENABLE);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, ADXL345_ADDRESS << 1, I2C_Direction_Receiver);

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
 * @fn      ADXL345_Init
 *
 * @brief   Initialize the ADXL345 and set it to measurement mode.
 *
 * @return  none
 */
void ADXL345_Init(void)
{
    ADXL345_WriteByte(ADXL345_REG_POWER_CTL, 0x08);  // Set the device to measurement mode
    ADXL345_WriteByte(ADXL345_REG_DATA_FORMAT, 0x08);  // Set data format to full resolution, +/-2g
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program to read and display ADXL345 accelerometer data.
 *
 * @return  none
 */
int main(void)
{
    s16 x, y, z;
    uint8_t data_buffer[6];

    SystemCoreClockUpdate();
    Delay_Init();

    USART_Printf_Init(115200);

    printf("SystemClk: %d\r\n", SystemCoreClock);
    printf("ChipID: %08x\r\n", DBGMCU_GetCHIPID());



    while (1)
    {
    	IIC_Init(100000, 0x00);
    	ADXL345_Init();
        // Read accelerometer data
        ADXL345_ReadBytes(ADXL345_REG_DATAX0, data_buffer, 6);

        // Combine high and low bytes for each axis
        x = ((s16)data_buffer[1] << 8) | data_buffer[0];
        y = ((s16)data_buffer[3] << 8) | data_buffer[2];
        z = ((s16)data_buffer[5] << 8) | data_buffer[4];

        // Output accelerometer data
        printf("X: %d, Y: %d, Z: %d\r\n", x, y, z);

        // Small delay for stability
        //for (volatile int i = 0; i < 10000; i++);
        Delay_Ms(100);  // Reduce delay for faster data output
    }
}

