#include <stdio.h>
#include <stdlib.h>
#include "inc/MLX90640_API.h"
#include "inc/MLX90640_I2C_Driver.h"
#include <Windows.h>


void main()
{
	float mlx90640To[768];
	paramsMLX90640 mlx90640;
	uint16_t eeMLX90640[832];
	uint16_t mlx90640Frame[834];

	const uint8_t MLX90640_address = 0x33;  

	if (MLX90640_I2CInit(MLX90640_address, 3955746004) != 1)
	{
		printf("failed to initialized diolan i2c");
		return;
	}

	int status = MLX90640_DumpEE(eeMLX90640);
	if (status != 1)
	{
		printf("Failed to load system parameters");
	}

	status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);

	MLX90640_GetRefreshRate();
	MLX90640_GetCurResolution();
	MLX90640_GetCurMode();

	while (1)
	{
		MLX90640_GetFrameData(mlx90640Frame, 834);

		const double TA_SHIFT = 8; //Default shift for MLX90640 in open air	 
		double m_emissivity = 0.95;
		MLX90640_GetSubPageNumber(mlx90640Frame);


		double vdd = MLX90640_GetVdd(mlx90640Frame, &mlx90640);
		double Ta = MLX90640_GetTa(mlx90640Frame, &mlx90640);

		double tr = Ta - TA_SHIFT; //Reflected temperature based on the sensor ambient temperature
		MLX90640_CalculateTo(mlx90640Frame, &mlx90640, m_emissivity, tr, mlx90640To);
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				printf("%.3f ", mlx90640To[i * 24 + j]);
			}
			printf("\n");
		}
		Sleep(1000);

	}


}