#ifndef UART_H
#define UART_H

#include <Arduino.h>

void UART_Init();

void UART_SendString(const char *text);

void UART_SendTemperature(float temperature);

void UART_SendStatus(const char *status);

#endif