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
* \file $Id: bsp_types.h,v 1.5 2009/08/06 12:55:57 carlo Exp $
*
* \brief General type definitions for board support packages
*
* This file contains type definitions that are needed for almost any
* board support package.
* The definitions are host and project independent.
*
*/

#ifndef __BSP_TYPES_H__
#define __BSP_TYPES_H__
/*-------------------------------------------------------------------------
INCLUDES
-------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
/*-------------------------------------------------------------------------
TYPEDEFS
-------------------------------------------------------------------------*/

/**
* \typedef unsigned char u8_t
* \brief type definition of an unsigned 8 bits integer
*/
typedef unsigned char  u8_t;
/**
* \typedef char s8_t
* \brief type definition of a signed 8 bits integer
*/
typedef char           s8_t;
/**
* \typedef unsigned short u16_t *pu16_t
* \brief type definition of an unsigned 16 bits integer
*/
typedef unsigned short u16_t;
/**
* \typedef short s16_t
* \brief type definition of a signed 16 bits integer
*/
typedef short          s16_t;
/**
* \typedef unsigned long u32_t
* \brief type definition of an unsigned 32 bits integer
*/
typedef unsigned long  u32_t;
/**
* \typedef long s32_t
* \brief type definition of a signed 32 bits integer
*/
typedef long           s32_t;
/*
* \typedef struct ... u64_t
* \brief type definition of an usigned 64 bits integer
*/
typedef struct {
	u32_t MSLW;
	u32_t LSLW;
} u64_t;
/*
* \typedef struct ... i64_t
* \brief type definition of a signed 64 bits integer
*/
typedef struct {
	s32_t MSLW;
	u32_t LSLW;
} s64_t;

/**
* \typedef u8_t *pu8_t
* \brief type definition of pointer to an unsigned 8 bits integer
*/
typedef u8_t         *pu8_t;
/**
* \typedef s8_t *ps8_t
* \brief type definition of pointer to a signed 8 bits integer
*/
typedef s8_t         *ps8_t;
/**
* \typedef u16_t *pu16_t
* \brief type definition of pointer to an unsigned 16 bits integer
*/
typedef u16_t        *pu16_t;
/**
* \typedef s16_t *ps16_t
* \brief type definition of pointer to a signed 16 bits integer
*/
typedef s16_t        *ps16_t;
/**
* \typedef u32_t *pu32_t
* \brief type definition of pointer to an unsigned 32 bits integer
*/
typedef u32_t        *pu32_t;
/**
* \typedef s32_t *ps32_t
* \brief type definition of pointer to a signed 32 bits integer
*/
typedef s32_t        *ps32_t;
/**
* \typedef u64_t *pu64_t
* \brief type definition of pointer to an usigned 64 bits integer
*/
typedef u64_t        *pu64_t;
/**
* \typedef s64_t *ps64_t
* \brief type definition of pointer to a signed 64 bits integer
*/
typedef s64_t        *ps64_t;


/**
* \typedef s32_t DRXFrequency_t
* \brief type definition of frequency
*/
typedef s32_t DRXFrequency_t;

/**
* \typedef DRXFrequency_t *pDRXFrequency_t
* \brief type definition of a pointer to a frequency
*/
typedef DRXFrequency_t *pDRXFrequency_t;

/**
* \typedef u32_t DRXSymbolrate_t
* \brief type definition of symbol rate
*/
typedef u32_t DRXSymbolrate_t;

/**
* \typedef DRXSymbolrate_t *pDRXSymbolrate_t
* \brief type definition of a pointer to a symbol rate
*/
typedef DRXSymbolrate_t *pDRXSymbolrate_t;

/*-------------------------------------------------------------------------
DEFINES
-------------------------------------------------------------------------*/
/**
* \def NULL
* \brief Define NULL for target.
*/
#ifndef NULL
#define NULL            (0)
#endif

/*-------------------------------------------------------------------------
ENUM
-------------------------------------------------------------------------*/

/*
* Boolean datatype. Only define if not already defined TRUE or FALSE.
*/
#if defined (TRUE) || defined (FALSE)
typedef int Bool_t;
#else
/**
* \enum Bool_t
* \brief Boolean type
*/
typedef enum {
   FALSE = 0,
   TRUE
} Bool_t;
#endif
typedef Bool_t  *pBool_t;

/**
* \enum DRXStatus_t
* \brief Various return statusses
*/
typedef enum {
	DRX_STS_READY = 3,               /**< device/service is ready     */
	DRX_STS_BUSY = 2,                /**< device/service is busy      */
	DRX_STS_OK = 1,                  /**< everything is OK            */
	DRX_STS_INVALID_ARG = -1,        /**< invalid arguments           */
	DRX_STS_ERROR = -2,              /**< general error               */
	DRX_STS_FUNC_NOT_AVAILABLE = -3  /**< unavailable functionality   */
} DRXStatus_t, *pDRXStatus_t;


/*-------------------------------------------------------------------------
STRUCTS
-------------------------------------------------------------------------*/

/**
Exported FUNCTIONS
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
THE END
-------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif /* __BSP_TYPES_H__ */

