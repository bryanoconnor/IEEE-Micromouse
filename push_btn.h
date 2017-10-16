/*
 * Duc Ngo
 * Interface definition for push button driver
 */

#ifndef PUSHBTN_H
#define PUSHBTN_H

#include "port_macros.h"
#include <stdbool.h>
#include <avr/io.h>

#define PUSH_BTN_PORT B
#define LEFT_BTN_LOC 1
#define MIDDLE_BTN_LOC 4
#define RIGHT_BTN_LOC 5

void initialize_push_btn_array();
bool left_btn_is_pressed();
bool middle_btn_is_pressed();
bool right_btn_is_pressed();
bool any_btn_is_pressed();

#endif