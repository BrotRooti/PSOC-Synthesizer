/*******************************************************************************
* File Name: WaveDAC8_3.c
* Version 2.10
*
* Description:
*  This file provides the source code for the 8-bit Waveform DAC 
*  (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "WaveDAC8_3.h"

uint8  WaveDAC8_3_initVar = 0u;

const uint8 CYCODE WaveDAC8_3_wave1[WaveDAC8_3_WAVE1_LENGTH] = { 125u,129u,133u,138u,142u,146u,150u,154u,158u,162u,166u,170u,174u,178u,181u,185u,189u,192u,196u,199u,202u,206u,209u,212u,215u,218u,220u,223u,226u,228u,230u,233u,235u,237u,238u,240u,242u,243u,244u,246u,247u,247u,248u,249u,249u,250u,250u,250u,250u,250u,249u,249u,248u,247u,247u,246u,244u,243u,242u,240u,238u,237u,235u,233u,230u,228u,226u,223u,220u,218u,215u,212u,209u,206u,202u,199u,196u,192u,189u,185u,181u,178u,174u,170u,166u,162u,158u,154u,150u,146u,142u,138u,133u,129u,125u,121u,117u,112u,108u,104u,100u,96u,92u,88u,84u,80u,76u,72u,69u,65u,61u,58u,54u,51u,48u,44u,41u,38u,35u,32u,30u,27u,24u,22u,20u,17u,15u,13u,12u,10u,8u,7u,6u,4u,3u,3u,2u,1u,1u,0u,0u,0u,0u,0u,1u,1u,2u,3u,3u,4u,6u,7u,8u,10u,12u,13u,15u,17u,20u,22u,24u,27u,30u,32u,35u,38u,41u,44u,48u,51u,54u,58u,61u,65u,69u,72u,76u,80u,84u,88u,92u,96u,100u,104u,108u,112u,117u,121u };
const uint8 CYCODE WaveDAC8_3_wave2[WaveDAC8_3_WAVE2_LENGTH] = { 128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u };

static uint8  WaveDAC8_3_Wave1Chan;
static uint8  WaveDAC8_3_Wave2Chan;
static uint8  WaveDAC8_3_Wave1TD;
static uint8  WaveDAC8_3_Wave2TD;


/*******************************************************************************
* Function Name: WaveDAC8_3_Init
********************************************************************************
*
* Summary:
*  Initializes component with parameters set in the customizer.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void WaveDAC8_3_Init(void) 
{
	WaveDAC8_3_VDAC8_Init();
	WaveDAC8_3_VDAC8_SetSpeed(WaveDAC8_3_HIGHSPEED);
	WaveDAC8_3_VDAC8_SetRange(WaveDAC8_3_DAC_RANGE);

	#if(WaveDAC8_3_DAC_MODE == WaveDAC8_3_CURRENT_MODE)
		WaveDAC8_3_IDAC8_SetPolarity(WaveDAC8_3_DAC_POL);
	#endif /* WaveDAC8_3_DAC_MODE == WaveDAC8_3_CURRENT_MODE */

	#if(WaveDAC8_3_OUT_MODE == WaveDAC8_3_BUFFER_MODE)
	   WaveDAC8_3_BuffAmp_Init();
	#endif /* WaveDAC8_3_OUT_MODE == WaveDAC8_3_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	WaveDAC8_3_Wave1TD = CyDmaTdAllocate();
	WaveDAC8_3_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	WaveDAC8_3_Wave1Setup(WaveDAC8_3_wave1, WaveDAC8_3_WAVE1_LENGTH) ;
	WaveDAC8_3_Wave2Setup(WaveDAC8_3_wave2, WaveDAC8_3_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(WaveDAC8_3_DacClk_PHASE)
	   WaveDAC8_3_DacClk_SetPhase(WaveDAC8_3_CLK_PHASE_0nS);
	#endif /* defined(WaveDAC8_3_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: WaveDAC8_3_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DAC block and DMA operation.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void WaveDAC8_3_Enable(void) 
{
	WaveDAC8_3_VDAC8_Enable();

	#if(WaveDAC8_3_OUT_MODE == WaveDAC8_3_BUFFER_MODE)
	   WaveDAC8_3_BuffAmp_Enable();
	#endif /* WaveDAC8_3_OUT_MODE == WaveDAC8_3_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(WaveDAC8_3_Wave1Chan, 1u);
	(void)CyDmaChEnable(WaveDAC8_3_Wave2Chan, 1u);
	
	/* set the initial value */
	WaveDAC8_3_SetValue(0u);
	
	#if(WaveDAC8_3_CLOCK_SRC == WaveDAC8_3_CLOCK_INT)  	
	   WaveDAC8_3_DacClk_Start();
	#endif /* WaveDAC8_3_CLOCK_SRC == WaveDAC8_3_CLOCK_INT */
}


/*******************************************************************************
* Function Name: WaveDAC8_3_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void WaveDAC8_3_Start(void) 
{
	/* If not Initialized then initialize all required hardware and software */
	if(WaveDAC8_3_initVar == 0u)
	{
		WaveDAC8_3_Init();
		WaveDAC8_3_initVar = 1u;
	}
	
	WaveDAC8_3_Enable();
}


/*******************************************************************************
* Function Name: WaveDAC8_3_StartEx
********************************************************************************
*
* Summary:
*  The StartEx function sets pointers and sizes for both waveforms
*  and then starts the component.
*
* Parameters:  
*   uint8 * wavePtr1:     Pointer to the waveform 1 array.
*   uint16  sampleSize1:  The amount of samples in the waveform 1.
*   uint8 * wavePtr2:     Pointer to the waveform 2 array.
*   uint16  sampleSize2:  The amount of samples in the waveform 2.
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void WaveDAC8_3_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)

{
	WaveDAC8_3_Wave1Setup(wavePtr1, sampleSize1);
	WaveDAC8_3_Wave2Setup(wavePtr2, sampleSize2);
	WaveDAC8_3_Start();
}


/*******************************************************************************
* Function Name: WaveDAC8_3_Stop
********************************************************************************
*
* Summary:
*  Stops the clock (if internal), disables the DMA channels
*  and powers down the DAC.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
*******************************************************************************/
void WaveDAC8_3_Stop(void) 
{
	/* Turn off internal clock, if one present */
	#if(WaveDAC8_3_CLOCK_SRC == WaveDAC8_3_CLOCK_INT)  	
	   WaveDAC8_3_DacClk_Stop();
	#endif /* WaveDAC8_3_CLOCK_SRC == WaveDAC8_3_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(WaveDAC8_3_Wave1Chan);
	(void)CyDmaChDisable(WaveDAC8_3_Wave2Chan);

	/* Disable power to DAC */
	WaveDAC8_3_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: WaveDAC8_3_Wave1Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 1.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None 
*
*******************************************************************************/
void WaveDAC8_3_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)

{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveDAC8_3_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		WaveDAC8_3_Wave1Chan = WaveDAC8_3_Wave1_DMA_DmaInitialize(
		WaveDAC8_3_Wave1_DMA_BYTES_PER_BURST, WaveDAC8_3_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveDAC8_3_Wave1Chan = WaveDAC8_3_Wave1_DMA_DmaInitialize(
		WaveDAC8_3_Wave1_DMA_BYTES_PER_BURST, WaveDAC8_3_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveDAC8_3_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveDAC8_3_Wave1TD, sampleSize, WaveDAC8_3_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveDAC8_3_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveDAC8_3_Wave1TD, LO16((uint32)wavePtr), LO16(WaveDAC8_3_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveDAC8_3_Wave1Chan, WaveDAC8_3_Wave1TD);
}


/*******************************************************************************
* Function Name: WaveDAC8_3_Wave2Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 2.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None
*
*******************************************************************************/
void WaveDAC8_3_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveDAC8_3_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		WaveDAC8_3_Wave2Chan = WaveDAC8_3_Wave2_DMA_DmaInitialize(
		WaveDAC8_3_Wave2_DMA_BYTES_PER_BURST, WaveDAC8_3_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveDAC8_3_Wave2Chan = WaveDAC8_3_Wave2_DMA_DmaInitialize(
		WaveDAC8_3_Wave2_DMA_BYTES_PER_BURST, WaveDAC8_3_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveDAC8_3_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveDAC8_3_Wave2TD, sampleSize, WaveDAC8_3_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveDAC8_3_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveDAC8_3_Wave2TD, LO16((uint32)wavePtr), LO16(WaveDAC8_3_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveDAC8_3_Wave2Chan, WaveDAC8_3_Wave2TD);
}


/* [] END OF FILE */
