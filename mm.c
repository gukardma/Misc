//////////////////////////////////////////////////
// Documentation:
// https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/api-reference/peripherals/gpio.html
// https://docs.espressif.com/projects/esp-idf/en/v4.3/esp32/api-reference/system/log.html
//////////////////////////////////////////////////
// Anecdotes
// https://github.com/espressif/esp-idf/blob/master/examples/peripherals/gpio/generic_gpio/main/gpio_example_main.c
// https://www.youtube.com/watch?v=KZVXQfy3is8
//////////////////////////////////////////////////

/*
helpful stuff ^^
*/

#include <stdio.h>

#include "driver\gpio.h"
#include "freeRTOS\freeRTOS.h"
#include "freeRTOS\task.h"

#include "esp_log.h"

// 1ULL represents an 'unsigned long long' which is used to create a bitmask that can represent up to 64 GPIO pins.
// bitmasks are lists of boolean flags compressed into a single field
#define HOUSE_LEDS ((1ULL << GPIO_NUM_12) | (1ULL << GPIO_NUM_13) | (1ULL << GPIO_NUM_14) | (1ULL << GPIO_NUM_26) | (1ULL << GPIO_NUM_27))

#define LDR_PIN GPIO_NUM_34

void configure_gpios()
{
    // initialize the config structure
    gpio_config_t io_cfg = {};
    // set as output mode
    io_cfg.mode = GPIO_MODE_OUTPUT;
    // bit mask fo the pins to be set
    io_cfg.pin_bit_mask = HOUSE_LEDS;
    // configure GPIO with the given settings
    gpio_config(&io_cfg);

    // ESP32 pins are multiplexed (UART,SPI,I2C,ADC,etc.) this configures the pin specifically for GPIO uses
    gpio_pad_select_gpio(GPIO_NUM_27);
    // sets direction
    gpio_set_direction(GPIO_NUM_27, GPIO_MODE_INPUT);
}

void app_main(void)
{
    configure_gpios();

    const int threshold = 600;
    int ldrValue = 0;

    while (true)
    {
        ldrValue = gpio_get_level(LDR_PIN);

        ESP_LOGI(LDR_PIN, "LDR_Value: %d", ldrValue);

        (ldrValue < threshold) ? gpio_set_level(HOUSE_LEDS, 1) : gpio_set_level(HOUSE_LEDS, 0);

        vTaskDelay(500);
    }
}