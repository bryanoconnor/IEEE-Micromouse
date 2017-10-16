/*
 * Duc Ngo
 * Interface definition for IF Sensor driver
 */

#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "OrangutanAnalog.h"
#include "port_macros.h"
#include <avr/io.h>
#include <stdint.h>

#define RIGHT_SENSOR_PORT C
#define RIGHT_SENSOR_LOC 5

void initialize_IR_sensor();
uint16_t get_left_sensor_reading();
uint16_t get_right_sensor_reading();

#endif