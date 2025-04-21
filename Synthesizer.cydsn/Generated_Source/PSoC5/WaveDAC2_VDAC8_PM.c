/*******************************************************************************
* File Name: WaveDAC2_VDAC8_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "WaveDAC2_VDAC8.h"

static WaveDAC2_VDAC8_backupStruct WaveDAC2_VDAC8_backup;


/*******************************************************************************
* Function Name: WaveDAC2_VDAC8_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void WaveDAC2_VDAC8_SaveConfig(void) 
{
    if (!((WaveDAC2_VDAC8_CR1 & WaveDAC2_VDAC8_SRC_MASK) == WaveDAC2_VDAC8_SRC_UDB))
    {
        WaveDAC2_VDAC8_backup.data_value = WaveDAC2_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: WaveDAC2_VDAC8_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void WaveDAC2_VDAC8_RestoreConfig(void) 
{
    if (!((WaveDAC2_VDAC8_CR1 & WaveDAC2_VDAC8_SRC_MASK) == WaveDAC2_VDAC8_SRC_UDB))
    {
        if((WaveDAC2_VDAC8_Strobe & WaveDAC2_VDAC8_STRB_MASK) == WaveDAC2_VDAC8_STRB_EN)
        {
            WaveDAC2_VDAC8_Strobe &= (uint8)(~WaveDAC2_VDAC8_STRB_MASK);
            WaveDAC2_VDAC8_Data = WaveDAC2_VDAC8_backup.data_value;
            WaveDAC2_VDAC8_Strobe |= WaveDAC2_VDAC8_STRB_EN;
        }
        else
        {
            WaveDAC2_VDAC8_Data = WaveDAC2_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: WaveDAC2_VDAC8_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  WaveDAC2_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void WaveDAC2_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(WaveDAC2_VDAC8_ACT_PWR_EN == (WaveDAC2_VDAC8_PWRMGR & WaveDAC2_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        WaveDAC2_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        WaveDAC2_VDAC8_backup.enableState = 0u;
    }
    
    WaveDAC2_VDAC8_Stop();
    WaveDAC2_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: WaveDAC2_VDAC8_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  WaveDAC2_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void WaveDAC2_VDAC8_Wakeup(void) 
{
    WaveDAC2_VDAC8_RestoreConfig();
    
    if(WaveDAC2_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        WaveDAC2_VDAC8_Enable();

        /* Restore the data register */
        WaveDAC2_VDAC8_SetValue(WaveDAC2_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
