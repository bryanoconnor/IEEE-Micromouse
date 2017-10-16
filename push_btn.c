/*
 * Duc Ngo
 * Implementation of push button driver
 */

#include "push_btn.h"
#include <stdbool.h>

void initialize_push_btn_array() {
	PULLUP(PUSH_BTN_PORT) |=  ((1<<LEFT_BTN_LOC) | (1<<MIDDLE_BTN_LOC) | (1<<RIGHT_BTN_LOC));
	DDR(PUSH_BTN_PORT) &= ~((1<<LEFT_BTN_LOC) | (1<<MIDDLE_BTN_LOC) | (1<<RIGHT_BTN_LOC));
}

bool left_btn_is_pressed() {
	return (PIN(PUSH_BTN_PORT) & (1<<LEFT_BTN_LOC)) == 0;
}

bool middle_btn_is_pressed() {
	return (PIN(PUSH_BTN_PORT) & (1<<MIDDLE_BTN_LOC)) == 0;
}

bool right_btn_is_pressed() {
	return (PIN(PUSH_BTN_PORT) & (1<<RIGHT_BTN_LOC)) == 0;
}

bool any_btn_is_pressed() {
	return left_btn_is_pressed() || middle_btn_is_pressed() || right_btn_is_pressed();
}
