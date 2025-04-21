/*******************************************************************************
* File Name: WaveDAC1_VDAC8_PM.c  
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

#include "WaveDAC1_VDAC8.h"

static WaveDAC1_VDAC8_backupStruct WaveDAC1_VDAC8_backup;


/*******************************************************************************
* Function Name: WaveDAC1_VDAC8_SaveConfig
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
void WaveDAC1_VDAC8_SaveConfig(void) 
{
    if (!((WaveDAC1_VDAC8_CR1 & WaveDAC1_VDAC8_SRC_MASK) == WaveDAC1_VDAC8_SRC_UDB))
    {
        WaveDAC1_VDAC8_backup.data_value = WaveDAC1_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: WaveDAC1_VDAC8_RestoreConfig
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
void WaveDAC1_VDAC8_RestoreConfig(void) 
{
    if (!((WaveDAC1_VDAC8_CR1 & WaveDAC1_VDAC8_SRC_MASK) == WaveDAC1_VDAC8_SRC_UDB))
    {
        if((WaveDAC1_VDAC8_Strobe & WaveDAC1_VDAC8_STRB_MASK) == WaveDAC1_VDAC8_STRB_EN)
        {
            WaveDAC1_VDAC8_Strobe &= (uint8)(~WaveDAC1_VDAC8_STRB_MASK);
            WaveDAC1_VDAC8_Data = WaveDAC1_VDAC8_backup.data_value;
            WaveDAC1_VDAC8_Strobe |= WaveDAC1_VDAC8_STRB_EN;
        }
        else
        {
            WaveDAC1_VDAC8_Data = WaveDAC1_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: WaveDAC1_VDAC8_Sleep
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
*  WaveDAC1_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void WaveDAC1_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(WaveDAC1_VDAC8_ACT_PWR_EN == (WaveDAC1_VDAC8_PWRMGR & WaveDAC1_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        WaveDAC1_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        WaveDAC1_VDAC8_backup.enableState = 0u;
    }
    
    WaveDAC1_VDAC8_Stop();
    WaveDAC1_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: WaveDAC1_VDAC8_Wakeup
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
*  WaveDAC1_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void WaveDAC1_VDAC8_Wakeup(void) 
{
    WaveDAC1_VDAC8_RestoreConfig();
    
    if(WaveDAC1_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        WaveDAC1_VDAC8_Enable();

        /* Restore the data register */
        WaveDAC1_VDAC8_SetValue(WaveDAC1_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
