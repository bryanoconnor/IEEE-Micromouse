/*
 * WCP 07 
 * Micromouse
 */

#include "led.h"
#include "push_btn.h"
#include "motor.h"
#include "OrangutanTime.h"
#include "OrangutanLCD.h"
#include "OrangutanAnalog.h"
#include "IRSensor.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

#define side_reading_null 150
#define side_reading_normal 215
#define side_reading_extremely_low (side_reading_normal-30)
#define side_reading_low (side_reading_normal-10)
#define side_reading_high (side_reading_normal+10)
#define side_reading_extremely_high (side_reading_normal+30)

#define front_reading_high 250
#define front_reading_extremely_high 350

#define reading_buffer_length 5
#define first_half 1
#define second_half 2
 
#define N 1
#define E 2
#define S 4
#define W 8


void init();
void forward_half_cell(uint8_t section);
void turn_left();
void turn_right();
void turn_around();
void undo_by_turning_left();
void undo_by_turning_right();
void get_sensor_reading();
void reset_sensor_reading_after_a_turn();
void restore_sensor_reading();
void update_next_cell_info();
uint8_t has_a_left_wall();
uint8_t has_a_right_wall();
uint8_t has_a_front_wall();
float left_proximity = side_reading_normal;
float right_proximity = side_reading_normal;
float saved_left_proximity, saved_right_proximity;
uint8_t cell_info[reading_buffer_length] = {0,0,0,0,0};


void init() {
	initialize_push_btn_array();
	initialize_green_led();
	initialize_red_led();
	initialize_left_motor();
	initialize_right_motor();
	initialize_IR_sensor();
	set_left_motor_duty_cycle(_20_SPEED);
	set_right_motor_duty_cycle(_20_SPEED);

	clear();

	// Display battery voltage and wait for button press
	while(!middle_btn_is_pressed()) {
		clear();
		print_long(read_battery_millivolts());
		print("mV");
		lcd_goto_xy(0,1);
		print("Press B");
		delay_ms(100);
	}

	clear();
	print("Go!");
	delay_ms(1000);
}

int main() {
	init();
	// ------- Constantly reading Sensor values -------
	/*
	while(1) {
		get_sensor_reading();
		_delay_ms(50);
	}
	*/
	// ------- Move 1 cell ------- 
	/*
	while(1) {
		while(!middle_btn_is_pressed());
		_delay_ms(2000);
		forward_half_cell(second_half);
		forward_half_cell(first_half);
	}
	*/
	// ------- Turn 90 ------- 
	/*
	while(1) {
		while(!middle_btn_is_pressed());
		_delay_ms(1000);
		turn_left();
	}
	*/
	// ------- Main -------
			
	forward_half_cell(second_half);

	while(1) {
		forward_half_cell(first_half);
		
		if (!has_a_left_wall()) {
			turn_left();
			reset_sensor_reading_after_a_turn();
			if (has_a_front_wall()) { 
				undo_by_turning_right(); 
				restore_sensor_reading();
			}
		} else if (!has_a_front_wall()) {
			// keep straight
		} else if (!has_a_right_wall()) {
			turn_right();
			reset_sensor_reading_after_a_turn();
			if (has_a_front_wall()) { 
				undo_by_turning_left(); 
				restore_sensor_reading();
			}
		} else {
			turn_around();
			reset_sensor_reading_after_a_turn();
		}

		forward_half_cell(second_half);
	}
	
}

void forward_half_cell(uint8_t position) {
	int8_t proportional, derivative, last_proportional = 0;
	uint8_t left_duty, right_duty;
	float steer;

	engage_left_motor_forward();
	engage_right_motor_forward();

	// loop 36 for 10ms delay
	// loop 136 for 1ms delay

	for(uint8_t i=0; i<136; i++) {
		get_sensor_reading();
		if (position == second_half && i >= 50 && i < 55)
			update_next_cell_info();

		set_left_motor_duty_cycle(_20_SPEED);
		set_right_motor_duty_cycle(_20_SPEED);

		if (right_proximity > front_reading_extremely_high && left_proximity > front_reading_extremely_high) {
			break;
		}
		if (right_proximity > side_reading_extremely_high && left_proximity > side_reading_extremely_high) {
			// approaching front wall
			if (right_proximity - left_proximity > 10) {
				set_right_motor_duty_cycle(_15_SPEED);
			} else if (left_proximity - right_proximity > 10) {
				set_left_motor_duty_cycle(_15_SPEED);
			}
		}
		else if (left_proximity > side_reading_extremely_low || right_proximity > side_reading_extremely_low) {
			if (left_proximity > side_reading_extremely_low) {
				proportional = (int)(left_proximity - side_reading_normal);	
			} else {
				proportional = (int)(side_reading_normal - right_proximity);	
			}
			
 			derivative = proportional - last_proportional;
			last_proportional = proportional;

  			steer = (float)proportional/8 - (float)derivative/4;
  			left_duty = _20_SPEED + steer;
  			right_duty = _20_SPEED - steer;
  
  			set_left_motor_duty_cycle(left_duty);
			set_right_motor_duty_cycle(right_duty);
		}
		_delay_ms(1);
	}

	brake_right_motor();
	brake_left_motor();
}

void turn_left() {
	_delay_ms(500);
	set_left_motor_duty_cycle(_75_SPEED);
	set_right_motor_duty_cycle(_75_SPEED);
	engage_left_motor_reverse();
	engage_right_motor_forward();
	_delay_ms(85);	// 70 for _100_
	brake_right_motor();
	brake_left_motor();
	_delay_ms(300);
}

void turn_right() {
	_delay_ms(500);
	set_left_motor_duty_cycle(_75_SPEED);
	set_right_motor_duty_cycle(_75_SPEED);
	engage_right_motor_reverse();
	engage_left_motor_forward();
	_delay_ms(85);
	brake_right_motor();
	brake_left_motor();
	_delay_ms(300);
}

void undo_by_turning_left() {
	turn_left();
}

void undo_by_turning_right() {
	turn_right();
}

void turn_around() {
	_delay_ms(500);
	set_left_motor_duty_cycle(_75_SPEED);
	set_right_motor_duty_cycle(_75_SPEED);
	engage_left_motor_reverse();
	engage_right_motor_forward();
	_delay_ms(160);	// 123 for _100_
	brake_right_motor();
	brake_left_motor();
	_delay_ms(300);
}

void get_sensor_reading() {
	clear();
	
	uint16_t raw_left_sensor_reading = get_left_sensor_reading();
	if (raw_left_sensor_reading < side_reading_extremely_low && raw_left_sensor_reading > side_reading_extremely_high) {
		left_proximity = raw_left_sensor_reading;
	} else {
		left_proximity = (7*left_proximity + raw_left_sensor_reading) / 8;	
	}

	uint16_t raw_right_sensor_reading = get_right_sensor_reading();
	if (raw_right_sensor_reading < side_reading_extremely_low && raw_right_sensor_reading > side_reading_extremely_high) {
		right_proximity = raw_left_sensor_reading;
	} else {
		right_proximity = (7*right_proximity + raw_right_sensor_reading) / 8;	
	}

	// print to LCD 
	print("L ");
	print_long((int)left_proximity);
	lcd_goto_xy(0,1);
	print("R ");
	print_long((int)right_proximity);
}

void reset_sensor_reading_after_a_turn() {
	clear();
	saved_left_proximity = left_proximity;
	saved_right_proximity = right_proximity;
	left_proximity = get_left_sensor_reading();
	right_proximity = get_right_sensor_reading();

	// print to LCD 
	print("L ");
	print_long((int)left_proximity);
	lcd_goto_xy(0,1);
	print("R ");
	print_long((int)right_proximity);
}

void restore_sensor_reading() {
	left_proximity = saved_left_proximity;
	right_proximity = saved_right_proximity;
}

void update_next_cell_info() {
	// shift val in cell_info
	for (uint8_t i=reading_buffer_length-1; i>0; i--) {
		cell_info[i] = cell_info[i-1];
	}
	// add new val into cell_info
	if (left_proximity > side_reading_null)
		cell_info[0] |= W;
	else 
		cell_info[0] &= ~W;
	if (right_proximity > side_reading_null)
		cell_info[0] |= E;
	else
		cell_info[0] &= ~E;
}

uint8_t has_a_left_wall() {
	uint8_t result = 0;
	for (uint8_t i=0; i< reading_buffer_length; i++)
		result += ((cell_info[i] & W)>>3);
	if (result >= 3)
		return 1;
	else return 0;
}

uint8_t has_a_right_wall() {
	uint8_t result = 0;
	for (uint8_t i=0; i< reading_buffer_length; i++)
		result += ((cell_info[i] & E)>>1);
	if (result >= 3) 
		return 1;
	else return 0;
}

uint8_t has_a_front_wall() {
	if (left_proximity > front_reading_high && right_proximity > front_reading_high)
		return 1;
	else return 0;
}
