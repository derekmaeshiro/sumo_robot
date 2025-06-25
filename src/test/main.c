#include <msp430.h>
#include "../drivers/io.h"
#include "../drivers/mcu_init.h"

static void test_setup(void)
{
     mcu_init();
}

/*
static void test_blink_led(void)
{
     test_setup();
     const struct io_config led_config =
     {
          .dir = IO_DIR_OUTPUT,
          .select = IO_SELECT_GPIO,
          .resistor = IO_RESISTOR_DISABLED,
          .out = IO_OUT_LOW
     };
     io_configure(IO_TEST_LED, &led_config);
     io_out_e out = IO_OUT_LOW;
     while(1) {
          out = (out == IO_OUT_LOW) ? IO_OUT_HIGH : IO_OUT_LOW;
          io_set_out(IO_TEST_LED, out);
          __delay_cycles(250000); //delay
     }
}
*/

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
               __delay_cycles(10000);
               io_set_out(io, IO_OUT_LOW);
          }
     }
}
*/

static void test_launchpad_io_pins_input(void)
{
     test_setup();
     const struct io_config input_config = {
          .select = IO_SELECT_GPIO,
          .resistor = IO_RESISTOR_ENABLED,
          .dir = IO_DIR_INPUT,
          .out = IO_OUT_HIGH // pull-up
     };

     const struct io_config led_config = { .select = IO_SELECT_GPIO,
                                           .resistor = IO_RESISTOR_DISABLED,
                                           .dir = IO_DIR_OUTPUT,
                                           .out = IO_OUT_LOW };

     const io_generic_e io_led = IO_10;

     // Configure all pins as input
     for (io_generic_e io = IO_10; io <= IO_27; io++) {
          io_configure(io, &input_config);
     }

     io_configure(io_led, &led_config);

     for (io_generic_e io = IO_10; io <= IO_27; io++) {
          if (io == io_led) {
               continue;
          }
          io_set_out(io_led, IO_OUT_HIGH);
          
          while(io_get_input(io) == IO_IN_HIGH) {
               __delay_cycles(100000); // 100 ms
          }
          io_set_out(io_led, IO_OUT_LOW);

          while (io_get_input(io) == IO_IN_LOW) {
               __delay_cycles(100000); // 100 ms
          }
     }

     // Blink LED when test is done
     while (1) {
          io_set_out(io_led, IO_OUT_HIGH);
          __delay_cycles(500000); // 500 ms
          io_set_out(io_led, IO_OUT_LOW);
          __delay_cycles(2000000); // 2000 ms
     }
}

int main(void)
{
     WDTCTL = WDTPW + WDTHOLD;
     // test_blink_led();
     // test_launchpad_io_pins_output();
     test_launchpad_io_pins_input();
     return 0;
}
