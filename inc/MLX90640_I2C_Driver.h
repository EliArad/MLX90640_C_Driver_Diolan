/**
 * @copyright (C) 2017 Melexis N.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef _MLX90640_I2C_Driver_H_
#define _MLX90640_I2C_Driver_H_

#include <stdint.h>

    int MLX90640_I2CInit(uint8_t slaveAddress, uint32_t sn);
	int MLX90640_I2CWrite(uint16_t writeAddress, uint32_t size, uint8_t* data);
	int MLX90640_I2CWrite16(uint16_t writeAddress, uint16_t data);
	int MLX90640_I2CRead(uint16_t startAddress, uint32_t size, uint16_t* data);
	int MLX90640_I2CRead832(uint16_t startAddress, uint32_t size, uint16_t* data);
	int MLX90640_I2CRead16(uint16_t startAddress, uint32_t size, uint16_t* data);

#endif