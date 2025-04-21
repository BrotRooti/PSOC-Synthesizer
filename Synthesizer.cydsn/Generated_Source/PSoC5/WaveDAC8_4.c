/*******************************************************************************
* File Name: WaveDAC8_4.c
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

#include "WaveDAC8_4.h"

uint8  WaveDAC8_4_initVar = 0u;

const uint8 CYCODE WaveDAC8_4_wave1[WaveDAC8_4_WAVE1_LENGTH] = { 128u,133u,139u,144u,150u,155u,160u,165u,171u,175u,180u,185u,189u,194u,198u,202u,205u,209u,212u,215u,217u,219u,222u,223u,225u,226u,227u,227u,227u,227u,227u,226u,225u,224u,222u,221u,218u,216u,213u,210u,207u,203u,200u,196u,192u,187u,183u,178u,173u,168u,163u,158u,152u,147u,141u,136u,130u,125u,119u,114u,108u,103u,97u,92u,87u,82u,77u,72u,68u,63u,59u,55u,52u,48u,45u,42u,39u,37u,34u,33u,31u,30u,29u,28u,28u,28u,28u,28u,29u,30u,32u,33u,36u,38u,40u,43u,46u,50u,53u,57u,61u,66u,70u,75u,80u,84u,90u,95u,100u,105u,111u,116u,122u };
const uint8 CYCODE WaveDAC8_4_wave2[WaveDAC8_4_WAVE2_LENGTH] = { 128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u };

static uint8  WaveDAC8_4_Wave1Chan;
static uint8  WaveDAC8_4_Wave2Chan;
static uint8  WaveDAC8_4_Wave1TD;
static uint8  WaveDAC8_4_Wave2TD;


/*******************************************************************************
* Function Name: WaveDAC8_4_Init
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
void WaveDAC8_4_Init(void) 
{
	WaveDAC8_4_VDAC8_Init();
	WaveDAC8_4_VDAC8_SetSpeed(WaveDAC8_4_HIGHSPEED);
	WaveDAC8_4_VDAC8_SetRange(WaveDAC8_4_DAC_RANGE);

	#if(WaveDAC8_4_DAC_MODE == WaveDAC8_4_CURRENT_MODE)
		WaveDAC8_4_IDAC8_SetPolarity(WaveDAC8_4_DAC_POL);
	#endif /* WaveDAC8_4_DAC_MODE == WaveDAC8_4_CURRENT_MODE */

	#if(WaveDAC8_4_OUT_MODE == WaveDAC8_4_BUFFER_MODE)
	   WaveDAC8_4_BuffAmp_Init();
	#endif /* WaveDAC8_4_OUT_MODE == WaveDAC8_4_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	WaveDAC8_4_Wave1TD = CyDmaTdAllocate();
	WaveDAC8_4_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	WaveDAC8_4_Wave1Setup(WaveDAC8_4_wave1, WaveDAC8_4_WAVE1_LENGTH) ;
	WaveDAC8_4_Wave2Setup(WaveDAC8_4_wave2, WaveDAC8_4_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(WaveDAC8_4_DacClk_PHASE)
	   WaveDAC8_4_DacClk_SetPhase(WaveDAC8_4_CLK_PHASE_0nS);
	#endif /* defined(WaveDAC8_4_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: WaveDAC8_4_Enable
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
void WaveDAC8_4_Enable(void) 
{
	WaveDAC8_4_VDAC8_Enable();

	#if(WaveDAC8_4_OUT_MODE == WaveDAC8_4_BUFFER_MODE)
	   WaveDAC8_4_BuffAmp_Enable();
	#endif /* WaveDAC8_4_OUT_MODE == WaveDAC8_4_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(WaveDAC8_4_Wave1Chan, 1u);
	(void)CyDmaChEnable(WaveDAC8_4_Wave2Chan, 1u);
	
	/* set the initial value */
	WaveDAC8_4_SetValue(0u);
	
	#if(WaveDAC8_4_CLOCK_SRC == WaveDAC8_4_CLOCK_INT)  	
	   WaveDAC8_4_DacClk_Start();
	#endif /* WaveDAC8_4_CLOCK_SRC == WaveDAC8_4_CLOCK_INT */
}


/*******************************************************************************
* Function Name: WaveDAC8_4_Start
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
void WaveDAC8_4_Start(void) 
{
	/* If not Initialized then initialize all required hardware and software */
	if(WaveDAC8_4_initVar == 0u)
	{
		WaveDAC8_4_Init();
		WaveDAC8_4_initVar = 1u;
	}
	
	WaveDAC8_4_Enable();
}


/*******************************************************************************
* Function Name: WaveDAC8_4_StartEx
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
void WaveDAC8_4_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)

{
	WaveDAC8_4_Wave1Setup(wavePtr1, sampleSize1);
	WaveDAC8_4_Wave2Setup(wavePtr2, sampleSize2);
	WaveDAC8_4_Start();
}


/*******************************************************************************
* Function Name: WaveDAC8_4_Stop
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
void WaveDAC8_4_Stop(void) 
{
	/* Turn off internal clock, if one present */
	#if(WaveDAC8_4_CLOCK_SRC == WaveDAC8_4_CLOCK_INT)  	
	   WaveDAC8_4_DacClk_Stop();
	#endif /* WaveDAC8_4_CLOCK_SRC == WaveDAC8_4_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(WaveDAC8_4_Wave1Chan);
	(void)CyDmaChDisable(WaveDAC8_4_Wave2Chan);

	/* Disable power to DAC */
	WaveDAC8_4_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: WaveDAC8_4_Wave1Setup
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
void WaveDAC8_4_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)

{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveDAC8_4_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		WaveDAC8_4_Wave1Chan = WaveDAC8_4_Wave1_DMA_DmaInitialize(
		WaveDAC8_4_Wave1_DMA_BYTES_PER_BURST, WaveDAC8_4_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveDAC8_4_Wave1Chan = WaveDAC8_4_Wave1_DMA_DmaInitialize(
		WaveDAC8_4_Wave1_DMA_BYTES_PER_BURST, WaveDAC8_4_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveDAC8_4_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveDAC8_4_Wave1TD, sampleSize, WaveDAC8_4_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveDAC8_4_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveDAC8_4_Wave1TD, LO16((uint32)wavePtr), LO16(WaveDAC8_4_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveDAC8_4_Wave1Chan, WaveDAC8_4_Wave1TD);
}


/*******************************************************************************
* Function Name: WaveDAC8_4_Wave2Setup
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
void WaveDAC8_4_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveDAC8_4_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		WaveDAC8_4_Wave2Chan = WaveDAC8_4_Wave2_DMA_DmaInitialize(
		WaveDAC8_4_Wave2_DMA_BYTES_PER_BURST, WaveDAC8_4_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveDAC8_4_Wave2Chan = WaveDAC8_4_Wave2_DMA_DmaInitialize(
		WaveDAC8_4_Wave2_DMA_BYTES_PER_BURST, WaveDAC8_4_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveDAC8_4_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveDAC8_4_Wave2TD, sampleSize, WaveDAC8_4_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveDAC8_4_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveDAC8_4_Wave2TD, LO16((uint32)wavePtr), LO16(WaveDAC8_4_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveDAC8_4_Wave2Chan, WaveDAC8_4_Wave2TD);
}


/* [] END OF FILE */
