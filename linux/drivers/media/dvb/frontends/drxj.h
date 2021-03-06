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
* \file $Id: drxj.h,v 1.132 2009/12/22 12:13:48 danielg Exp $
*
* \brief DRXJ specific header file
*
* \author Dragan Savic, Milos Nikolic, Mihajlo Katona, Tao Ding, Paul Janssen
*/

#ifndef __DRXJ_H__
#define __DRXJ_H__
/*-------------------------------------------------------------------------
INCLUDES
-------------------------------------------------------------------------*/

#include "drx_driver.h"
#include "drx_dap_fasi.h"

#ifdef __cplusplus
extern "C" {

#endif				/*
 */

/* Check DRX-J specific dap condition */
/* Multi master mode and short addr format only will not work.
   RMW, CRC reset, broadcast and switching back to single master mode
   cannot be done with short addr only in multi master mode. */
#if ((DRXDAP_SINGLE_MASTER==0)&&(DRXDAPFASI_LONG_ADDR_ALLOWED==0))
#error "Multi master mode and short addressing only is an illegal combination"
	*;			/* Generate a fatal compiler error to make sure it stops here,
				   this is necesarry because not all compilers stop after a #error. */

#endif				/*
 */

/*-------------------------------------------------------------------------
TYPEDEFS
-------------------------------------------------------------------------*/
/*============================================================================*/
/*============================================================================*/
/*== code support ============================================================*/
/*============================================================================*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*== SCU cmd if  =============================================================*/
/*============================================================================*/
/*============================================================================*/

typedef struct {

u16_t command;
			     /**< Command number */

u16_t parameterLen;
			     /**< Data length in byte */

u16_t resultLen;
			     /**< result length in byte */

u16_t * parameter;
			     /**< General purpous param */

u16_t * result;
			     /**< General purpous param */

} DRXJSCUCmd_t, *pDRXJSCUCmd_t;



/*============================================================================*/
/*============================================================================*/
/*== CTRL CFG related data structures ========================================*/
/*============================================================================*/
/*============================================================================*/

/* extra intermediate lock state for VSB,QAM,NTSC */
#define DRXJ_DEMOD_LOCK       (DRX_LOCK_STATE_1)

/* OOB lock states */
#define DRXJ_OOB_AGC_LOCK     (DRX_LOCK_STATE_1)   /* analog gain control lock */
#define DRXJ_OOB_SYNC_LOCK    (DRX_LOCK_STATE_2)   /* digital gain control lock */

/* Intermediate powermodes for DRXJ */
#define DRXJ_POWER_DOWN_MAIN_PATH   DRX_POWER_MODE_8
#define DRXJ_POWER_DOWN_CORE        DRX_POWER_MODE_9
#define DRXJ_POWER_DOWN_PLL         DRX_POWER_MODE_10

/* supstition for GPIO FNC mux */
#define APP_O                 (0x0000)

/*#define DRX_CTRL_BASE         (0x0000)*/

#define DRXJ_CTRL_CFG_BASE    (0x1000)
		typedef enum {
DRXJ_CFG_AGC_RF =
		DRXJ_CTRL_CFG_BASE,
DRXJ_CFG_AGC_IF,

DRXJ_CFG_AGC_INTERNAL,
DRXJ_CFG_PRE_SAW,

DRXJ_CFG_AFE_GAIN,
DRXJ_CFG_SYMBOL_CLK_OFFSET,

DRXJ_CFG_ACCUM_CR_RS_CW_ERR,
DRXJ_CFG_FEC_MERS_SEQ_COUNT,

DRXJ_CFG_OOB_MISC,
DRXJ_CFG_SMART_ANT,

DRXJ_CFG_OOB_PRE_SAW,
DRXJ_CFG_VSB_MISC,

DRXJ_CFG_RESET_PACKET_ERR,

		    /* ATV (FM) */
		    DRXJ_CFG_ATV_OUTPUT, /* also for FM (SIF control) but not likely */
		    DRXJ_CFG_ATV_MISC,
DRXJ_CFG_ATV_EQU_COEF,

DRXJ_CFG_ATV_AGC_STATUS,
		/* also for FM (IF,RF, audioAGC) */

DRXJ_CFG_MPEG_OUTPUT_MISC,
DRXJ_CFG_HW_CFG,

DRXJ_CFG_OOB_LO_POW,


DRXJ_CFG_MAX /* dummy, never to be used */

	} DRXJCfgType_t, *pDRXJCfgType_t;


/**
* /struct DRXJCfgSmartAntIO_t
* smart antenna i/o.
*/
	typedef enum DRXJCfgSmartAntIO_t {
DRXJ_SMT_ANT_OUTPUT =
		    0,
DRXJ_SMT_ANT_INPUT
	} DRXJCfgSmartAntIO_t, *pDRXJCfgSmartAntIO_t;


/**
* /struct DRXJCfgSmartAnt_t
* Set smart antenna.
*/
	    typedef struct {

DRXJCfgSmartAntIO_t io;

u16_t ctrlData;

} DRXJCfgSmartAnt_t, *pDRXJCfgSmartAnt_t;


/**
* /struct DRXJAGCSTATUS_t
* AGC status information from the DRXJ-IQM-AF.
*/
	    typedef struct {

u16_t IFAGC;

u16_t RFAGC;

u16_t DigitalAGC;

} DRXJAgcStatus_t, *pDRXJAgcStatus_t;


/* DRXJ_CFG_AGC_RF, DRXJ_CFG_AGC_IF */

/**
* /struct DRXJAgcCtrlMode_t
* Available AGCs modes in the DRXJ.
*/
	typedef enum {
DRX_AGC_CTRL_AUTO =
		    0,
DRX_AGC_CTRL_USER,
DRX_AGC_CTRL_OFF
	} DRXJAgcCtrlMode_t, *pDRXJAgcCtrlMode_t;


/**
* /struct DRXJCfgAgc_t
* Generic interface for all AGCs present on the DRXJ.
*/
	    typedef struct {

DRXStandard_t standard;	/* standard for which these settings
						   apply */

DRXJAgcCtrlMode_t ctrlMode;	/* off, user, auto          */

u16_t outputLevel;	/* range dependent on AGC   */

u16_t minOutputLevel;	/* range dependent on AGC   */

u16_t maxOutputLevel;	/* range dependent on AGC   */

u16_t speed;	/* range dependent on AGC   */

u16_t top;	/* rf-agc take over point   */

u16_t cutOffCurrent;	/* rf-agc is accelerated if output
					   current
					   is below cut-off current                */

} DRXJCfgAgc_t, *pDRXJCfgAgc_t;


/* DRXJ_CFG_PRE_SAW */

/**
* /struct DRXJCfgPreSaw_t
* Interface to configure pre SAW sense.
*/
	    typedef struct {

DRXStandard_t standard;	/* standard to which
						   these settings apply */

u16_t reference;	/* pre SAW reference
					   value, range 0 .. 31 */

Bool_t usePreSaw;	/* TRUE algorithms must use
					   pre SAW sense */

} DRXJCfgPreSaw_t, *pDRXJCfgPreSaw_t;


/* DRXJ_CFG_AFE_GAIN */

/**
* /struct DRXJCfgAfeGain_t
* Interface to configure gain of AFE (LNA + PGA).
*/
	    typedef struct {

DRXStandard_t standard;	/* standard to which these
						   settings apply */

u16_t gain;	/* gain in 0.1 dB steps,
				   DRXJ range 140 .. 335 */

} DRXJCfgAfeGain_t, *pDRXJCfgAfeGain_t;


/**
* /struct DRXJRSErrors_t
* Available failure information in DRXJ_FEC_RS.
*
* Container for errors that are received in the most recently finished
* measurment period
*
*/
	    typedef struct {

u16_t nrBitErrors;  /**< no of pre RS bit errors          */

u16_t nrSymbolErrors;
				     /**< no of pre RS symbol errors       */

u16_t nrPacketErrors;
				     /**< no of pre RS packet errors       */

u16_t nrFailures;   /**< no of post RS failures to decode */

u16_t nrSncParFailCount;
				     /**< no of post RS bit erros          */

} DRXJRSErrors_t, *pDRXJRSErrors_t;


/**
* /struct DRXJCfgVSBMisc_t
* symbol error rate
*/
	    typedef struct {

u32_t symbError;  /**< symbol error rate sps */

} DRXJCfgVSBMisc_t, *pDRXJCfgVSBMisc_t;


/**
* /enum DRXJMpegOutputClockRate_t
* Mpeg output clock rate.
*
*/
	    typedef enum {
DRXJ_MPEG_START_WIDTH_1CLKCYC,

DRXJ_MPEG_START_WIDTH_8CLKCYC
	} DRXJMpegStartWidth_t, *pDRXJMpegStartWidth_t;


/**
* /enum DRXJMpegOutputClockRate_t
* Mpeg output clock rate.
*
*/
	    typedef enum {
DRXJ_MPEGOUTPUT_CLOCK_RATE_AUTO,

DRXJ_MPEGOUTPUT_CLOCK_RATE_75973K,

DRXJ_MPEGOUTPUT_CLOCK_RATE_50625K,

DRXJ_MPEGOUTPUT_CLOCK_RATE_37968K,

DRXJ_MPEGOUTPUT_CLOCK_RATE_30375K,

DRXJ_MPEGOUTPUT_CLOCK_RATE_25313K,

DRXJ_MPEGOUTPUT_CLOCK_RATE_21696K
	} DRXJMpegOutputClockRate_t, *pDRXJMpegOutputClockRate_t;


/**
* /struct DRXJCfgMisc_t
* Change TEI bit of MPEG output
* reverse MPEG output bit order
* set MPEG output clock rate
*/
	    typedef struct {

Bool_t disableTEIHandling;		   /**< if TRUE pass
							(not change) TEI bit */

Bool_t bitReverseMpegOutout;		   /**< if TRUE, parallel:
							msb on MD0; serial:
								 lsb out first */

DRXJMpegOutputClockRate_t mpegOutputClockRate;
							   /**< set MPEG output
							 clock rate that
							 overwrites the
							 derived one from
							 symbol rate */

DRXJMpegStartWidth_t mpegStartWidth;	   /**< set MPEG output
							 start width */

} DRXJCfgMpegOutputMisc_t, *pDRXJCfgMpegOutputMisc_t;


/**
* /enum DRXJXtalFreq_t
* Supported external crystal reference frequency.
*/
	    typedef enum {
DRXJ_XTAL_FREQ_RSVD,
DRXJ_XTAL_FREQ_27MHZ,

DRXJ_XTAL_FREQ_20P25MHZ,
DRXJ_XTAL_FREQ_4MHZ
	} DRXJXtalFreq_t, *pDRXJXtalFreq_t;


/**
* /enum DRXJXtalFreq_t
* Supported external crystal reference frequency.
*/
	typedef enum {
DRXJ_I2C_SPEED_400KBPS,
DRXJ_I2C_SPEED_100KBPS
	} DRXJI2CSpeed_t, *pDRXJI2CSpeed_t;


/**
* /struct DRXJCfgHwCfg_t
* Get hw configuration, such as crystal reference frequency, I2C speed, etc...
*/
	    typedef struct {

DRXJXtalFreq_t xtalFreq;
					/**< crystal reference frequency */

DRXJI2CSpeed_t i2cSpeed;
					/**< 100 or 400 kbps */

} DRXJCfgHwCfg_t, *pDRXJCfgHwCfg_t;


/*
 *  DRXJ_CFG_ATV_MISC
 */
	    typedef struct {

s16_t peakFilter;	/* -8 .. 15 */

u16_t noiseFilter;	/* 0 .. 15 */

} DRXJCfgAtvMisc_t, *pDRXJCfgAtvMisc_t;


/*
 *  DRXJCfgOOBMisc_t
 */
#define   DRXJ_OOB_STATE_RESET                                        0x0
#define   DRXJ_OOB_STATE_AGN_HUNT                                     0x1
#define   DRXJ_OOB_STATE_DGN_HUNT                                     0x2
#define   DRXJ_OOB_STATE_AGC_HUNT                                     0x3
#define   DRXJ_OOB_STATE_FRQ_HUNT                                     0x4
#define   DRXJ_OOB_STATE_PHA_HUNT                                     0x8
#define   DRXJ_OOB_STATE_TIM_HUNT                                     0x10
#define   DRXJ_OOB_STATE_EQU_HUNT                                     0x20
#define   DRXJ_OOB_STATE_EQT_HUNT                                     0x30
#define   DRXJ_OOB_STATE_SYNC                                         0x40

typedef struct {

DRXJAgcStatus_t agc;

Bool_t eqLock;

Bool_t symTimingLock;

Bool_t phaseLock;

Bool_t freqLock;

Bool_t digGainLock;

Bool_t anaGainLock;

u8_t state;

} DRXJCfgOOBMisc_t, *pDRXJCfgOOBMisc_t;


/*
 *  Index of in array of coef
 */
	    typedef enum {
DRXJ_OOB_LO_POW_MINUS0DB =
		    0,
DRXJ_OOB_LO_POW_MINUS5DB,

DRXJ_OOB_LO_POW_MINUS10DB,
DRXJ_OOB_LO_POW_MINUS15DB,

DRXJ_OOB_LO_POW_MAX
	} DRXJCfgOobLoPower_t, *pDRXJCfgOobLoPower_t;


/*
 *  DRXJ_CFG_ATV_EQU_COEF
 */
	    typedef struct {

s16_t coef0;	/* -256 .. 255 */

s16_t coef1;	/* -256 .. 255 */

s16_t coef2;	/* -256 .. 255 */

s16_t coef3;	/* -256 .. 255 */

} DRXJCfgAtvEquCoef_t, *pDRXJCfgAtvEquCoef_t;


/*
 *  Index of in array of coef
 */
	    typedef enum {
DRXJ_COEF_IDX_MN =
		    0,
DRXJ_COEF_IDX_FM,
DRXJ_COEF_IDX_L,

DRXJ_COEF_IDX_LP,
DRXJ_COEF_IDX_BG,
DRXJ_COEF_IDX_DK,

DRXJ_COEF_IDX_I,
DRXJ_COEF_IDX_MAX
	} DRXJCoefArrayIndex_t, *pDRXJCoefArrayIndex_t;


/*
 *  DRXJ_CFG_ATV_OUTPUT
 */

/**
* /enum DRXJAttenuation_t
* Attenuation setting for SIF AGC.
*
*/
	    typedef enum {
DRXJ_SIF_ATTENUATION_0DB,
DRXJ_SIF_ATTENUATION_3DB,

DRXJ_SIF_ATTENUATION_6DB,
DRXJ_SIF_ATTENUATION_9DB
	} DRXJSIFAttenuation_t, *pDRXJSIFAttenuation_t;


/**
* /struct DRXJCfgAtvOutput_t
* SIF attenuation setting.
*
*/
	    typedef struct {

Bool_t enableCVBSOutput;	/* TRUE= enabled */

Bool_t enableSIFOutput;	/* TRUE= enabled */

DRXJSIFAttenuation_t sifAttenuation;

} DRXJCfgAtvOutput_t, *pDRXJCfgAtvOutput_t;


/*
   DRXJ_CFG_ATV_AGC_STATUS (get only)
*/
/* TODO : AFE interface not yet finished, subject to change */
	    typedef struct {

u16_t rfAgcGain;	/* 0 .. 877 uA */

u16_t ifAgcGain;	/* 0 .. 877  uA */

s16_t videoAgcGain;	/* -75 .. 1972 in 0.1 dB steps */

s16_t audioAgcGain;	/* -4 .. 1020 in 0.1 dB steps */

u16_t rfAgcLoopGain;	/* 0 .. 7 */

u16_t ifAgcLoopGain;	/* 0 .. 7 */

u16_t videoAgcLoopGain;	/* 0 .. 7 */

} DRXJCfgAtvAgcStatus_t, *pDRXJCfgAtvAgcStatus_t;


/*============================================================================*/
/*============================================================================*/
/*== CTRL related data structures ============================================*/
/*============================================================================*/
/*============================================================================*/

/* NONE */

/*============================================================================*/
/*============================================================================*/

/*========================================*/
/**
* /struct DRXJData_t
* DRXJ specific attributes.
*
* Global data container for DRXJ specific data.
*
*/
	    typedef struct {

		    /* device capabilties (determined during DRX_Open()) */
		Bool_t hasLNA;		       /**< TRUE if LNA (aka PGA) present */

Bool_t hasOOB;		       /**< TRUE if OOB supported */

Bool_t hasNTSC;	       /**< TRUE if NTSC supported */

Bool_t hasBTSC;	       /**< TRUE if BTSC supported */

Bool_t hasSMATX;	       /**< TRUE if mat_tx is available */

Bool_t hasSMARX;	       /**< TRUE if mat_rx is available */

Bool_t hasGPIO;	       /**< TRUE if GPIO is available */

Bool_t hasIRQN;	       /**< TRUE if IRQN is available */

		    /* A1/A2/A... */
		u8_t mfx;		       /**< metal fix */


		    /* tuner settings */
		Bool_t mirrorFreqSpectOOB;     /**< tuner inversion (TRUE = tuner mirrors the signal */


		    /* standard/channel settings */
		DRXStandard_t standard;	       /**< current standard information                     */

DRXConstellation_t constellation;
					       /**< current constellation                            */

DRXFrequency_t frequency;     /**< center signal frequency in KHz                   */

DRXBandwidth_t currBandwidth; /**< current channel bandwidth                        */

DRXMirror_t mirror;	       /**< current channel mirror                           */


		    /* signal quality information */
		u32_t fecBitsDesired;	       /**< BER accounting period                            */

u16_t fecVdPlen;	       /**< no of trellis symbols: VD SER measurement period */

u16_t qamVdPrescale;	       /**< Viterbi Measurement Prescale                     */

u16_t qamVdPeriod;	       /**< Viterbi Measurement period                       */

u16_t fecRsPlen;	       /**< defines RS BER measurement period                */

u16_t fecRsPrescale;	       /**< ReedSolomon Measurement Prescale                 */

u16_t fecRsPeriod;	       /**< ReedSolomon Measurement period                   */

Bool_t resetPktErrAcc;	       /**< Set a flag to reset accumulated packet error     */

u16_t pktErrAccStart;	       /**< Set a flag to reset accumulated packet error     */


		    /* HI configuration */
		u16_t HICfgTimingDiv;	       /**< HI Configure() parameter 2                       */

u16_t HICfgBridgeDelay;       /**< HI Configure() parameter 3                       */

u16_t HICfgWakeUpKey;	       /**< HI Configure() parameter 4                       */

u16_t HICfgCtrl;	       /**< HI Configure() parameter 5                       */

u16_t HICfgTransmit;	       /**< HI Configure() parameter 6                       */


		    /* UIO configuartion */
		DRXUIOMode_t uioSmaRxMode;     /**< current mode of SmaRx pin                        */

DRXUIOMode_t uioSmaTxMode;    /**< current mode of SmaTx pin                        */

DRXUIOMode_t uioGPIOMode;     /**< current mode of ASEL pin                         */

DRXUIOMode_t uioIRQNMode;     /**< current mode of IRQN pin                         */


		    /* IQM fs frequecy shift and inversion */
		u32_t iqmFsRateOfs;		/**< frequency shifter setting after setchannel      */

Bool_t posImage;		/**< Ture: positive image                            */

		    /* IQM RC frequecy shift */
		u32_t iqmRcRateOfs;		/**< frequency shifter setting after setchannel      */


		    /* ATV configuartion */
		u32_t atvCfgChangedFlags;      /**< flag: flags cfg changes */

s16_t atvTopEqu0[DRXJ_COEF_IDX_MAX];		  /**< shadow of ATV_TOP_EQU0__A */

s16_t atvTopEqu1[DRXJ_COEF_IDX_MAX];		  /**< shadow of ATV_TOP_EQU1__A */

s16_t atvTopEqu2[DRXJ_COEF_IDX_MAX];		  /**< shadow of ATV_TOP_EQU2__A */

s16_t atvTopEqu3[DRXJ_COEF_IDX_MAX];		  /**< shadow of ATV_TOP_EQU3__A */

Bool_t phaseCorrectionBypass;	  /**< flag: TRUE=bypass */

s16_t atvTopVidPeak;	       /**< shadow of ATV_TOP_VID_PEAK__A */

u16_t atvTopNoiseTh;	       /**< shadow of ATV_TOP_NOISE_TH__A */

Bool_t enableCVBSOutput;      /**< flag CVBS ouput enable */

Bool_t enableSIFOutput;       /**< flag SIF ouput enable */

DRXJSIFAttenuation_t
 sifAttenuation;
					    /**< current SIF att setting */

		    /* Agc configuration for QAM and VSB */
		DRXJCfgAgc_t qamRfAgcCfg;      /**< qam RF AGC config */

DRXJCfgAgc_t qamIfAgcCfg;     /**< qam IF AGC config */

DRXJCfgAgc_t vsbRfAgcCfg;     /**< vsb RF AGC config */

DRXJCfgAgc_t vsbIfAgcCfg;     /**< vsb IF AGC config */


		    /* PGA gain configuration for QAM and VSB */
		u16_t qamPgaCfg;	       /**< qam PGA config */

u16_t vsbPgaCfg;	       /**< vsb PGA config */


		    /* Pre SAW configuration for QAM and VSB */
		DRXJCfgPreSaw_t qamPreSawCfg;  /**< qam pre SAW config */

DRXJCfgPreSaw_t vsbPreSawCfg; /**< qam pre SAW config */


		    /* Version information */
		char vText[2][12];	       /**< allocated text versions */

DRXVersion_t vVersion[2];     /**< allocated versions structs */

DRXVersionList_t vListElements[2];
					       /**< allocated version list */


		    /* smart antenna configuration */
		 Bool_t smartAntInverted;


		    /* Tracking filter setting for OOB */
		 u16_t oobTrkFilterCfg[8];

Bool_t oobPowerOn;


		    /* MPEG static bitrate setting */
		 u32_t mpegTsStaticBitrate;	 /**< bitrate static MPEG output */

Bool_t disableTEIhandling;	 /**< MPEG TS TEI handling */

Bool_t bitReverseMpegOutout;	 /**< MPEG output bit order */

DRXJMpegOutputClockRate_t
	mpegOutputClockRate;
					      /**< MPEG output clock rate */

DRXJMpegStartWidth_t
	mpegStartWidth;
					      /**< MPEG Start width */


		    /* Pre SAW & Agc configuration for ATV */
		 DRXJCfgPreSaw_t atvPreSawCfg; /**< atv pre SAW config */

DRXJCfgAgc_t atvRfAgcCfg;     /**< atv RF AGC config */

DRXJCfgAgc_t atvIfAgcCfg;     /**< atv IF AGC config */

u16_t atvPgaCfg;	       /**< atv pga config    */


u32_t currSymbolRate;


		    /* pin-safe mode */
		 Bool_t pdrSafeMode;		 /**< PDR safe mode activated      */

u16_t pdrSafeRestoreValGpio;

u16_t pdrSafeRestoreValVSync;

u16_t pdrSafeRestoreValSmaRx;

u16_t pdrSafeRestoreValSmaTx;


		    /* OOB pre-saw value */
		 u16_t oobPreSaw;

DRXJCfgOobLoPower_t oobLoPow;


DRXAudData_t audData;	 /**< audio storage                  */


} DRXJData_t, *pDRXJData_t;


/*-------------------------------------------------------------------------
Access MACROS
-------------------------------------------------------------------------*/
/**
* \brief Compilable references to attributes
* \param d pointer to demod instance
*
* Used as main reference to an attribute field.
* Can be used by both macro implementation and function implementation.
* These macros are defined to avoid duplication of code in macro and function
* definitions that handle access of demod common or extended attributes.
*
*/

#define DRXJ_ATTR_BTSC_DETECT(d)                       \
	 (((pDRXJData_t) (d)->myExtAttr)->audData.btscDetect)

/**
* \brief Actual access macros
* \param d pointer to demod instance
* \param x value to set or to get
*
* SET macros must be used to set the value of an attribute.
* GET macros must be used to retrieve the value of an attribute.
* Depending on the value of DRX_USE_ACCESS_FUNCTIONS the macro's will be
* substituted by "direct-access-inline-code" or a function call.
*
*/
#define DRXJ_GET_BTSC_DETECT(d, x)                     \
	    do {					\
(x) = DRXJ_ATTR_BTSC_DETECT((d)); 			\
} while (0)

#define DRXJ_SET_BTSC_DETECT(d, x)                     \
				      do {	      \
DRXJ_ATTR_BTSC_DETECT(d) = (x);				      \
} while (0)


/*-------------------------------------------------------------------------
DEFINES
-------------------------------------------------------------------------*/

/**
* \def DRXJ_NTSC_CARRIER_FREQ_OFFSET
* \brief Offset from picture carrier to centre frequency in kHz, in RF domain
*
* For NTSC standard.
* NTSC channels are listed by their picture carrier frequency (Fpc).
* The function DRX_CTRL_SET_CHANNEL requires the centre frequency as input.
* In case the tuner module is not used the DRX-J requires that the tuner is
* tuned to the centre frequency of the channel:
*
* Fcentre = Fpc + DRXJ_NTSC_CARRIER_FREQ_OFFSET
*
*/
#define DRXJ_NTSC_CARRIER_FREQ_OFFSET           ((DRXFrequency_t)(1750))

/**
* \def DRXJ_PAL_SECAM_BG_CARRIER_FREQ_OFFSET
* \brief Offset from picture carrier to centre frequency in kHz, in RF domain
*
* For PAL/SECAM - BG standard. This define is needed in case the tuner module
* is NOT used. PAL/SECAM channels are listed by their picture carrier frequency
* (Fpc).
* The DRX-J requires that the tuner is tuned to:
* Fpc + DRXJ_PAL_SECAM_BG_CARRIER_FREQ_OFFSET
*
* In case the tuner module is used the drxdriver takes care of this.
* In case the tuner module is NOT used the application programmer must take
* care of this.
*
*/
#define DRXJ_PAL_SECAM_BG_CARRIER_FREQ_OFFSET   ((DRXFrequency_t)(2375))

/**
* \def DRXJ_PAL_SECAM_DKIL_CARRIER_FREQ_OFFSET
* \brief Offset from picture carrier to centre frequency in kHz, in RF domain
*
* For PAL/SECAM - DK, I, L standards. This define is needed in case the tuner
* module
* is NOT used. PAL/SECAM channels are listed by their picture carrier frequency
* (Fpc).
* The DRX-J requires that the tuner is tuned to:
* Fpc + DRXJ_PAL_SECAM_DKIL_CARRIER_FREQ_OFFSET
*
* In case the tuner module is used the drxdriver takes care of this.
* In case the tuner module is NOT used the application programmer must take
* care of this.
*
*/
#define DRXJ_PAL_SECAM_DKIL_CARRIER_FREQ_OFFSET ((DRXFrequency_t)(2775))

/**
* \def DRXJ_PAL_SECAM_LP_CARRIER_FREQ_OFFSET
* \brief Offset from picture carrier to centre frequency in kHz, in RF domain
*
* For PAL/SECAM - LP standard. This define is needed in case the tuner module
* is NOT used. PAL/SECAM channels are listed by their picture carrier frequency
* (Fpc).
* The DRX-J requires that the tuner is tuned to:
* Fpc + DRXJ_PAL_SECAM_LP_CARRIER_FREQ_OFFSET
*
* In case the tuner module is used the drxdriver takes care of this.
* In case the tuner module is NOT used the application programmer must take
* care of this.
*/
#define DRXJ_PAL_SECAM_LP_CARRIER_FREQ_OFFSET   ((DRXFrequency_t)(-3255))

/**
* \def DRXJ_FM_CARRIER_FREQ_OFFSET
* \brief Offset from sound carrier to centre frequency in kHz, in RF domain
*
* For FM standard.
* FM channels are listed by their sound carrier frequency (Fsc).
* The function DRX_CTRL_SET_CHANNEL requires the Ffm frequency (see below) as
* input.
* In case the tuner module is not used the DRX-J requires that the tuner is
* tuned to the Ffm frequency of the channel.
*
* Ffm = Fsc + DRXJ_FM_CARRIER_FREQ_OFFSET
*
*/
#define DRXJ_FM_CARRIER_FREQ_OFFSET             ((DRXFrequency_t)(-3000))

/* Revision types -------------------------------------------------------*/

#define DRXJ_TYPE_ID (0x3946000DUL)

/* Macros ---------------------------------------------------------------*/

/* Convert OOB lock status to string */
#define DRXJ_STR_OOB_LOCKSTATUS(x) (\
				      (x ==  DRX_NEVER_LOCK) ? "Never" : \
(x ==      DRX_NOT_LOCKED)     ? "No" : \
(x ==  DRX_LOCKED) ? "Locked"			      : \
(x ==		   DRX_LOCK_STATE_1)			      "AGC lock" : \
(x == DRX_LOCK_STATE_2)				      ? "sync lock" : \
"(Invalid)")


/*-------------------------------------------------------------------------
ENUM
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
STRUCTS
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
Exported FUNCTIONS
-------------------------------------------------------------------------*/

extern DRXStatus_t DRXJ_Open(pDRXDemodInstance_t demod);

extern DRXStatus_t DRXJ_Close(pDRXDemodInstance_t demod);

extern DRXStatus_t DRXJ_Ctrl(pDRXDemodInstance_t demod,

DRXCtrlIndex_t ctrl,
void *ctrlData);


/*-------------------------------------------------------------------------
Exported GLOBAL VARIABLES
-------------------------------------------------------------------------*/
	extern DRXAccessFunc_t drxDapDRXJFunct_g;

extern DRXDemodFunc_t DRXJFunctions_g;

extern DRXJData_t DRXJData_g;

extern I2CDeviceAddr_t DRXJDefaultAddr_g;

extern DRXCommonAttr_t DRXJDefaultCommAttr_g;

extern DRXDemodInstance_t DRXJDefaultDemod_g;


/*-------------------------------------------------------------------------
THE END
-------------------------------------------------------------------------*/
#ifdef __cplusplus
	}
#endif				/*
 */
#endif	/* __DRXJ_H__ */
