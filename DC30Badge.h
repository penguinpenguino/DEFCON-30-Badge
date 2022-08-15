#pragma once

// Stuff for the DEFCON 30 badge

// define NO_BOOTLOADER to torture yourself (require shorting of J1 to access bootloader)

#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

#define LED_R 24 // Note: These are GPIO #'s, not pin #'s
#define LED_G 25
#define LED_B 26
#define BTN_UP 15
#define BTN_DOWN 16
#define BTN_LEFT 17
#define BTN_RIGHT 18
#define VOL_UP 27
#define VOL_DOWN 28
#define SCREENPOW 19
#define SCREEN1 20
#define SCREEN2 21

// Forward declarations

void init(); // MUST CALL INIT FIRST!!!
bool IsDown(int button);
void LED(int r, int g, int b);



ssd1306_t Screen;

void init() {
    gpio_init(BTN_UP); // Buttons
    gpio_init(BTN_DOWN);
    gpio_init(BTN_LEFT);
    gpio_init(BTN_RIGHT);
    gpio_init(VOL_UP);
    gpio_init(VOL_DOWN);
    gpio_set_dir(BTN_UP, GPIO_IN);
    gpio_set_dir(BTN_DOWN, GPIO_IN);
    gpio_set_dir(BTN_LEFT, GPIO_IN);
    gpio_set_dir(BTN_RIGHT, GPIO_IN);
    gpio_set_dir(VOL_UP, GPIO_IN);
    gpio_set_dir(VOL_DOWN, GPIO_IN);
    gpio_set_input_enabled(BTN_UP, true);
    gpio_set_input_enabled(BTN_DOWN, true);
    gpio_set_input_enabled(BTN_LEFT, true);
    gpio_set_input_enabled(BTN_RIGHT, true);
    gpio_set_input_enabled(VOL_UP, true);
    gpio_set_input_enabled(VOL_DOWN, true);
    gpio_pull_up(BTN_DOWN);
    gpio_pull_up(BTN_LEFT);
    gpio_pull_up(BTN_RIGHT);
    gpio_pull_up(BTN_UP);
    gpio_pull_up(VOL_UP);
    gpio_pull_up(VOL_DOWN);

#ifndef NO_BOOTLOADER
    sleep_ms(10);
    if (IsDown(BTN_DOWN)) {
        reset_usb_boot(0, 0);
    }
#endif

    gpio_init(LED_R); // LEDs
    gpio_init(LED_G);
    gpio_init(LED_B);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_put(LED_R, 1);
    gpio_put(LED_G, 1);
    gpio_put(LED_B, 1);

    gpio_init(SCREENPOW); // Screen
    gpio_set_dir(SCREENPOW, GPIO_OUT);
    gpio_put(SCREENPOW, 1);
    stdio_init_all();
    i2c_init(i2c0, 400000);
    gpio_set_function(SCREEN1, GPIO_FUNC_I2C);
    gpio_set_function(SCREEN2, GPIO_FUNC_I2C);
    gpio_pull_up(SCREEN1);
    gpio_pull_up(SCREEN2);
    Screen.external_vcc = false;
    ssd1306_init(&Screen, 128, 64, 0x3C, i2c0);
    ssd1306_clear(&Screen);
}

void LED(int r, int g, int b) {
    gpio_put(LED_R, 1 - r);
    gpio_put(LED_G, 1 - g);
    gpio_put(LED_B, 1 - b);
}

bool IsDown(int button) {
    return !gpio_get(BTN_DOWN);
}