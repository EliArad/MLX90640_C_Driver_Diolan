 
#include "MLX90640_I2C_Driver.h"
#include <dln_generic.h>
#include <dln_i2c_master.h>
 
 
HDLN device;
uint8_t m_slaveAddress;
int MLX90640_I2CInit(uint8_t slaveAddress, uint32_t sn)
{   
	m_slaveAddress = slaveAddress;
	DLN_RESULT res = DLN_RES_SUCCESS;
	if (sn == 0)
	{
		res = DlnOpenUsbDevice(&device);
		if (res != DLN_RES_SUCCESS)
			return 0;
	}
	else 
	{
		res = DlnOpenUsbDeviceBySn(sn, &device);
		if (res != DLN_RES_SUCCESS)
			return 0;
	}

	// Set frequency
	uint32_t frequency;
	res = DlnI2cMasterSetFrequency(device, 0, 100000, &frequency);
	if (res != DLN_RES_SUCCESS)
		return 0;
	// Enable I2C master
	uint16_t conflict;
	res = DlnI2cMasterEnable(device, 0, &conflict);
	if (res != DLN_RES_SUCCESS)
		return 0;

	return 1;
}

 
int MLX90640_I2CRead16(uint16_t startAddress, uint32_t size, uint16_t *data)
{
	byte i2cData[2];
	DLN_RESULT r = DlnI2cMasterRead(device, 0, m_slaveAddress, 2, startAddress, 2, i2cData);
	*data = (uint16_t)((i2cData[0] << 8) | (i2cData[1]));
	if (r == DLN_RES_SUCCESS)
		return 1;
	return 0;

}
int MLX90640_I2CRead832(uint16_t startAddress, uint32_t size, uint16_t *data)
{
	uint8_t i2cData[1664];
	uint8_t tempI2c[64];
	 
	memset(i2cData, 0, sizeof(i2cData));

	int count = 0;
	for (int i = 0; i < 26; i++)
	{
		DLN_RESULT res = DlnI2cMasterRead(device, 0, m_slaveAddress, 2, startAddress, 64, (uint8_t *)tempI2c);
		if (res != DLN_RES_SUCCESS)
			return 0;

		memcpy(i2cData + count, tempI2c , 64);
		startAddress += 32;
		count += 64;
	}

	int j = 0;
	for (int i = 0; i < 1664; i += 2)
	{
		data[j] = (uint16_t)((i2cData[i] << 8) | i2cData[i + 1]);
		j++;
	} 

	return 1;

    
}  


int MLX90640_I2CRead768(uint16_t startAddress, uint32_t size, uint16_t *data)
{
	uint8_t i2cData[1536];
	uint8_t tempI2c[64];

	memset(i2cData, 0, sizeof(i2cData));

	int count = 0;
	for (int i = 0; i < 24; i++)
	{
		DLN_RESULT res = DlnI2cMasterRead(device, 0, m_slaveAddress, 2, startAddress, 64, (uint8_t *)tempI2c);
		if (res != DLN_RES_SUCCESS)
			return 0;

		memcpy(i2cData + count, tempI2c, 64);
		startAddress += 32;
		count += 64;
	}

	int j = 0;
	for (int i = 0; i < 1536; i += 2)
	{
		data[j] = (uint16_t)((i2cData[i] << 8) | i2cData[i + 1]);
		j++;
	}

	return 1;


}

int MLX90640_I2CRead64(uint16_t startAddress, uint32_t size, uint16_t *data)
{
	uint8_t i2cData[64];
	uint8_t tempI2c[64];

	memset(i2cData, 0, sizeof(i2cData));

	int count = 0;
	for (int i = 0; i < 1; i++)
	{
		DLN_RESULT res = DlnI2cMasterRead(device, 0, m_slaveAddress, 2, startAddress, 64, (uint8_t *)tempI2c);
		if (res != DLN_RES_SUCCESS)
			return 0;

		memcpy(i2cData + count, tempI2c, 64);
		startAddress += 32;
		count += 64;
	}

	int j = 0;
	for (int i = 0; i < 64; i += 2)
	{
		data[j] = (uint16_t)((i2cData[i] << 8) | i2cData[i + 1]);
		j++;
	}

	return 1;


}

int MLX90640_I2CReadFrame(uint16_t startAddress, uint32_t size, uint16_t *data)
{
	uint8_t i2cData[1664];
	uint8_t tempI2c[64];

	memset(i2cData, 0, sizeof(i2cData));

	int count = 0;
	for (int i = 0; i < 26; i++)
	{
		DLN_RESULT res = DlnI2cMasterRead(device, 0, m_slaveAddress, 2, startAddress, 64, (uint8_t *)tempI2c);
		if (res != DLN_RES_SUCCESS)
			return 0;

		memcpy(i2cData + count, tempI2c, 64);
		startAddress += 32;
		count += 64;
	}

	int j = 0;
	for (int i = 0; i < 1664; i += 2)
	{
		data[j] = (uint16_t)((i2cData[i] << 8) | i2cData[i + 1]);
		j++;
	}

	return 1;


}

int MLX90640_I2CRead(uint16_t startAddress, uint32_t size, uint16_t *data)
{

	DLN_RESULT res = DlnI2cMasterRead(device, 0, m_slaveAddress, size, startAddress, size, (uint8_t *)data);
	if (res == DLN_RES_SUCCESS)
		return 1;
   
	return 0;
}
 

int MLX90640_I2CWrite(uint16_t writeAddress, uint32_t size, uint8_t *data)
{
     
	DLN_RESULT r = DlnI2cMasterWrite(device, 0, m_slaveAddress, size, writeAddress, size, data);
	if (r != DLN_RES_SUCCESS)
		return 0;

    //MLX90640_I2CRead(slaveAddr,writeAddress,1, &dataCheck);
    
    //if ( dataCheck != data)
    {
        return -2;
    }        
    return 1;
}

int MLX90640_I2CWrite16(uint16_t writeAddress, uint16_t data)
{
	
	byte temp[2] = { (byte)(data >> 8), (byte)(data & 0xFF) };
	DLN_RESULT r = DlnI2cMasterWrite(device, 0, m_slaveAddress, 2, writeAddress, 2, temp);
	if (r != DLN_RES_SUCCESS)
		return 0;

	uint16_t dataCheck;
	MLX90640_I2CRead16(writeAddress,1, &dataCheck);

	if ( dataCheck != data)
	{
		//return -2;
	}

	return 1;
}

