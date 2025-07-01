#include <msp430.h>
#include "../drivers/io.h"
#include "../drivers/led.h"
#include "../drivers/mcu_init.h"
#include "../common/assert_handler.h"
#include "../common/defines.h"

static void test_setup(void)
{
    mcu_init();
}

/*
static void test_assert(void)
{
    test_setup();
    ASSERT(0);
}
*/

static void test_blink_led(void)
{
    test_setup();
    led_init();
    led_state_e led_state = LED_STATE_OFF;
    while (1) {
        led_state = (led_state == LED_STATE_OFF) ? LED_STATE_ON : LED_STATE_OFF;
        led_set(LED_TEST, led_state);
        BUSY_WAIT_ms(1000);
    }
}

/*
static void test_launchpad_io_pins_output(void)
{
     test_setup();
     const struct io_config output_config = { .select = IO_SELECT_GPIO,
                                              .resistor = IO_RESISTOR_DISABLED,
                                              .out = IO_OUT_LOW,
                                              .dir = IO_DIR_OUTPUT};

     // Configure all pins as output
     for (io_generic_e io = IO_10; io <= IO_27; io++) {
          io_configure(io, &output_config);
     }
     while (1) {
          for (io_generic_e io = IO_10; io <= IO_27; io++) {
               io_set_out(io, IO_OUT_HIGH);
               BUSY_WAIT_ms(100);
               io_set_out(io, IO_OUT_LOW);
          }
     }
}
*/

/*
static void test_launchpad_io_pins_input(void)
{
    test_setup();
    led_init();

    const struct io_config input_config = {
        .select = IO_SELECT_GPIO,
        .resistor = IO_RESISTOR_ENABLED,
        .dir = IO_DIR_INPUT,
        .out = IO_OUT_HIGH // pull-up
    };

    // Configure all pins as input
    for (io_generic_e io = IO_10; io <= IO_27; io++) {
        io_configure(io, &input_config);
    }

    for (io_generic_e io = IO_10; io <= IO_27; io++) {
        if (io == (io_generic_e)IO_TEST_LED) {
            continue;
        }

        led_set(LED_TEST, LED_STATE_ON);

        while (io_get_input(io) == IO_IN_HIGH) {
            BUSY_WAIT_ms(100);
        }

        led_set(LED_TEST, LED_STATE_OFF);

        while (io_get_input(io) == IO_IN_LOW) {
            BUSY_WAIT_ms(100);
        }
    }

    // Blink LED when test is done
    while (1) {
        led_set(LED_TEST, LED_STATE_ON);
        BUSY_WAIT_ms(500);
        led_set(LED_TEST, LED_STATE_OFF);
        BUSY_WAIT_ms(2000);
    }
}
*/

int main(void)
{
    // test_assert();
    test_blink_led();
    // test_launchpad_io_pins_output();
    // test_launchpad_io_pins_input();
    return 0;
}
