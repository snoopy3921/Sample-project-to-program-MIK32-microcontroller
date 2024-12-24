#include "mik32_hal_timer32.h"
#include "app_cli.h"
#include "xprintf.h"
#include "uart_lib.h"
#include "stdlib.h"
#include "mik32_hal_irq.h"
TIMER32_HandleTypeDef htimer32_1_aaa;
TIMER32_CHANNEL_HandleTypeDef htimer32_channel1_aaa;
TIMER32_CHANNEL_HandleTypeDef htimer32_channel2_aaa;
TIMER32_CHANNEL_HandleTypeDef htimer32_channel3_aaa;
TIMER32_CHANNEL_HandleTypeDef htimer32_channel4_aaa;

void SystemClock_Config(void);
static void Timer32_1_Init(void);
static void Timer32_2_Init(void);
void GPIO_Init();

/*
 * В данном примере демонстрируется работа таймера32.
 * Нулевой канал таймера используется в режиме ШИМ. На Port0_1 генерирует периодичный сигнал (ШИМ)
 * с заполнением 50 %, частота которого задается верхним пределом таймера. Таймер считает от частоты
 * системной шины, поэтому для установки частоты нужно передать по UART0 значение: 
 * top = (частота основного генератора) / (задаваемая частота).
 * 
 * Например, для частоты 100кГц следует отправить "t320\n".
 * 
 * ШИМ работает с каналом 1 2 3 4 
 */

int main()
{

    SystemClock_Config();

    GPIO_Init();

    Timer32_1_Init();

    HAL_Timer32_Value_Clear(&htimer32_1);
    HAL_Timer32_Start(&htimer32_1);

    HAL_Timer32_Channel_Enable(&htimer32_channel1);

    while(1)
    {

    }

}

    app_cli_start();

    

    xprintf("UART init\n");





    // HAL_Timer32_Top_Set(&htimer32_1_aaa, 3000);
    // HAL_Timer32_Channel_OCR_Set(&htimer32_channel1_aaa, 3000 >> 1);
    // HAL_Timer32_Value_Clear(&htimer32_1_aaa); 




    // if (HAL_Timer32_Compare_Start_IT(&htimer32_1_aaa, &htimer32_channel1_aaa) != HAL_OK)
    // {
    //     xprintf("Error\n");
    // }
    // HAL_EPIC_MaskLevelSet(TIMER32_INT_OC_M(TIMER32_CHANNEL_0));
    // HAL_IRQ_EnableInterrupts();


    // HAL_DelayMs(1);
    // HAL_Timer32_Channel_Enable(&htimer32_channel2_aaa);
    // HAL_DelayMs(1);
    // HAL_Timer32_Channel_Enable(&htimer32_channel3_aaa);
    // HAL_DelayMs(1);
    // HAL_Timer32_Channel_Enable(&htimer32_channel4_aaa);

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
    PCC_OscInit.LSI32KCalibrationValue = 8;
    PCC_OscInit.RTCClockSelection = PCC_RTC_CLOCK_SOURCE_AUTO;
    PCC_OscInit.RTCClockCPUSelection = PCC_CPU_RTC_CLOCK_SOURCE_OSC32K;
    HAL_PCC_Config(&PCC_OscInit);
}


static void Timer32_1_Init(void)
{
    htimer32_1.Instance = TIMER32_1;
    htimer32_1.Top = 15;
    htimer32_1.State = TIMER32_STATE_DISABLE;
    htimer32_1.Clock.Source = TIMER32_SOURCE_PRESCALER;
    htimer32_1.Clock.Prescaler = 0;
    htimer32_1.InterruptMask = 0; 
    htimer32_1.CountMode = TIMER32_COUNTMODE_FORWARD;
    HAL_Timer32_Init(&htimer32_1);

    htimer32_channel1.TimerInstance = htimer32_1.Instance;
    htimer32_channel1.ChannelIndex = TIMER32_CHANNEL_0;
    htimer32_channel1.PWM_Invert = TIMER32_CHANNEL_NON_INVERTED_PWM;
    htimer32_channel1.Mode = TIMER32_CHANNEL_MODE_PWM;
    htimer32_channel1.CaptureEdge = TIMER32_CHANNEL_CAPTUREEDGE_RISING;
    htimer32_channel1.OCR = 5;
    htimer32_channel1.Noise = TIMER32_CHANNEL_FILTER_OFF;
    HAL_Timer32_Channel_Init(&htimer32_channel1);
}



    htimer32_channel2_aaa.TimerInstance = htimer32_1_aaa.Instance;
    htimer32_channel2_aaa.ChannelIndex = TIMER32_CHANNEL_1;
    htimer32_channel2_aaa.PWM_Invert = TIMER32_CHANNEL_NON_INVERTED_PWM;
    htimer32_channel2_aaa.Mode = TIMER32_CHANNEL_MODE_PWM;
    htimer32_channel2_aaa.CaptureEdge = TIMER32_CHANNEL_CAPTUREEDGE_RISING;
    htimer32_channel2_aaa.OCR = 12000;
    htimer32_channel2_aaa.Noise = TIMER32_CHANNEL_FILTER_OFF;
    HAL_Timer32_Channel_Init(&htimer32_channel2_aaa);

    htimer32_channel3_aaa.TimerInstance = htimer32_1_aaa.Instance;
    htimer32_channel3_aaa.ChannelIndex = TIMER32_CHANNEL_2;
    htimer32_channel3_aaa.PWM_Invert = TIMER32_CHANNEL_NON_INVERTED_PWM;
    htimer32_channel3_aaa.Mode = TIMER32_CHANNEL_MODE_PWM;
    htimer32_channel3_aaa.CaptureEdge = TIMER32_CHANNEL_CAPTUREEDGE_RISING;
    htimer32_channel3_aaa.OCR = 18000;
    htimer32_channel3_aaa.Noise = TIMER32_CHANNEL_FILTER_OFF;
    HAL_Timer32_Channel_Init(&htimer32_channel3_aaa);

    htimer32_channel4_aaa.TimerInstance = htimer32_1_aaa.Instance;
    htimer32_channel4_aaa.ChannelIndex = TIMER32_CHANNEL_3;
    htimer32_channel4_aaa.PWM_Invert = TIMER32_CHANNEL_NON_INVERTED_PWM;
    htimer32_channel4_aaa.Mode = TIMER32_CHANNEL_MODE_PWM;
    htimer32_channel4_aaa.CaptureEdge = TIMER32_CHANNEL_CAPTUREEDGE_RISING;
    htimer32_channel4_aaa.OCR = 24000;
    htimer32_channel4_aaa.Noise = TIMER32_CHANNEL_FILTER_OFF;
    HAL_Timer32_Channel_Init(&htimer32_channel4_aaa);
}
static void Timer32_2_Init(void)
{

}


void GPIO_Init()
{
    __HAL_PCC_GPIO_0_CLK_ENABLE();
    __HAL_PCC_GPIO_1_CLK_ENABLE();
    __HAL_PCC_GPIO_2_CLK_ENABLE();
}

int i = 0;
void trap_handler(void)
{
    if (EPIC_CHECK_TIMER32_1())
    {
        uint32_t interrupt_status = HAL_Timer32_InterruptFlags_Get(&htimer32_1_aaa);
        uint32_t interrupt_mask = htimer32_1_aaa.Instance->INT_MASK;

        if ((interrupt_status & TIMER32_INT_OC_M(htimer32_channel1_aaa.ChannelIndex)) & interrupt_mask)
        {
            xprintf("\nCOMPARE_IRQ\n");
            /* code */
            if(i < 3)
            {
                switch (i)
                {
                case 0:
                    HAL_Timer32_Channel_Enable(&htimer32_channel2_aaa);
                    break;
                case 1:
                    HAL_Timer32_Channel_Enable(&htimer32_channel3_aaa);
                    break;
                case 2:
                    HAL_Timer32_Channel_Enable(&htimer32_channel4_aaa);
                    break;
                default:
                    break;
                }
                i++;
            }
            else HAL_Timer32_InterruptMask_Clear(&htimer32_1_aaa, TIMER32_INT_OC_M(TIMER32_CHANNEL_0));
        }

        HAL_TIMER32_INTERRUPTFLAGS_CLEAR(&htimer32_1_aaa); /* Сброс всех флагов */

    }

}