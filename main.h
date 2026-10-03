#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#define GREEN_LED_PIN PA1
#define BLUE_LED_PIN  PA2
#define RED_LED_PIN   PA3
#define BUZZER_PIN    PA4

void ThermalDetector(float temperature);

#endif