/*
 * Duc Ngo
 * Interface definition for LED driver
 */

#ifndef LED_H
#define LED_H

#include "port_macros.h"
#include <avr/io.h>

#define LED_PORT D
#define GREEN_LED_LOC 7
#define RED_LED_LOC 1

void initialize_green_led();
void initialize_red_led();
void turn_on_green_led();
void turn_off_green_led();
void turn_on_red_led();
void turn_off_red_led();
void toggle_green_led();
void toggle_red_led();

#endif