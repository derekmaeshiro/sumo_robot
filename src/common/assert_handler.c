#include "../common/assert_handler.h"
#include "defines.h"
#include <msp430.h>

#define BREAKPOINT __asm volatile("CLR.B R3");

void assert_handler(void)
{
    // TODO: Turn off motors ("safe state")
    // TODO: Trace to console

    BREAKPOINT

    P1SEL &= ~(BIT0);
    P1SEL2 &= ~(BIT0);
    P1DIR |= BIT0;
    P1REN &= ~(BIT0);

    // Configure TEST LED pin on NSUMO
    P2SEL &= ~(BIT6);
    P2SEL2 &= ~(BIT6);
    P2DIR |= BIT6;
    P2REN &= ~(BIT6);

    while (1) {
        P1OUT ^= BIT0;
        P2OUT ^= BIT6;
        BUSY_WAIT_ms(100); // takes miliseconds
    }
}