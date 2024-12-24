#include <mik32_memory_map.h>
#include <mik32_hal.h>
#include <mik32_hal_pcc.h>
#include <mik32_hal_gpio.h>
#include <mik32_hal_spi.h>
#include <xprintf.h>

#define GPIO_ResetBits(port, pin)   HAL_GPIO_WritePin(port, pin, GPIO_PIN_LOW)
#define GPIO_SetBits(port, pin)     HAL_GPIO_WritePin(port, pin, GPIO_PIN_HIGH)

#define STB_Pin GPIO_PIN_12
#define CLK_Pin GPIO_PIN_11
#define DIO_Pin GPIO_PIN_10


extern SPI_HandleTypeDef HSPI1;


extern void SystemClock_Config(void);
extern void trap_handler(void);
