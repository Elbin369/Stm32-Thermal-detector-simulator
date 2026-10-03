#include "app_uart.h"
#include "main.h"

#include "stm32f1xx_hal.h"

#include <stdio.h>
#include <string.h>


UART_HandleTypeDef huart1;


void UART_Init()
{
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();


    GPIO_InitTypeDef GPIO_InitStruct = {0};


    /*
     * PA9 = USART1 TX
     */

    GPIO_InitStruct.Pin = GPIO_PIN_9;

    GPIO_InitStruct.Mode =
        GPIO_MODE_AF_PP;

    GPIO_InitStruct.Speed =
        GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(
        GPIOA,
        &GPIO_InitStruct
    );


    /*
     * PA10 = USART1 RX
     */

    GPIO_InitStruct.Pin =
        GPIO_PIN_10;

    GPIO_InitStruct.Mode =
        GPIO_MODE_INPUT;

    GPIO_InitStruct.Pull =
        GPIO_NOPULL;

    HAL_GPIO_Init(
        GPIOA,
        &GPIO_InitStruct
    );


    huart1.Instance =
        USART1;

    huart1.Init.BaudRate =
        115200;

    huart1.Init.WordLength =
        UART_WORDLENGTH_8B;

    huart1.Init.StopBits =
        UART_STOPBITS_1;

    huart1.Init.Parity =
        UART_PARITY_NONE;

    huart1.Init.Mode =
        UART_MODE_TX_RX;

    huart1.Init.HwFlowCtl =
        UART_HWCONTROL_NONE;

    huart1.Init.OverSampling =
        UART_OVERSAMPLING_16;


    HAL_UART_Init(&huart1);
}


/* =========================
   SEND STRING
   ========================= */

void UART_SendString(const char *text)
{
    HAL_UART_Transmit(
        &huart1,
        (uint8_t *)text,
        strlen(text),
        1000
    );
}


/* =========================
   SEND TEMPERATURE
   ========================= */

void UART_SendTemperature(float temperature)
{
    char buffer[50];

    sprintf(
        buffer,
        "Temperature: %.1f C\r\n",
        temperature
    );

    UART_SendString(buffer);
}


/* =========================
   SEND STATUS
   ========================= */

void UART_SendStatus(const char *status)
{
    char buffer[60];

    sprintf(
        buffer,
        "Status: %s\r\n",
        status
    );

    UART_SendString(buffer);
}