/*
 * Duc Ngo
 * Implementation of LED driver
 */

#include "led.h"
#include <stdint.h>

void initialize_green_led() {
	DDR(LED_PORT) |= (1<<GREEN_LED_LOC);
}

void initialize_red_led() {
	DDR(LED_PORT) |= (1<<RED_LED_LOC);
}

void turn_on_green_led() {
	PORT(LED_PORT) |= (1<<GREEN_LED_LOC);
}

void turn_off_green_led() {
	PORT(LED_PORT) &= ~(1<<GREEN_LED_LOC);
}

void turn_on_red_led() {
	PORT(LED_PORT) |= (1<<RED_LED_LOC);
}

void turn_off_red_led() {
	PORT(LED_PORT) &= ~(1<<RED_LED_LOC);
}

void toggle_green_led() {
	PORT(LED_PORT) ^= (1<<GREEN_LED_LOC);
}

void toggle_red_led() {
	PORT(LED_PORT) ^= (1<<RED_LED_LOC);
}