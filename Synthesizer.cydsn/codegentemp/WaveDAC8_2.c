/*******************************************************************************
* File Name: WaveDAC8_2.c
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

#include "WaveDAC8_2.h"

uint8  WaveDAC8_2_initVar = 0u;

const uint8 CYCODE WaveDAC8_2_wave1[WaveDAC8_2_WAVE1_LENGTH] = { 128u,129u,131u,133u,134u,136u,138u,140u,141u,143u,145u,147u,148u,150u,152u,153u,155u,157u,158u,160u,162u,163u,165u,167u,168u,170u,172u,173u,175u,177u,178u,180u,181u,183u,184u,186u,187u,189u,191u,192u,193u,195u,196u,198u,199u,201u,202u,203u,205u,206u,208u,209u,210u,211u,213u,214u,215u,217u,218u,219u,220u,221u,222u,224u,225u,226u,227u,228u,229u,230u,231u,232u,233u,234u,235u,235u,236u,237u,238u,239u,240u,240u,241u,242u,242u,243u,244u,244u,245u,246u,246u,247u,247u,248u,248u,249u,249u,249u,250u,250u,250u,251u,251u,251u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,251u,251u,251u,250u,250u,250u,249u,249u,249u,248u,248u,247u,247u,246u,246u,245u,244u,244u,243u,242u,242u,241u,240u,240u,239u,238u,237u,236u,235u,235u,234u,233u,232u,231u,230u,229u,228u,227u,226u,225u,224u,222u,221u,220u,219u,218u,217u,215u,214u,213u,211u,210u,209u,208u,206u,205u,203u,202u,201u,199u,198u,196u,195u,193u,192u,191u,189u,187u,186u,184u,183u,181u,180u,178u,177u,175u,173u,172u,170u,168u,167u,165u,163u,162u,160u,158u,157u,155u,153u,152u,150u,148u,147u,145u,143u,141u,140u,138u,136u,134u,133u,131u,129u,128u,126u,124u,122u,121u,119u,117u,115u,114u,112u,110u,108u,107u,105u,103u,102u,100u,98u,97u,95u,93u,92u,90u,88u,87u,85u,83u,82u,80u,78u,77u,75u,74u,72u,71u,69u,68u,66u,64u,63u,62u,60u,59u,57u,56u,54u,53u,52u,50u,49u,47u,46u,45u,44u,42u,41u,40u,38u,37u,36u,35u,34u,33u,31u,30u,29u,28u,27u,26u,25u,24u,23u,22u,21u,20u,20u,19u,18u,17u,16u,15u,15u,14u,13u,13u,12u,11u,11u,10u,9u,9u,8u,8u,7u,7u,6u,6u,6u,5u,5u,5u,4u,4u,4u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,4u,4u,4u,5u,5u,5u,6u,6u,6u,7u,7u,8u,8u,9u,9u,10u,11u,11u,12u,13u,13u,14u,15u,15u,16u,17u,18u,19u,20u,20u,21u,22u,23u,24u,25u,26u,27u,28u,29u,30u,31u,33u,34u,35u,36u,37u,38u,40u,41u,42u,44u,45u,46u,47u,49u,50u,52u,53u,54u,56u,57u,59u,60u,62u,63u,64u,66u,68u,69u,71u,72u,74u,75u,77u,78u,80u,82u,83u,85u,87u,88u,90u,92u,93u,95u,97u,98u,100u,102u,103u,105u,107u,108u,110u,112u,114u,115u,117u,119u,121u,122u,124u,126u };
const uint8 CYCODE WaveDAC8_2_wave2[WaveDAC8_2_WAVE2_LENGTH] = { 128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u,128u };

static uint8  WaveDAC8_2_Wave1Chan;
static uint8  WaveDAC8_2_Wave2Chan;
static uint8  WaveDAC8_2_Wave1TD;
static uint8  WaveDAC8_2_Wave2TD;


/*******************************************************************************
* Function Name: WaveDAC8_2_Init
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
void WaveDAC8_2_Init(void) 
{
	WaveDAC8_2_VDAC8_Init();
	WaveDAC8_2_VDAC8_SetSpeed(WaveDAC8_2_HIGHSPEED);
	WaveDAC8_2_VDAC8_SetRange(WaveDAC8_2_DAC_RANGE);

	#if(WaveDAC8_2_DAC_MODE == WaveDAC8_2_CURRENT_MODE)
		WaveDAC8_2_IDAC8_SetPolarity(WaveDAC8_2_DAC_POL);
	#endif /* WaveDAC8_2_DAC_MODE == WaveDAC8_2_CURRENT_MODE */

	#if(WaveDAC8_2_OUT_MODE == WaveDAC8_2_BUFFER_MODE)
	   WaveDAC8_2_BuffAmp_Init();
	#endif /* WaveDAC8_2_OUT_MODE == WaveDAC8_2_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	WaveDAC8_2_Wave1TD = CyDmaTdAllocate();
	WaveDAC8_2_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	WaveDAC8_2_Wave1Setup(WaveDAC8_2_wave1, WaveDAC8_2_WAVE1_LENGTH) ;
	WaveDAC8_2_Wave2Setup(WaveDAC8_2_wave2, WaveDAC8_2_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(WaveDAC8_2_DacClk_PHASE)
	   WaveDAC8_2_DacClk_SetPhase(WaveDAC8_2_CLK_PHASE_0nS);
	#endif /* defined(WaveDAC8_2_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: WaveDAC8_2_Enable
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
void WaveDAC8_2_Enable(void) 
{
	WaveDAC8_2_VDAC8_Enable();

	#if(WaveDAC8_2_OUT_MODE == WaveDAC8_2_BUFFER_MODE)
	   WaveDAC8_2_BuffAmp_Enable();
	#endif /* WaveDAC8_2_OUT_MODE == WaveDAC8_2_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(WaveDAC8_2_Wave1Chan, 1u);
	(void)CyDmaChEnable(WaveDAC8_2_Wave2Chan, 1u);
	
	/* set the initial value */
	WaveDAC8_2_SetValue(0u);
	
	#if(WaveDAC8_2_CLOCK_SRC == WaveDAC8_2_CLOCK_INT)  	
	   WaveDAC8_2_DacClk_Start();
	#endif /* WaveDAC8_2_CLOCK_SRC == WaveDAC8_2_CLOCK_INT */
}


/*******************************************************************************
* Function Name: WaveDAC8_2_Start
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
void WaveDAC8_2_Start(void) 
{
	/* If not Initialized then initialize all required hardware and software */
	if(WaveDAC8_2_initVar == 0u)
	{
		WaveDAC8_2_Init();
		WaveDAC8_2_initVar = 1u;
	}
	
	WaveDAC8_2_Enable();
}


/*******************************************************************************
* Function Name: WaveDAC8_2_StartEx
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
void WaveDAC8_2_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)

{
	WaveDAC8_2_Wave1Setup(wavePtr1, sampleSize1);
	WaveDAC8_2_Wave2Setup(wavePtr2, sampleSize2);
	WaveDAC8_2_Start();
}


/*******************************************************************************
* Function Name: WaveDAC8_2_Stop
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
void WaveDAC8_2_Stop(void) 
{
	/* Turn off internal clock, if one present */
	#if(WaveDAC8_2_CLOCK_SRC == WaveDAC8_2_CLOCK_INT)  	
	   WaveDAC8_2_DacClk_Stop();
	#endif /* WaveDAC8_2_CLOCK_SRC == WaveDAC8_2_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(WaveDAC8_2_Wave1Chan);
	(void)CyDmaChDisable(WaveDAC8_2_Wave2Chan);

	/* Disable power to DAC */
	WaveDAC8_2_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: WaveDAC8_2_Wave1Setup
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
void WaveDAC8_2_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)

{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveDAC8_2_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		WaveDAC8_2_Wave1Chan = WaveDAC8_2_Wave1_DMA_DmaInitialize(
		WaveDAC8_2_Wave1_DMA_BYTES_PER_BURST, WaveDAC8_2_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveDAC8_2_Wave1Chan = WaveDAC8_2_Wave1_DMA_DmaInitialize(
		WaveDAC8_2_Wave1_DMA_BYTES_PER_BURST, WaveDAC8_2_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveDAC8_2_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveDAC8_2_Wave1TD, sampleSize, WaveDAC8_2_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveDAC8_2_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveDAC8_2_Wave1TD, LO16((uint32)wavePtr), LO16(WaveDAC8_2_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveDAC8_2_Wave1Chan, WaveDAC8_2_Wave1TD);
}


/*******************************************************************************
* Function Name: WaveDAC8_2_Wave2Setup
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
void WaveDAC8_2_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveDAC8_2_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		WaveDAC8_2_Wave2Chan = WaveDAC8_2_Wave2_DMA_DmaInitialize(
		WaveDAC8_2_Wave2_DMA_BYTES_PER_BURST, WaveDAC8_2_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveDAC8_2_Wave2Chan = WaveDAC8_2_Wave2_DMA_DmaInitialize(
		WaveDAC8_2_Wave2_DMA_BYTES_PER_BURST, WaveDAC8_2_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveDAC8_2_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveDAC8_2_Wave2TD, sampleSize, WaveDAC8_2_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveDAC8_2_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveDAC8_2_Wave2TD, LO16((uint32)wavePtr), LO16(WaveDAC8_2_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveDAC8_2_Wave2Chan, WaveDAC8_2_Wave2TD);
}


/* [] END OF FILE */
