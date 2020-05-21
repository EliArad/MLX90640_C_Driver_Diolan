#include "inc/MLX90640_API.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
	float mlx90640To[768];
	paramsMLX90640 mlx90640;
	uint16_t eeMLX90640[832];

	const uint8_t MLX90640_address = 0x33; //Default 7-bit unshifted address of the MLX90640

	if (MLX90640_I2CInit(MLX90640_address) != 1)
	{
		printf("failed to initialized diolan i2c");
		return;
	}

	int status = MLX90640_DumpEE(eeMLX90640);
	if (status != 0)
	{
		printf("Failed to load system parameters");
	}

	status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);
}