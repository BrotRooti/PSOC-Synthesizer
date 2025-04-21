/*******************************************************************************
* File Name: WaveDAC2.h  
* Version 2.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the 8-bit Waveform DAC (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_WaveDAC8_WaveDAC2_H) 
#define CY_WaveDAC8_WaveDAC2_H

#include "cytypes.h"
#include "cyfitter.h"
#include <WaveDAC2_Wave1_DMA_dma.h>
#include <WaveDAC2_Wave2_DMA_dma.h>
#include <WaveDAC2_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define WaveDAC2_WAVE1_TYPE     (0u)     /* Waveform for wave1 */
#define WaveDAC2_WAVE2_TYPE     (0u)     /* Waveform for wave2 */
#define WaveDAC2_SINE_WAVE      (0u)
#define WaveDAC2_SQUARE_WAVE    (1u)
#define WaveDAC2_TRIANGLE_WAVE  (2u)
#define WaveDAC2_SAWTOOTH_WAVE  (3u)
#define WaveDAC2_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define WaveDAC2_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define WaveDAC2_WAVE1_LENGTH   (284u)   /* Length for wave1 */
#define WaveDAC2_WAVE2_LENGTH   (568u)   /* Length for wave2 */
	
#define WaveDAC2_DEFAULT_RANGE    (0u) /* Default DAC range */
#define WaveDAC2_DAC_RANGE_1V     (0u)
#define WaveDAC2_DAC_RANGE_1V_BUF (16u)
#define WaveDAC2_DAC_RANGE_4V     (1u)
#define WaveDAC2_DAC_RANGE_4V_BUF (17u)
#define WaveDAC2_VOLT_MODE        (0u)
#define WaveDAC2_CURRENT_MODE     (1u)
#define WaveDAC2_DAC_MODE         (((WaveDAC2_DEFAULT_RANGE == WaveDAC2_DAC_RANGE_1V) || \
									  (WaveDAC2_DEFAULT_RANGE == WaveDAC2_DAC_RANGE_4V) || \
							  		  (WaveDAC2_DEFAULT_RANGE == WaveDAC2_DAC_RANGE_1V_BUF) || \
									  (WaveDAC2_DEFAULT_RANGE == WaveDAC2_DAC_RANGE_4V_BUF)) ? \
									   WaveDAC2_VOLT_MODE : WaveDAC2_CURRENT_MODE)

#define WaveDAC2_DACMODE WaveDAC2_DAC_MODE /* legacy definition for backward compatibility */

#define WaveDAC2_DIRECT_MODE (0u)
#define WaveDAC2_BUFFER_MODE (1u)
#define WaveDAC2_OUT_MODE    (((WaveDAC2_DEFAULT_RANGE == WaveDAC2_DAC_RANGE_1V_BUF) || \
								 (WaveDAC2_DEFAULT_RANGE == WaveDAC2_DAC_RANGE_4V_BUF)) ? \
								  WaveDAC2_BUFFER_MODE : WaveDAC2_DIRECT_MODE)

#if(WaveDAC2_OUT_MODE == WaveDAC2_BUFFER_MODE)
    #include <WaveDAC2_BuffAmp.h>
#endif /* WaveDAC2_OUT_MODE == WaveDAC2_BUFFER_MODE */

#define WaveDAC2_CLOCK_INT      (1u)
#define WaveDAC2_CLOCK_EXT      (0u)
#define WaveDAC2_CLOCK_SRC      (1u)

#if(WaveDAC2_CLOCK_SRC == WaveDAC2_CLOCK_INT)  
	#include <WaveDAC2_DacClk.h>
	#if defined(WaveDAC2_DacClk_PHASE)
		#define WaveDAC2_CLK_PHASE_0nS (1u)
	#endif /* defined(WaveDAC2_DacClk_PHASE) */
#endif /* WaveDAC2_CLOCK_SRC == WaveDAC2_CLOCK_INT */

#if (CY_PSOC3)
	#define WaveDAC2_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define WaveDAC2_Wave1_DMA_BYTES_PER_BURST      (1u)
#define WaveDAC2_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define WaveDAC2_Wave2_DMA_BYTES_PER_BURST      (1u)
#define WaveDAC2_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}WaveDAC2_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void WaveDAC2_Start(void)             ;
void WaveDAC2_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void WaveDAC2_Init(void)              ;
void WaveDAC2_Enable(void)            ;
void WaveDAC2_Stop(void)              ;

void WaveDAC2_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void WaveDAC2_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void WaveDAC2_Sleep(void)             ;
void WaveDAC2_Wakeup(void)            ;

#define WaveDAC2_SetSpeed       WaveDAC2_VDAC8_SetSpeed
#define WaveDAC2_SetRange       WaveDAC2_VDAC8_SetRange
#define WaveDAC2_SetValue       WaveDAC2_VDAC8_SetValue
#define WaveDAC2_DacTrim        WaveDAC2_VDAC8_DacTrim
#define WaveDAC2_SaveConfig     WaveDAC2_VDAC8_SaveConfig
#define WaveDAC2_RestoreConfig  WaveDAC2_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 WaveDAC2_initVar;

extern const uint8 CYCODE WaveDAC2_wave1[WaveDAC2_WAVE1_LENGTH];
extern const uint8 CYCODE WaveDAC2_wave2[WaveDAC2_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(WaveDAC2_DAC_MODE == WaveDAC2_VOLT_MODE)
    #define WaveDAC2_RANGE_1V       (0x00u)
    #define WaveDAC2_RANGE_4V       (0x04u)
#else /* current mode */
    #define WaveDAC2_RANGE_32uA     (0x00u)
    #define WaveDAC2_RANGE_255uA    (0x04u)
    #define WaveDAC2_RANGE_2mA      (0x08u)
    #define WaveDAC2_RANGE_2048uA   WaveDAC2_RANGE_2mA
#endif /* WaveDAC2_DAC_MODE == WaveDAC2_VOLT_MODE */

/* Power setting for SetSpeed API */
#define WaveDAC2_LOWSPEED       (0x00u)
#define WaveDAC2_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define WaveDAC2_DAC8__D WaveDAC2_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define WaveDAC2_HS_MASK        (0x02u)
#define WaveDAC2_HS_LOWPOWER    (0x00u)
#define WaveDAC2_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define WaveDAC2_MODE_MASK      (0x10u)
#define WaveDAC2_MODE_V         (0x00u)
#define WaveDAC2_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define WaveDAC2_RANGE_MASK     (0x0Cu)
#define WaveDAC2_RANGE_0        (0x00u)
#define WaveDAC2_RANGE_1        (0x04u)
#define WaveDAC2_RANGE_2        (0x08u)
#define WaveDAC2_RANGE_3        (0x0Cu)
#define WaveDAC2_IDIR_MASK      (0x04u)

#define WaveDAC2_DAC_RANGE      ((uint8)(0u << 2u) & WaveDAC2_RANGE_MASK)
#define WaveDAC2_DAC_POL        ((uint8)(0u >> 1u) & WaveDAC2_IDIR_MASK)


#endif /* CY_WaveDAC8_WaveDAC2_H  */

/* [] END OF FILE */
