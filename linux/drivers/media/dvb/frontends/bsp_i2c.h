/*
  Copyright (c), 2004-2005,2007-2010 Trident Microsystems, Inc.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
	and/or other materials provided with the distribution.
  * Neither the name of Trident Microsystems nor Hauppauge Computer Works
    nor the names of its contributors may be used to endorse or promote
	products derived from this software without specific prior written
	permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

/**
* \file $Id: bsp_i2c.h,v 1.5 2009/07/07 14:20:30 justin Exp $
*
* \brief I2C API, implementation depends on board specifics
*
* This module encapsulates I2C access.In some applications several devices
* share one I2C bus. If these devices have the same I2C address some kind
* off "switch" must be implemented to ensure error free communication with
* one device.  In case such a "switch" is used, the device ID can be used
* to implement control over this "switch".
*
*
*/

#ifndef __BSPI2C_H__
#define __BSPI2C_H__
/*------------------------------------------------------------------------------
INCLUDES
------------------------------------------------------------------------------*/
#include "bsp_types.h"

#ifdef __cplusplus
extern "C" {
#endif
/*------------------------------------------------------------------------------
TYPEDEFS
------------------------------------------------------------------------------*/
/**
* \typedef I2Caddr_t
* \brief I2C device address (7-bit or 10-bit)
*/
typedef u16_t I2Caddr_t;

/**
* \typedef I2CdevId_t
* \brief Device identifier.
*
* The device ID can be useful if several devices share an I2C address,
* or if multiple I2C busses are used.
* It can be used to control a "switch" selecting the correct device and/or
* I2C bus.
*
*/
typedef u16_t I2CdevId_t;

/**
* \struct _I2CDeviceAddr_t
* \brief I2C device parameters.
*
* This structure contains the I2C address, the device ID and a userData pointer.
* The userData pointer can be used for application specific purposes.
*
*/
struct _I2CDeviceAddr_t {
	I2Caddr_t  i2cAddr;        /**< The I2C address of the device. */
	I2CdevId_t i2cDevId;       /**< The device identifier. */
	void	*userData;      /**< User data pointer */
};

/**
* \typedef I2CDeviceAddr_t
* \brief I2C device parameters.
*
* This structure contains the I2C address and the device ID.
*
*/
typedef struct _I2CDeviceAddr_t I2CDeviceAddr_t;

/**
* \typedef pI2CDeviceAddr_t
* \brief Pointer to I2C device parameters.
*/
typedef I2CDeviceAddr_t *pI2CDeviceAddr_t;

/*------------------------------------------------------------------------------
DEFINES
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
MACROS
------------------------------------------------------------------------------*/

/**
* \def IS_I2C_10BIT(addr)
* \brief Determine if I2C address 'addr' is a 10 bits address or not.
* \param addr The I2C address.
* \return int.
* \retval 0 if address is not a 10 bits I2C address.
* \retval 1 if address is a 10 bits I2C address.
*/
#define IS_I2C_10BIT(addr) \
	 (((addr) & 0xF8) == 0xF0)

/*------------------------------------------------------------------------------
ENUM
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
STRUCTS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Exported FUNCTIONS
------------------------------------------------------------------------------*/


/**
* \fn DRXBSP_I2C_Init()
* \brief Initialize I2C communication module.
* \return DRXStatus_t Return status.
* \retval DRX_STS_OK Initialization successful.
* \retval DRX_STS_ERROR Initialization failed.
*/
DRXStatus_t DRXBSP_I2C_Init(void);


/**
* \fn DRXBSP_I2C_Term()
* \brief Terminate I2C communication module.
* \return DRXStatus_t Return status.
* \retval DRX_STS_OK Termination successful.
* \retval DRX_STS_ERROR Termination failed.
*/
DRXStatus_t DRXBSP_I2C_Term(void);

/**
* \fn DRXStatus_t DRXBSP_I2C_WriteRead(pI2CDeviceAddr_t wDevAddr,
*                                       u16_t wCount,
*                                       pu8_t wData,
*                                       pI2CDeviceAddr_t rDevAddr,
*                                       u16_t rCount,
*                                       pu8_t rData)
* \brief Read and/or write count bytes from I2C bus, store them in data[].
* \param wDevAddr The device i2c address and the device ID to write to
* \param wCount   The number of bytes to write
* \param wData    The array to write the data to
* \param rDevAddr The device i2c address and the device ID to read from
* \param rCount   The number of bytes to read
* \param rData    The array to read the data from
* \return DRXStatus_t Return status.
* \retval DRX_STS_OK Succes.
* \retval DRX_STS_ERROR Failure.
* \retval DRX_STS_INVALID_ARG Parameter 'wcount' is not zero but parameter
*                                       'wdata' contains NULL.
*                                       Idem for 'rcount' and 'rdata'.
*                                       Both wDevAddr and rDevAddr are NULL.
*
* This function must implement an atomic write and/or read action on the I2C bus
* No other process may use the I2C bus when this function is executing.
* The critical section of this function runs from and including the I2C
* write, up to and including the I2C read action.
*
* The device ID can be useful if several devices share an I2C address.
* It can be used to control a "switch" on the I2C bus to the correct device.
*/
DRXStatus_t DRXBSP_I2C_WriteRead(pI2CDeviceAddr_t wDevAddr,
				    u16_t            wCount,
				    pu8_t            wData,
				    pI2CDeviceAddr_t rDevAddr,
				    u16_t            rCount,
				    pu8_t            rData);


/**
* \fn DRXBSP_I2C_ErrorText()
* \brief Returns a human readable error.
* Counter part of numerical DRX_I2C_Error_g.
*
* \return char* Pointer to human readable error text.
*/
char* DRXBSP_I2C_ErrorText(void);

/**
* \var DRX_I2C_Error_g;
* \brief I2C specific error codes, platform dependent.
*/
extern int DRX_I2C_Error_g;


/*------------------------------------------------------------------------------
THE END
------------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif /* __BSPI2C_H__ */

