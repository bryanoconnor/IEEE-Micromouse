/*
 * Duc Ngo
 * Implementation of motor driver
 */

#include "motor.h"
#include <stdint.h>

#define COMxA1 7
#define COMxA0 6 
#define COMxB1 5
#define COMxB0 4

void initialize_left_motor() {
	set_left_motor_duty_cycle(0x80);
	brake_left_motor();
	DDR(LEFT_MOTOR_CONTROL_A_PORT) |= (1<<LEFT_MOTOR_CONTROL_A_LOC);
	DDR(LEFT_MOTOR_CONTROL_B_PORT) |= (1<<LEFT_MOTOR_CONTROL_B_LOC);
	TCCRA(LEFT_MOTOR_TIMER) = 0x03;
	TCCRB(LEFT_MOTOR_TIMER) = 0x01;
}
void brake_left_motor() {
	TCCRA(LEFT_MOTOR_TIMER) &= ~((1<<COMxA1) | (1<<COMxA0) | (1<<COMxB1) | (1<<COMxB0));
	PORT(LEFT_MOTOR_CONTROL_A_PORT) |= (1<<LEFT_MOTOR_CONTROL_A_LOC);
	PORT(LEFT_MOTOR_CONTROL_B_PORT) |= (1<<LEFT_MOTOR_CONTROL_B_LOC);
}
void coast_left_motor() {
	TCCRA(LEFT_MOTOR_TIMER) &= ~((1<<COMxA1) | (1<<COMxA0) | (1<<COMxB1) | (1<<COMxB0));
	PORT(LEFT_MOTOR_CONTROL_A_PORT) &= ~(1<<LEFT_MOTOR_CONTROL_A_LOC);
	PORT(LEFT_MOTOR_CONTROL_B_PORT) &= ~(1<<LEFT_MOTOR_CONTROL_B_LOC);
}
void engage_left_motor_forward() {
	brake_left_motor();
	TCCRA(LEFT_MOTOR_TIMER) |= ((1<<COMxB1) | (1<<COMxB0));
}
void engage_left_motor_reverse() {
	brake_left_motor();
	TCCRA(LEFT_MOTOR_TIMER) |= ((1<<COMxA1) | (1<<COMxA0));
}
void set_left_motor_duty_cycle( uint8_t duty_cycle) {
	OCRA(LEFT_MOTOR_TIMER) = duty_cycle;
	OCRB(LEFT_MOTOR_TIMER) = duty_cycle;
}
uint8_t get_left_motor_duty_cycle() {
	return OCRA(LEFT_MOTOR_TIMER);
}

void initialize_right_motor() {
	set_right_motor_duty_cycle(0x80);
	brake_right_motor();
	DDR(RIGHT_MOTOR_CONTROL_A_PORT) |= (1<<RIGHT_MOTOR_CONTROL_A_LOC);
	DDR(RIGHT_MOTOR_CONTROL_B_PORT) |= (1<<RIGHT_MOTOR_CONTROL_B_LOC);
	TCCRA(RIGHT_MOTOR_TIMER) = 0x03;
	TCCRB(RIGHT_MOTOR_TIMER) = 0x01;
}
void brake_right_motor() {
	TCCRA(RIGHT_MOTOR_TIMER) &= ~((1<<COMxA1) | (1<<COMxA0) | (1<<COMxB1) | (1<<COMxB0));
	PORT(RIGHT_MOTOR_CONTROL_A_PORT) |= (1<<RIGHT_MOTOR_CONTROL_A_LOC);
	PORT(RIGHT_MOTOR_CONTROL_B_PORT) |= (1<<RIGHT_MOTOR_CONTROL_B_LOC);
}
void coast_right_motor() {
	TCCRA(RIGHT_MOTOR_TIMER) &= ~((1<<COMxA1) | (1<<COMxA0) | (1<<COMxB1) | (1<<COMxB0));
	PORT(RIGHT_MOTOR_CONTROL_A_PORT) &= ~(1<<RIGHT_MOTOR_CONTROL_A_LOC);
	PORT(RIGHT_MOTOR_CONTROL_B_PORT) &= ~(1<<RIGHT_MOTOR_CONTROL_B_LOC);
}
void engage_right_motor_forward() {
	brake_right_motor();
	TCCRA(RIGHT_MOTOR_TIMER) |= ((1<<COMxB1) | (1<<COMxB0));
}
void engage_right_motor_reverse() {
	brake_right_motor();
	TCCRA(RIGHT_MOTOR_TIMER) |= ((1<<COMxA1) | (1<<COMxA0));
}
void set_right_motor_duty_cycle( uint8_t duty_cycle) {
	OCRA(RIGHT_MOTOR_TIMER) = duty_cycle;
	OCRB(RIGHT_MOTOR_TIMER) = duty_cycle;
}
uint8_t get_right_motor_duty_cycle() {
	return OCRA(RIGHT_MOTOR_TIMER);
}