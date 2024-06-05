/*
 * DHT11_register.h
 *
 *  Created on: Jun 5, 2024
 *      Author: jules
 */

#ifndef INC_MODULE_REGISTER_H_
#define INC_MODULE_REGISTER_H_

#include <stdbool.h>
#include <stdint.h>

/*

0x00:0x01 [sensorTypeMSB][sensorTypeLSB]
0x02:0x05 [sensorIDMSB1][sensorIDMSB2][sensorIDLSB1][sensorIDLSB1]
0x06:0x06 [sensorConf] ---> [readInProgress][idle][][][][][][]                  // bit field used to manage sensor
                                                                        // readInProgress:
                                                                        // set this value before reading data from sensor to prevent byte mangling
                                                                        //      0: sensor can update value
                                                                        //      1: sensor can't update value
                                                                        //
                                                                        // idle:
                                                                        // set the device in power saving mode
                                                                        //      0: sensor operate normally
                                                                        //      1: sensor consume less power
0x07:0x07 [sensorValueUpdatePeriod]                                             // this value represent the time between each value update of the sensor
0x08:0x09 [sensorErrorStatusMSB][sensorErrorStatusLSB]                          // this will be a bit field that represent which error occured
                                                                        //      0:   no error
                                                                        //      1:
                                                                        //      2:
                                                                        //      4:
                                                                        //      8:
                                                                        //      16:
                                                                        //      32:
                                                                        //      64:
                                                                        //      128:
0x0A:0x0E [sensorValueMSB1][sensorValueMSB2][sensorValueLSB1][sensorValueLSB1]  // real sensor value on 32 bit (float)
                                                                        // uint32_t value = 0
                                                                        // value |= (sensorValueMSB1 << 24)
                                                                        // value |= (sensorValueMSB2 << 16)
                                                                        // value |= (sensorValueLSB1 << 8)
                                                                        // value |= (sensorValueLSB1 << 0)
                                                                        // float* real_value = (float*) &value;
*/

enum Register
{
	SENSOR_TYPE_MSB,
	SENSOR_TYPE_LSB,
	SENSOR_ID_MSB1,
	SENSOR_ID_MSB2,
	SENSOR_ID_LSB1,
	SENSOR_ID_LSB2,
	SENSOR_CONFIG,
	SENSOR_UPDATE_PERIOD,
	SENSOR_ERROR_MSB,
	SENSOR_ERROR_LSB,
	SENSOR_VALUE_MSB1,
	SENSOR_VALUE_MSB2,
	SENSOR_VALUE_LSB1,
	SENSOR_VALUE_LSB2,

	REGISTER_MAX_VALUE,
};

enum ConfigBitField
{
	CBF_READ_IN_PROGRESS,
	CBF_IDLE,
};


uint8_t write_register(uint8_t address, uint8_t value);
uint8_t read_register(uint8_t address, uint8_t *value);

void set_sensor_type(uint16_t value);
void set_sensor_id(uint64_t value);
void set_sensor_config_readInProgress(bool value);
void set_sensor_config_idle(bool value);
void set_sensor_updatePeriod(uint8_t value);
void set_sensor_error(uint16_t value);
void set_sensor_value(float value);

uint16_t get_sensor_type();
uint64_t get_sensor_id();
bool get_sensor_config_ReadInProgress();
bool get_sensor_config_Idle();
uint8_t get_sensor_updatePeriod();
uint16_t get_sensor_error();
float get_sensor_value();



#endif /* INC_MODULE_REGISTER_H_ */
