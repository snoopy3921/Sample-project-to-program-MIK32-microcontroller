#include "app_cli.h"
#include "app_pwm.h"
#include "mik32_hal_irq.h"
#include <xprintf.h>
#include <stdio.h>
#include <stdlib.h>


TIMER32_HandleTypeDef htimer32_1;
TIMER32_CHANNEL_HandleTypeDef htimer32_channel1;

static uint8_t pwm_stt = 0;
static uint8_t pwm_run = 0;
static const char cmd_init[]       = "-init";
static const char cmd_view[]       = "-view";
static const char cmd_stop[]       = "-stop";
static const char cmd_run[]        = "-run";
static const char cmd_none[]       = "";
static char *  pwm_cmd = cmd_none;

static void pwm_init(void)
{
    //GPIO
    __HAL_PCC_GPIO_0_CLK_ENABLE();
    __HAL_PCC_GPIO_1_CLK_ENABLE();
    __HAL_PCC_GPIO_2_CLK_ENABLE();

    //Timer setup
    htimer32_1.Instance = TIMER32_1;
    htimer32_1.Top = 7543;
    htimer32_1.State = TIMER32_STATE_DISABLE;
    htimer32_1.Clock.Source = TIMER32_SOURCE_TIM2_OSC32K;
    htimer32_1.Clock.Prescaler = 0;
    htimer32_1.InterruptMask = 0;
    htimer32_1.CountMode = TIMER32_COUNTMODE_FORWARD;
    HAL_Timer32_Init(&htimer32_1);

    //Channel setup
    htimer32_channel1.TimerInstance = htimer32_1.Instance;
    htimer32_channel1.ChannelIndex = TIMER32_CHANNEL_1;
    htimer32_channel1.PWM_Invert = TIMER32_CHANNEL_NON_INVERTED_PWM;
    htimer32_channel1.Mode = TIMER32_CHANNEL_MODE_PWM;
    htimer32_channel1.CaptureEdge = TIMER32_CHANNEL_CAPTUREEDGE_RISING;
    htimer32_channel1.OCR = 7544 >> 1;
    htimer32_channel1.Noise = TIMER32_CHANNEL_FILTER_OFF;
    HAL_Timer32_Channel_Init(&htimer32_channel1);
}

cli_status_t pwm_func(int argc, char **argv)
{
    cli_status_t rslt = CLI_OK;

    uint8_t i = 1;
    while (i < argc)
    {
        switch (i)
        {
        case 1:
            if(strcmp(argv[i], cmd_init) == 0)
            {
                pwm_cmd = cmd_init;
                pwm_stt = 1;
            }
            else if(strcmp(argv[i], cmd_view) == 0)
            {
                pwm_cmd = cmd_view;
            }
            else if(strcmp(argv[i], cmd_stop) == 0)
            {
                pwm_cmd = cmd_stop;
                pwm_run = 0;
                pwm_stt = 0;
            }
            else if(strcmp(argv[i], cmd_run) == 0)
            {
                pwm_cmd = cmd_run;
                pwm_run = 1;
            }
            break;
        
        default:
            if(strcmp(pwm_cmd, cmd_init) == 0)
            {
                pwm_init();
                xprintf("PWM Initialized!\r\n");
            }
            else if(strcmp(pwm_cmd, cmd_run) == 0)
            {
                HAL_Timer32_Channel_Enable(&htimer32_channel1);
                HAL_Timer32_Value_Clear(&htimer32_1);
                HAL_Timer32_Start(&htimer32_1);

                HAL_Timer32_Top_Set(&htimer32_1, 3000);
                HAL_Timer32_Channel_OCR_Set(&htimer32_channel1, 1500);
                HAL_Timer32_Value_Clear(&htimer32_1);
                xprintf("PWM is running!\r\n");
            }
            break;
        }

        i++;
        /* code */
    }


    if(!pwm_stt)
    {
        xprintf("PWM is not configured!\r\n");
        return rslt;
    }
    pwm_cmd = cmd_none;
    return rslt;
}

void app_pwm_run(void)
{
    // HAL_IRQ_DisableInterrupts();
    // if(pwm_run)
    // {
    //     HAL_Timer32_Top_Set(&htimer32_1, 3000);
    //     HAL_Timer32_Channel_OCR_Set(&htimer32_channel1, 1500);
    //     HAL_Timer32_Value_Clear(&htimer32_1);
    // }
    // HAL_IRQ_EnableInterrupts();
}