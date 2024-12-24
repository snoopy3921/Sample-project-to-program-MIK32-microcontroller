#include "cli.h"
#include <mik32_hal_usart.h>


extern USART_HandleTypeDef HUSART0;

extern cmd_t cmds[3];

extern cli_status_t pwm_func(int argc, char **argv);
extern cli_status_t adc_func(int argc, char **argv);
extern cli_status_t help_func(int argc, char **argv);


extern void app_cli_start(void);
extern void app_cli_run(void);
extern bool app_cli_get_stt(void);
extern void cli_interrupt(void);