
# Embedded Peripheral Drivers for STM32F4xx

## Overview
This project provides **bare-metal peripheral drivers** for STM32F4xx microcontrollers, implemented from scratch **without using HAL or CMSIS**. The goal is to develop a deeper understanding of low-level embedded programming by directly interacting with hardware registers. This project includes **both polling-based and interrupt-based implementations** for all peripheral drivers, ensuring efficient and responsive communication. **Future plans include implementing DMA-based data transfer** for enhanced performance.

## Features
✔️ **GPIO (General Purpose Input/Output) Driver with Polling and Interrupt Support**  
✔️ **I2C (Inter-Integrated Circuit) Driver with Polling and Interrupt Support**  
✔️ **SPI (Serial Peripheral Interface) Driver with Polling and Interrupt Support**  
✔️ **Bare-metal register-level programming (No HAL, No CMSIS)**  
✔️ **Structured, modular, and reusable driver architecture**  
✔️ **Upcoming: DMA-based data transfer for optimized performance**  


## Project Structure
```
EmbeddedPeripheralDrivers_STM32/
│
├── Src/                # Source files
│   ├── main.c          # Application code
│   ├── gpio_driver.c   # GPIO driver implementation
│   ├── i2c_driver.c    # I2C driver implementation
│   ├── spi_driver.c    # SPI driver implementation
│
├── Inc/                # Header files
│   ├── gpio_driver.h
│   ├── i2c_driver.h
│   ├── spi_driver.h
│
├── Startup/            # Startup assembly file
│   └── startup_stm32f407xx.s
│
├── Linker/             # Linker scripts
│   ├── STM32F407VGTX_FLASH.ld
│   ├── STM32F407VGTX_RAM.ld
│
├── .gitignore
├── README.md           # Project documentation
└── LICENSE             # Project license
```

---

## Getting Started
### Prerequisites
- ✅ **Hardware**: STM32F4 Discovery Board or equivalent  
- ✅ **Toolchain**: ARM GCC Compiler, STM32CubeIDE, or Keil uVision  
- ✅ **Debugger**: ST-Link V2 / Onboard Debugger  

### Setup & Compilation
1. **Clone the Repository**
   ```bash
   git clone https://github.com/bobburudinesh/EmbeddedPeripheralDrivers_STM32.git
   ```
2. **Open the project in STM32CubeIDE / Keil / Any ARM Compiler**  
3. **Build the project** 
4. **Flash the binary to STM32F4 using ST-Link**  
5. **Verify the peripheral functionality**  

---

## Peripheral Driver Implementations
### 1. GPIO Driver
- Configures pin modes, speed, and pull-up/pull-down resistors.
- Example usage:
  ```c
  GPIO_InitTypeDef gpio;
  gpio.pin = GPIO_PIN_13;
  gpio.mode = GPIO_MODE_OUTPUT;
  gpio.speed = GPIO_SPEED_LOW;
  GPIO_Init(GPIOC, &gpio);
  GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  ```

### 2. I2C Driver
- Implements I2C communication using **register-level programming**.
- Example usage:
  ```c
  uint8_t data = 0xAA;
  I2C_MasterTransmit(&i2c, EEPROM_ADDRESS, &data, 1);
  ```

### 3. SPI Driver
- Supports master/slave communication, full-duplex data transmission.
- Example usage:
  ```c
  uint8_t tx_data = 0x55, rx_data;
  SPI_Transmit(&spi, &tx_data, 1);
  SPI_Receive(&spi, &rx_data, 1);
  ```

---

## Example Application
This project includes a **basic GPIO LED blink example** using the custom GPIO driver.

```c
#include "gpio_driver.h"

int main(void) {
    GPIO_InitTypeDef gpio;
    gpio.pin = GPIO_PIN_13;
    gpio.mode = GPIO_MODE_OUTPUT;
    GPIO_Init(GPIOC, &gpio);

    while (1) {
        GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        for (volatile int i = 0; i < 100000; i++); // Delay
    }
}
```

---

## Future Enhancements
🚀 Adding **DMA-based peripheral communication** for optimized performance  
🚀 **Adding UART Driver**  
🚀 **Adding PWM Driver**  
---

## Contributing
Contributions are welcome! To contribute:  
1. Fork the repository  
2. Create a new feature branch  
3. Commit and push your changes  
4. Open a pull request  

---

## License
This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.

