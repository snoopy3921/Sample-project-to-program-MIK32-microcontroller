#include "main.h"
#include "app_cli.h"
#include "app_adc.h"
#include "app_pwm.h"
#include "mik32_hal_scr1_timer.h"

SPI_HandleTypeDef HSPI1;
static volatile uint32_t millis_now;


void SystemClock_Config(void);


int main()
{
    HAL_Init();
    SystemClock_Config();
    HAL_Time_SCR1TIM_Init();
    app_cli_start();

    __HAL_PCC_GPIO_2_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitTypeDef_User;
    GPIO_InitTypeDef_User.Pin = GPIO_PIN_7;
    GPIO_InitTypeDef_User.Mode = HAL_GPIO_MODE_GPIO_OUTPUT;
    GPIO_InitTypeDef_User.Pull = HAL_GPIO_PULL_NONE;

    HAL_GPIO_Init(GPIO_2, &GPIO_InitTypeDef_User);

    millis_now = HAL_Millis();
    while(1)
    {
        if(HAL_Millis() < millis_now ) millis_now = HAL_Millis(); //Overflow
        if(HAL_Millis() - millis_now > 10)
        {
            HAL_GPIO_TogglePin(GPIO_2, GPIO_PIN_7);
            if(!app_cli_get_stt()) app_adc_run();
            millis_now = HAL_Millis();
        }
        app_pwm_run();
        app_cli_run();
    }
}



void SystemClock_Config(void)
{
    PCC_InitTypeDef PCC_OscInit = {0};
    PCC_OscInit.OscillatorEnable = PCC_OSCILLATORTYPE_ALL;
    PCC_OscInit.FreqMon.OscillatorSystem = PCC_OSCILLATORTYPE_OSC32M;
    PCC_OscInit.FreqMon.ForceOscSys = PCC_FORCE_OSC_SYS_UNFIXED;
    PCC_OscInit.FreqMon.Force32KClk = PCC_FREQ_MONITOR_SOURCE_OSC32K;
    PCC_OscInit.AHBDivider = 0;
    PCC_OscInit.APBMDivider = 0;
    PCC_OscInit.APBPDivider = 0;
    PCC_OscInit.HSI32MCalibrationValue = 128;
    PCC_OscInit.LSI32KCalibrationValue = 128;
    PCC_OscInit.RTCClockSelection = PCC_RTC_CLOCK_SOURCE_AUTO;
    PCC_OscInit.RTCClockCPUSelection = PCC_CPU_RTC_CLOCK_SOURCE_OSC32K;
    HAL_PCC_Config(&PCC_OscInit);
}


uint32_t HAL_Millis()
{
    return HAL_Time_SCR1TIM_Millis();
}

void trap_handler(void)
{
    cli_interrupt();
}