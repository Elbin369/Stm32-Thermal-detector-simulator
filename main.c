#include "main.h"
#include "uart.h"
#include "enablePin.h"

#include "stm32f1xx_hal.h"

#include <stdio.h>


/* =====================================================
   OLED
   ===================================================== */

#define OLED_ADDRESS 0x3C << 1


I2C_HandleTypeDef hi2c1;


/* =====================================================
   OLED COMMAND
   ===================================================== */

void OLED_Command(uint8_t command)
{
    uint8_t data[2];

    data[0] = 0x00;
    data[1] = command;

    HAL_I2C_Master_Transmit(
        &hi2c1,
        OLED_ADDRESS,
        data,
        2,
        100
    );
}


/* =====================================================
   OLED DATA
   ===================================================== */

void OLED_Data(uint8_t dataByte)
{
    uint8_t data[2];

    data[0] = 0x40;
    data[1] = dataByte;

    HAL_I2C_Master_Transmit(
        &hi2c1,
        OLED_ADDRESS,
        data,
        2,
        100
    );
}


/* =====================================================
   OLED INITIALIZATION
   ===================================================== */

void OLED_Init()
{
    delay(100);

    OLED_Command(0xAE);

    OLED_Command(0x20);
    OLED_Command(0x00);

    OLED_Command(0xB0);

    OLED_Command(0xC8);

    OLED_Command(0x00);

    OLED_Command(0x10);

    OLED_Command(0x40);

    OLED_Command(0x81);
    OLED_Command(0x7F);

    OLED_Command(0xA1);

    OLED_Command(0xA6);

    OLED_Command(0xA8);
    OLED_Command(0x3F);

    OLED_Command(0xA4);

    OLED_Command(0xD3);
    OLED_Command(0x00);

    OLED_Command(0xD5);
    OLED_Command(0x80);

    OLED_Command(0xD9);
    OLED_Command(0xF1);

    OLED_Command(0xDA);
    OLED_Command(0x12);

    OLED_Command(0xDB);
    OLED_Command(0x40);

    OLED_Command(0x8D);
    OLED_Command(0x14);

    OLED_Command(0xAF);
}


/* =====================================================
   OLED CLEAR
   ===================================================== */

void OLED_Clear()
{
    for(uint8_t page = 0; page < 8; page++)
    {
        OLED_Command(0xB0 + page);

        OLED_Command(0x00);
        OLED_Command(0x10);

        for(uint8_t column = 0;
            column < 128;
            column++)
        {
            OLED_Data(0x00);
        }
    }
}


/* =====================================================
   FONT 5x7
   ===================================================== */

const uint8_t Font5x7[10][5] =
{
    {0x3E,0x51,0x49,0x45,0x3E},  /* 0 */
    {0x00,0x42,0x7F,0x40,0x00},  /* 1 */
    {0x42,0x61,0x51,0x49,0x46},  /* 2 */
    {0x21,0x41,0x45,0x4B,0x31},  /* 3 */
    {0x18,0x14,0x12,0x7F,0x10},  /* 4 */
    {0x27,0x45,0x45,0x45,0x39},  /* 5 */
    {0x3C,0x4A,0x49,0x49,0x30},  /* 6 */
    {0x01,0x71,0x09,0x05,0x03},  /* 7 */
    {0x36,0x49,0x49,0x49,0x36},  /* 8 */
    {0x06,0x49,0x49,0x29,0x1E}   /* 9 */
};


/* =====================================================
   PRINT NUMBER
   ===================================================== */

void OLED_PrintNumber(int number)
{
    char buffer[10];

    sprintf(
        buffer,
        "%d",
        number
    );


    for(
        uint8_t i = 0;
        buffer[i] != '\0';
        i++
    )
    {
        if(
            buffer[i] >= '0' &&
            buffer[i] <= '9'
        )
        {
            uint8_t digit =
                buffer[i] - '0';


            for(
                uint8_t j = 0;
                j < 5;
                j++
            )
            {
                OLED_Data(
                    Font5x7[digit][j]
                );
            }

            OLED_Data(0x00);
        }
    }
}


/* =====================================================
   SHOW TEMPERATURE
   ===================================================== */

void OLED_ShowTemperature(
    float temperature
)
{
    int temp =
        (int)temperature;


    OLED_Clear();


    /*
     * Move to page 2
     */

    OLED_Command(0xB2);

    OLED_Command(0x00);
    OLED_Command(0x10);


    /*
     * Display temperature
     */

    OLED_PrintNumber(temp);


    /*
     * Degree symbol
     */

    OLED_Data(0x06);
    OLED_Data(0x09);
    OLED_Data(0x09);
    OLED_Data(0x06);


    /*
     * C
     */

    OLED_Data(0x3E);
    OLED_Data(0x41);
    OLED_Data(0x41);
    OLED_Data(0x41);
    OLED_Data(0x22);
}


/* =====================================================
   I2C INITIALIZATION
   ===================================================== */

void OLED_I2C_Init()
{
    __HAL_RCC_GPIOB_CLK_ENABLE();

    __HAL_RCC_I2C1_CLK_ENABLE();


    GPIO_InitTypeDef GPIO_InitStruct = {0};


    /*
     * PB6 = SCL
     * PB7 = SDA
     */

    GPIO_InitStruct.Pin =
        GPIO_PIN_6 |
        GPIO_PIN_7;

    GPIO_InitStruct.Mode =
        GPIO_MODE_AF_OD;

    GPIO_InitStruct.Pull =
        GPIO_PULLUP;

    GPIO_InitStruct.Speed =
        GPIO_SPEED_FREQ_HIGH;


    HAL_GPIO_Init(
        GPIOB,
        &GPIO_InitStruct
    );


    /*
     * I2C1
     */

    hi2c1.Instance =
        I2C1;

    hi2c1.Init.ClockSpeed =
        100000;

    hi2c1.Init.DutyCycle =
        I2C_DUTYCYCLE_2;

    hi2c1.Init.OwnAddress1 =
        0;

    hi2c1.Init.AddressingMode =
        I2C_ADDRESSINGMODE_7BIT;

    hi2c1.Init.DualAddressMode =
        I2C_DUALADDRESS_DISABLE;

    hi2c1.Init.OwnAddress2 =
        0;

    hi2c1.Init.GeneralCallMode =
        I2C_GENERALCALL_DISABLE;

    hi2c1.Init.NoStretchMode =
        I2C_NOSTRETCH_DISABLE;


    HAL_I2C_Init(&hi2c1);
}


/* =====================================================
   THERMAL DETECTOR
   ===================================================== */

void ThermalDetector(
    float temperature
)
{
    /*
     * Turn everything OFF first
     */

    All_Outputs_OFF();


    /* =========================
       NORMAL
       ========================= */

    if(temperature < 37.5)
    {
        Green_LED_ON();

        UART_SendStatus(
            "NORMAL"
        );
    }


    /* =========================
       WARNING
       ========================= */

    else if(temperature < 38.5)
    {
        Blue_LED_ON();

        UART_SendStatus(
            "WARNING"
        );
    }


    /* =========================
       HIGH TEMPERATURE
       ========================= */

    else
    {
        Red_LED_ON();

        Buzzer_ON();

        UART_SendStatus(
            "HIGH TEMPERATURE"
        );
    }
}


/* =====================================================
   SIMULATED TEMPERATURE
   ===================================================== */

float temperature = 36.0;

int temperatureDirection = 1;


/* =====================================================
   SETUP
   ===================================================== */

void setup()
{
    /*
     * Initialize LEDs and buzzer
     */

    EnablePin_Init();


    /*
     * Initialize I2C
     */

    OLED_I2C_Init();


    /*
     * Initialize OLED
     */

    OLED_Init();

    OLED_Clear();


    /*
     * Initialize UART
     */

    UART_Init();


    /*
     * Startup message
     */

    UART_SendString(
        "\r\n"
        "==============================\r\n"
        "    STM32 THERMAL DETECTOR\r\n"
        "==============================\r\n"
    );


    UART_SendString(
        "Mode: SIMULATED SENSOR\r\n"
    );


    UART_SendString(
        "Green  = NORMAL\r\n"
    );

    UART_SendString(
        "Blue   = WARNING\r\n"
    );

    UART_SendString(
        "Red    = HIGH TEMPERATURE\r\n"
    );

    UART_SendString(
        "Buzzer = HIGH TEMPERATURE\r\n\r\n"
    );


    delay(500);
}


/* =====================================================
   LOOP
   ===================================================== */

void loop()
{
    /*
     * Increase/decrease simulated temperature
     */

    temperature =
        temperature +
        (0.1 * temperatureDirection);


    /*
     * Maximum
     */

    if(temperature >= 40.0)
    {
        temperatureDirection = -1;
    }


    /*
     * Minimum
     */

    if(temperature <= 36.0)
    {
        temperatureDirection = 1;
    }


    /*
     * Thermal detection
     */

    ThermalDetector(
        temperature
    );


    /*
     * OLED display
     */

    OLED_ShowTemperature(
        temperature
    );


    /*
     * UART
     */

    UART_SendTemperature(
        temperature
    );


    /*
     * One second delay
     */

    delay(1000);
}