 
#include "MLX90640_I2C_Driver.h"
#include <dln_generic.h>
#include <dln_i2c_master.h>
 
 
HDLN device;
uint8_t m_slaveAddress;
int MLX90640_I2CInit(uint8_t slaveAddress)
{   
	m_slaveAddress = slaveAddress;
	DLN_RESULT res = DlnOpenUsbDevice(&device);
	if (res != DLN_RES_SUCCESS)
		return 0;

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
	DlnI2cMasterRead(device, 0, m_slaveAddress, startAddress, 2, 2, (uint8_t *)data);
	return 1;

}
int MLX90640_I2CRead(uint16_t startAddress, uint32_t size, uint16_t *data)
{
    
	DlnI2cMasterRead(device, 0, m_slaveAddress, startAddress, size, size, (uint8_t *)data);

#if 0 
    for(cnt=0; cnt < nMemAddressRead; cnt++)
    {
        i = cnt << 1;
        *p++ = (uint16_t)i2cData[i]*256 + (uint16_t)i2cData[i+1];
    }
#endif 
    return 0;   
} 
 

int MLX90640_I2CWrite(uint16_t writeAddress, uint32_t size, uint8_t *data)
{
     
	DlnI2cMasterWrite(device, 0, m_slaveAddress, size, writeAddress, size, data);
    //MLX90640_I2CRead(slaveAddr,writeAddress,1, &dataCheck);
    
    //if ( dataCheck != data)
    {
        return -2;
    }    
    
    return 0;
}

int MLX90640_I2CWrite16(uint16_t writeAddress, uint16_t data)
{

	DlnI2cMasterWrite(device, 0, m_slaveAddress, 2, writeAddress, 2, (uint8_t *)data);
	//MLX90640_I2CRead(slaveAddr,writeAddress,1, &dataCheck);

	//if ( dataCheck != data)
	{
		return -2;
	}

	return 0;
}

