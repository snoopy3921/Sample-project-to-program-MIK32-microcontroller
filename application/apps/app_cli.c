#include "app_cli.h"
#include "main.h"
#include <xprintf.h>
#include "mik32_hal_irq.h"


USART_HandleTypeDef HUSART0;

static bool console_listening;

static void USART_Init();
static void user_uart_println(char *string);
static void static_send_char(unsigned char c);

cmd_t cmds[3] = {
    {
        .cmd = "help",
        .func = help_func
    },
    {
        .cmd = "ADC",
        .func = adc_func
    },
    {
        .cmd = "PWM",
        .func = pwm_func
    }
};

cli_t cli = {
    .println = user_uart_println,
    .cmd_tbl = cmds,
    .cmd_cnt = sizeof(cmds) / sizeof(cmd_t)
};

void app_cli_start(void)
{
    USART_Init();
    xfunc_out = (void(*)(unsigned char))static_send_char;
    __HAL_PCC_EPIC_CLK_ENABLE();
    HAL_EPIC_MaskLevelSet(HAL_EPIC_UART_0_MASK); 
    HAL_IRQ_EnableInterrupts();
    HAL_USART_RXNE_EnableInterrupt(&HUSART0);
    console_listening = false;


    cli_status_t rslt = CLI_OK;
    if((rslt = cli_init(&cli)) != CLI_OK)
    {
        xprintf("CLI: Failed to initialise");
    }
}
void app_cli_run(void)
{
    cli_process(&cli);
}
bool app_cli_get_stt(void)
{
    return console_listening;
}

cli_status_t help_func(int argc, char **argv)
{
    cli_status_t rslt = CLI_OK;

    /* Code executed when 'help' is entered */
    xprintf("Wait a minute...");
    uint8_t i = 1;
    while (i < argc)
    {
        HAL_USART_Print(&HUSART0, argv[i], USART_TIMEOUT_DEFAULT);
        i++;
        /* code */
    }
    return rslt;
}
void static_send_char(unsigned char c)
{
    HAL_USART_Print(&HUSART0, &c, USART_TIMEOUT_DEFAULT);
}

static void user_uart_println(char *string)
{
    /* For example.. */
    HAL_USART_Print(&HUSART0, string, USART_TIMEOUT_DEFAULT);
    
}
void cli_interrupt()
{
    if (EPIC_CHECK_UART_0())
    {
        /* Прием данных: запись в буфер */
        if (HAL_USART_RXNE_ReadFlag(&HUSART0))
        {
            console_listening = true;
            char c = HAL_USART_ReadByte(&HUSART0);
            cli_put(&cli, c);
            if(c == '\r') console_listening = false;
            HAL_USART_RXNE_ClearFlag(&HUSART0);
        }
    }
   HAL_EPIC_Clear((uint32_t) 1 << 1);
}

static void USART_Init()
{
    HUSART0.Instance = UART_0;
    HUSART0.transmitting = Enable;
    HUSART0.receiving = Enable;
    HUSART0.frame = Frame_8bit;
    HUSART0.parity_bit = Disable;
    HUSART0.parity_bit_inversion = Disable;
    HUSART0.bit_direction = LSB_First;
    HUSART0.data_inversion = Disable;
    HUSART0.tx_inversion = Disable;
    HUSART0.rx_inversion = Disable;
    HUSART0.swap = Disable;
    HUSART0.lbm = Disable;
    HUSART0.stop_bit = StopBit_1;
    HUSART0.mode = Asynchronous_Mode;
    HUSART0.xck_mode = XCK_Mode3;
    HUSART0.last_byte_clock = Disable;
    HUSART0.overwrite = Disable;
    HUSART0.rts_mode = AlwaysEnable_mode;
    HUSART0.dma_tx_request = Disable;
    HUSART0.dma_rx_request = Disable;
    HUSART0.channel_mode = Duplex_Mode;
    HUSART0.tx_break_mode = Disable;
    HUSART0.Interrupt.ctsie = Disable;
    HUSART0.Interrupt.eie = Disable;
    HUSART0.Interrupt.idleie = Disable;
    HUSART0.Interrupt.lbdie = Disable;
    HUSART0.Interrupt.peie = Disable;
    HUSART0.Interrupt.rxneie = Disable;
    HUSART0.Interrupt.tcie = Disable;
    HUSART0.Interrupt.txeie = Disable;
    HUSART0.Modem.rts = Disable; //out
    HUSART0.Modem.cts = Disable; //in
    HUSART0.Modem.dtr = Disable; //out
    HUSART0.Modem.dcd = Disable; //in
    HUSART0.Modem.dsr = Disable; //in
    HUSART0.Modem.ri = Disable;  //in
    HUSART0.Modem.ddis = Disable;//out
    HUSART0.baudrate = 9600;
    HAL_USART_Init(&HUSART0);
}
