# STM32 Blue Pill Thermal Sensor & Threshold Monitor

An embedded C/C++ project developed and simulated on [Wokwi](https://wokwi.com) using the **STM32F103C8T6 (Blue Pill)** microcontroller, a non-contact infrared thermal sensor (**GY-906 MLX90614**), a 0.96-inch monochrome **SSD1306 I²C OLED display**, threshold indicator LEDs, and an active buzzer.

---

## 📌 Project Overview

This system monitors ambient and object temperatures in real-time. Based on configurable temperature thresholds, it triggers visual feedback (OLED screen updates and LEDs) and audible alerts (active buzzer).

### 🔑 Key Features
* **Non-Contact Temperature Sensing:** Reads target object temperature and ambient temperature via I²C interface.
* **Monochrome OLED Interface:** Real-time display of temperature readings (°C), status tags (`[NORMAL]`, `[WARM]`, `[HIGH]`), and a graphical progress gauge.
* **Multi-Stage Threshold Alerts:**
  * **Normal Range:** Green LED ON, Buzzer OFF.
  * **Warning/Warm Range:** Blue LED ON, Buzzer OFF.
  * **High Temperature/Alarm:** Red LED ON, Active Buzzer sound.
* **Modular Code Structure:** Uses standard C header files (`app_uart.h`, `enablePin.h`, etc.) for peripheral management.

---

## 🛠️ Component & Hardware List

| Component | Description / Model | Interface / Connection |
| :--- | :--- | :--- |
| **Microcontroller** | STM32F103C8T6 (Blue Pill) | Main Controller |
| **Thermal Sensor** | GY-906 (MLX90614ESF-BCC) | I²C (SCL/SDA) |
| **OLED Display** | 0.96" SSD1306 (128x64) | I²C (SCL/SDA) |
| **Green LED** | Normal Threshold Indicator | GPIO Pin (with current-limiting resistor) |
| **Blue LED** | Warning Threshold Indicator | GPIO Pin (with current-limiting resistor) |
| **Red LED** | High Temp Alarm Indicator | GPIO Pin (with current-limiting resistor) |
| **Buzzer** | 5V Active Buzzer | GPIO Pin |
| **Resistors** | 220Ω / 330Ω | Current limiting for LEDs |

---

## 🔌 Pin Connections & Wiring Diagram

The physical and simulated connections (as defined in `diagram.json` for Wokwi) are wired as follows:

```text
STM32F103C8T6 Blue Pill
 ├── I2C Pins (Bus 1)
 │    ├── PB6 (SCL)  ────────► MLX90614 SCL & SSD1306 OLED SCL
 │    └── PB7 (SDA)  ────────► MLX90614 SDA & SSD1306 OLED SDA
 ├── Output Pins
 │    ├── PA0        ────────► Green LED (Anode via resistor)
 │    ├── PA1        ────────► Blue LED (Anode via resistor)
 │    ├── PA2        ────────► Red LED (Anode via resistor)
 │    └── PA3        ────────► Active Buzzer (+ Pin)
 └── Power & Ground
      ├── 3.3V / 5V  ────────► VCC (Sensors, OLED, Buzzer)
      └── GND        ────────► GND (Common Ground)



To View : https://wokwi.com/projects/476828600027886593
