#include <stdint.h>
#include "mcu_init.h"
#include "io.h"
#include "../common/defines.h"
#include <msp430.h>

static void watchdog_stop(void)
{
    WDTCTL = WDTPW + WDTHOLD; // stop watchdog
}

void mcu_init(void)
{
    watchdog_stop();
    io_init();
}