/*
 * module_register.c
 *
 *  Created on: Jun 5, 2024
 *      Author: jules
 */

#ifndef SRC_MODULE_REGISTER_C_
#define SRC_MODULE_REGISTER_C_

#include "module_register.h"

volatile uint8_t module_registers[REGISTER_MAX_VALUE] = {0};

uint8_t write_register(uint8_t address, uint8_t value)
{
	if (address >= REGISTER_MAX_VALUE)
		return 1;
	module_registers[address] = value;
	return 0;
}
uint8_t read_register(uint8_t address, uint8_t *value)
{
	if (address >= REGISTER_MAX_VALUE)
		return 1;
	*value = module_registers[address];
	return 0;
}

void set_sensor_type(uint16_t value)
{
	write_register(SENSOR_TYPE_MSB, ((value & 0xff00) >> 8));
	write_register(SENSOR_TYPE_LSB, ((value & 0x00FF) >> 0));
}
void set_sensor_id(uint64_t value)
{
	write_register(SENSOR_ID_MSB1, ((value & 0xff000000) >> 24));
	write_register(SENSOR_ID_MSB2, ((value & 0x00ff0000) >> 16));
	write_register(SENSOR_ID_LSB1, ((value & 0x0000ff00) >>  8));
	write_register(SENSOR_ID_LSB2, ((value & 0x000000ff) >>  0));
}
void set_sensor_config_readInProgress(bool value)
{
	uint8_t reg_value = module_registers[SENSOR_CONFIG];

	if (value)
		reg_value |= (1 << CBF_READ_IN_PROGRESS);
	else
		reg_value &= ~(1 << CBF_READ_IN_PROGRESS);
	write_register(SENSOR_CONFIG, reg_value);
}

void set_sensor_config_idle(bool value)
{
	uint8_t reg_value = module_registers[SENSOR_CONFIG];

	if (value)
		reg_value |= (1 << CBF_IDLE);
	else
		reg_value &= ~(1 << CBF_IDLE);

	write_register(SENSOR_CONFIG, reg_value);
}
void set_sensor_updatePeriod(uint8_t value)
{
	write_register(SENSOR_UPDATE_PERIOD, value);
}
void set_sensor_error(uint16_t value)
{
	write_register(SENSOR_ERROR_MSB, ((value & 0xff00) >> 8));
	write_register(SENSOR_ERROR_LSB, ((value & 0x00FF) >> 0));
}
void set_sensor_value(float value)
{
	uint64_t *r_value = (uint64_t *) &value;

	write_register(SENSOR_VALUE_MSB1, ((*r_value & 0xff000000) >> 24));
	write_register(SENSOR_VALUE_MSB2, ((*r_value & 0x00ff0000) >> 16));
	write_register(SENSOR_VALUE_LSB1, ((*r_value & 0x0000ff00) >>  8));
	write_register(SENSOR_VALUE_LSB2, ((*r_value & 0x000000ff) >>  0));
}

uint16_t get_sensor_type()
{
	uint16_t result = 0;
	result = module_registers[SENSOR_ERROR_MSB];
	result <<= 8;
	result |= module_registers[SENSOR_ERROR_LSB];
	return result;
}
uint64_t get_sensor_id()
{
	uint64_t result = 0;
	result = module_registers[SENSOR_ID_MSB1];
	result <<= 8;
	result |= module_registers[SENSOR_ID_MSB2];
	result <<= 8;
	result |= module_registers[SENSOR_ID_LSB1];
	result <<= 8;
	result |= module_registers[SENSOR_ID_LSB2];
	return result;
}
bool get_sensor_config_ReadInProgress()
{
	return((module_registers[SENSOR_CONFIG] >> CBF_READ_IN_PROGRESS) & 0x01);
}
bool get_sensor_config_Idle()
{
	return((module_registers[SENSOR_CONFIG] >> CBF_IDLE) & 0x01);
}
uint8_t get_sensor_updatePeriod()
{
	return module_registers[SENSOR_UPDATE_PERIOD];
}
uint16_t get_sensor_error()
{
	uint16_t result = 0;
	result = module_registers[SENSOR_ERROR_MSB];
	result <<= 8;
	result |= module_registers[SENSOR_ERROR_LSB];
	return result;
}

float get_sensor_value()
{
	float result = 0;

	uint64_t *r_result = (uint64_t *) &result;

	*r_result = module_registers[SENSOR_VALUE_MSB1];
	*r_result <<= 8;
	*r_result |= module_registers[SENSOR_VALUE_MSB2];
	*r_result <<= 8;
	*r_result |= module_registers[SENSOR_VALUE_LSB1];
	*r_result <<= 8;
	*r_result |= module_registers[SENSOR_VALUE_LSB2];

	return result;
}

#endif /* SRC_MODULE_REGISTER_C_ */
