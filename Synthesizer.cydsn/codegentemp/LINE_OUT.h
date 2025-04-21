/*******************************************************************************
* File Name: LINE_OUT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LINE_OUT_H) /* Pins LINE_OUT_H */
#define CY_PINS_LINE_OUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LINE_OUT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LINE_OUT__PORT == 15 && ((LINE_OUT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LINE_OUT_Write(uint8 value);
void    LINE_OUT_SetDriveMode(uint8 mode);
uint8   LINE_OUT_ReadDataReg(void);
uint8   LINE_OUT_Read(void);
void    LINE_OUT_SetInterruptMode(uint16 position, uint16 mode);
uint8   LINE_OUT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LINE_OUT_SetDriveMode() function.
     *  @{
     */
        #define LINE_OUT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LINE_OUT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LINE_OUT_DM_RES_UP          PIN_DM_RES_UP
        #define LINE_OUT_DM_RES_DWN         PIN_DM_RES_DWN
        #define LINE_OUT_DM_OD_LO           PIN_DM_OD_LO
        #define LINE_OUT_DM_OD_HI           PIN_DM_OD_HI
        #define LINE_OUT_DM_STRONG          PIN_DM_STRONG
        #define LINE_OUT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LINE_OUT_MASK               LINE_OUT__MASK
#define LINE_OUT_SHIFT              LINE_OUT__SHIFT
#define LINE_OUT_WIDTH              1u

/* Interrupt constants */
#if defined(LINE_OUT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LINE_OUT_SetInterruptMode() function.
     *  @{
     */
        #define LINE_OUT_INTR_NONE      (uint16)(0x0000u)
        #define LINE_OUT_INTR_RISING    (uint16)(0x0001u)
        #define LINE_OUT_INTR_FALLING   (uint16)(0x0002u)
        #define LINE_OUT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LINE_OUT_INTR_MASK      (0x01u) 
#endif /* (LINE_OUT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LINE_OUT_PS                     (* (reg8 *) LINE_OUT__PS)
/* Data Register */
#define LINE_OUT_DR                     (* (reg8 *) LINE_OUT__DR)
/* Port Number */
#define LINE_OUT_PRT_NUM                (* (reg8 *) LINE_OUT__PRT) 
/* Connect to Analog Globals */                                                  
#define LINE_OUT_AG                     (* (reg8 *) LINE_OUT__AG)                       
/* Analog MUX bux enable */
#define LINE_OUT_AMUX                   (* (reg8 *) LINE_OUT__AMUX) 
/* Bidirectional Enable */                                                        
#define LINE_OUT_BIE                    (* (reg8 *) LINE_OUT__BIE)
/* Bit-mask for Aliased Register Access */
#define LINE_OUT_BIT_MASK               (* (reg8 *) LINE_OUT__BIT_MASK)
/* Bypass Enable */
#define LINE_OUT_BYP                    (* (reg8 *) LINE_OUT__BYP)
/* Port wide control signals */                                                   
#define LINE_OUT_CTL                    (* (reg8 *) LINE_OUT__CTL)
/* Drive Modes */
#define LINE_OUT_DM0                    (* (reg8 *) LINE_OUT__DM0) 
#define LINE_OUT_DM1                    (* (reg8 *) LINE_OUT__DM1)
#define LINE_OUT_DM2                    (* (reg8 *) LINE_OUT__DM2) 
/* Input Buffer Disable Override */
#define LINE_OUT_INP_DIS                (* (reg8 *) LINE_OUT__INP_DIS)
/* LCD Common or Segment Drive */
#define LINE_OUT_LCD_COM_SEG            (* (reg8 *) LINE_OUT__LCD_COM_SEG)
/* Enable Segment LCD */
#define LINE_OUT_LCD_EN                 (* (reg8 *) LINE_OUT__LCD_EN)
/* Slew Rate Control */
#define LINE_OUT_SLW                    (* (reg8 *) LINE_OUT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LINE_OUT_PRTDSI__CAPS_SEL       (* (reg8 *) LINE_OUT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LINE_OUT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LINE_OUT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LINE_OUT_PRTDSI__OE_SEL0        (* (reg8 *) LINE_OUT__PRTDSI__OE_SEL0) 
#define LINE_OUT_PRTDSI__OE_SEL1        (* (reg8 *) LINE_OUT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LINE_OUT_PRTDSI__OUT_SEL0       (* (reg8 *) LINE_OUT__PRTDSI__OUT_SEL0) 
#define LINE_OUT_PRTDSI__OUT_SEL1       (* (reg8 *) LINE_OUT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LINE_OUT_PRTDSI__SYNC_OUT       (* (reg8 *) LINE_OUT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LINE_OUT__SIO_CFG)
    #define LINE_OUT_SIO_HYST_EN        (* (reg8 *) LINE_OUT__SIO_HYST_EN)
    #define LINE_OUT_SIO_REG_HIFREQ     (* (reg8 *) LINE_OUT__SIO_REG_HIFREQ)
    #define LINE_OUT_SIO_CFG            (* (reg8 *) LINE_OUT__SIO_CFG)
    #define LINE_OUT_SIO_DIFF           (* (reg8 *) LINE_OUT__SIO_DIFF)
#endif /* (LINE_OUT__SIO_CFG) */

/* Interrupt Registers */
#if defined(LINE_OUT__INTSTAT)
    #define LINE_OUT_INTSTAT            (* (reg8 *) LINE_OUT__INTSTAT)
    #define LINE_OUT_SNAP               (* (reg8 *) LINE_OUT__SNAP)
    
	#define LINE_OUT_0_INTTYPE_REG 		(* (reg8 *) LINE_OUT__0__INTTYPE)
#endif /* (LINE_OUT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LINE_OUT_H */


/* [] END OF FILE */
