#include "app_cli.h"
#include "app_adc.h"
#include "mik32_hal_irq.h"
#include <xprintf.h>
#include <stdio.h>
#include <stdlib.h>


ADC_HandleTypeDef HADC;

enum
{
    ADC_NOT_INIT    = 1 << 0,
    ADC_CH0_READY   = 1 << 1,
    ADC_CH1_READY   = 1 << 2,
    ADC_CH2_READY   = 1 << 3,
    ADC_CH3_READY   = 1 << 4,
    ADC_CH4_READY   = 1 << 5,
    ADC_CH5_READY   = 1 << 6,
    ADC_CH6_READY   = 1 << 7,
    ADC_CH7_READY   = 1 << 8,
};
static uint8_t adc_stt = 0;
static uint8_t adc_run = 0;
static const char cmd_channel[]    = "-channel";
static const char cmd_view[]       = "-view";
static const char cmd_stop[]       = "-stop";
static const char cmd_run[]        = "-run";
static const char cmd_none[]       = "";
static char *  adc_cmd = cmd_none;

static void ADC_Init(uint8_t channel);

cli_status_t adc_func(int argc, char **argv)
{
    cli_status_t rslt = CLI_OK;

    uint8_t i = 1;
    while (i < argc)
    {
        switch (i)
        {
        case 1:
            if(strcmp(argv[i], cmd_channel) == 0)
            {
                adc_cmd = cmd_channel;
            }
            else if(strcmp(argv[i], cmd_view) == 0)
            {
                adc_cmd = cmd_view;
            }
            else if(strcmp(argv[i], cmd_stop) == 0)
            {
                adc_cmd = cmd_stop;
                adc_run = 0;
                adc_stt = 0;
            }
            else if(strcmp(argv[i], cmd_run) == 0)
            {
                adc_run = 1;
            }
            break;
        
        default:
            if(strcmp(adc_cmd, cmd_channel) == 0)
            {
                if(atoi(argv[i]) < 0 || atoi(argv[i]) > 7) break;
                adc_stt |= ( 1 << (atoi(argv[i]) + 1) );
                ADC_Init(atoi(argv[i]));
                xprintf("ADC is setting channel: %s\r\n", argv[i]);
            }
            if(strcmp(adc_cmd, cmd_view) == 0)
            {
                if(atoi(argv[i]) < 0 || atoi(argv[i]) > 7) break;
                if(strcmp(argv[i], "all") == 0)
                {
                    for(int j = 1; j < 9; j++)
                    {
                        if(adc_stt & (1 << j))
                        {
                            HAL_ADC_SINGLE_AND_SET_CH(HADC.Instance, j-1);
                            xprintf("ADC channel %d value: %d\r\n", j-1, HAL_ADC_WaitAndGetValue(&HADC));
                        }
                    }
                }
                else if(adc_stt & (1 << (atoi(argv[i]) + 1) ))
                {
                    HAL_ADC_SINGLE_AND_SET_CH(HADC.Instance, atoi(argv[i]));
                    xprintf("ADC channel %d value: %d\r\n", atoi(argv[i]), HAL_ADC_WaitAndGetValue(&HADC));
                }
            }
            break;
        }

        i++;
        /* code */
    }
    
    if(!adc_stt)
    {
        xprintf("ADC is not configured!\r\n");
        return rslt;
    }
    adc_cmd = cmd_none;
    return rslt;
}


static void ADC_Init(uint8_t channel)
{
    HADC.Instance = ANALOG_REG;
    HADC.Init.Sel = channel;
    HADC.Init.EXTRef = ADC_EXTREF_OFF;    /* Выбор источника опорного напряжения: «1» - внешний; «0» - встроенный */
    HADC.Init.EXTClb = ADC_EXTCLB_ADCREF; /* Выбор источника внешнего опорного напряжения: «1» - внешний вывод; «0» - настраиваемый ОИН */
    adc_run = 0;
    HAL_ADC_Init(&HADC);    
}

void app_adc_run(void)
{
    HAL_IRQ_DisableInterrupts();
    if(adc_run)
    {
        for(int j = 1; j < 9; j++)
        {
            if(adc_stt & (1 << j))
            {
                HAL_ADC_SINGLE_AND_SET_CH(HADC.Instance, j-1);
                xprintf("ADC channel %d value: %d\r\n", j-1, HAL_ADC_WaitAndGetValue(&HADC));
            }
        }
    }
    HAL_IRQ_EnableInterrupts();
}