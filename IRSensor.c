/*
 * Duc Ngo
 * Implementation of IF Sensor
 */


#include "IRSensor.h"
#include "OrangutanAnalog.h"
#include <stdint.h>

void initialize_IR_sensor() {
	DDR(RIGHT_SENSOR_PORT)  &= ~(1<<RIGHT_SENSOR_LOC);
	PORT(RIGHT_SENSOR_PORT) &= ~(1<<RIGHT_SENSOR_LOC);
}

uint16_t get_left_sensor_reading() {
	return analog_read(5);
}

uint16_t get_right_sensor_reading() {
	return analog_read(7);
}
