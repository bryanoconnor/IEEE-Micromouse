/*
 * Duc Ngo
 * Interface definition for motor driver
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "port_macros.h"
#include <avr/io.h>
#include <stdint.h>

#define LEFT_MOTOR_CONTROL_A_PORT D
#define LEFT_MOTOR_CONTROL_B_PORT D
#define LEFT_MOTOR_CONTROL_A_LOC 5
#define LEFT_MOTOR_CONTROL_B_LOC 6
#define LEFT_MOTOR_TIMER 0

#define RIGHT_MOTOR_CONTROL_A_PORT D
#define RIGHT_MOTOR_CONTROL_B_PORT B
#define RIGHT_MOTOR_CONTROL_A_LOC 3
#define RIGHT_MOTOR_CONTROL_B_LOC 3
#define RIGHT_MOTOR_TIMER 2

#define _100_SPEED 0xFF
#define _90_SPEED 0xDF
#define _75_SPEED 0xC0
#define _50_SPEED 0x80
#define _25_SPEED 0x40
#define _22_SPEED 0x3A
#define _20_SPEED 0x35
#define _18_SPEED 0x30
#define _15_SPEED 0x27
#define _10_SPEED 0x1A


void initialize_left_motor();
void brake_left_motor();
void coast_left_motor();
void engage_left_motor_forward();
void engage_left_motor_reverse();
void set_left_motor_duty_cycle( uint8_t duty_cycle);
uint8_t get_left_motor_duty_cycle();

void initialize_right_motor();
void brake_right_motor();
void coast_right_motor();
void engage_right_motor_forward();
void engage_right_motor_reverse();
void set_right_motor_duty_cycle( uint8_t duty_cycle);
uint8_t get_right_motor_duty_cycle();

#endif