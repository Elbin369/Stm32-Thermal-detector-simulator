#include "enablePin.h"
#include "main.h"


void EnablePin_Init()
{
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    All_Outputs_OFF();
}


/* =========================
   GREEN LED
   ========================= */

void Green_LED_ON()
{
    digitalWrite(GREEN_LED_PIN, HIGH);
}


void Green_LED_OFF()
{
    digitalWrite(GREEN_LED_PIN, LOW);
}


/* =========================
   BLUE LED
   ========================= */

void Blue_LED_ON()
{
    digitalWrite(BLUE_LED_PIN, HIGH);
}


void Blue_LED_OFF()
{
    digitalWrite(BLUE_LED_PIN, LOW);
}


/* =========================
   RED LED
   ========================= */

void Red_LED_ON()
{
    digitalWrite(RED_LED_PIN, HIGH);
}


void Red_LED_OFF()
{
    digitalWrite(RED_LED_PIN, LOW);
}


/* =========================
   BUZZER
   ========================= */

void Buzzer_ON()
{
    digitalWrite(BUZZER_PIN, HIGH);
}


void Buzzer_OFF()
{
    digitalWrite(BUZZER_PIN, LOW);
}


/* =========================
   ALL OFF
   ========================= */

void All_Outputs_OFF()
{
    Green_LED_OFF();
    Blue_LED_OFF();
    Red_LED_OFF();
    Buzzer_OFF();
}