/*******************************************************************************
* File Name: SEL.h  
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

#if !defined(CY_PINS_SEL_H) /* Pins SEL_H */
#define CY_PINS_SEL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SEL_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SEL__PORT == 15 && ((SEL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SEL_Write(uint8 value);
void    SEL_SetDriveMode(uint8 mode);
uint8   SEL_ReadDataReg(void);
uint8   SEL_Read(void);
void    SEL_SetInterruptMode(uint16 position, uint16 mode);
uint8   SEL_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SEL_SetDriveMode() function.
     *  @{
     */
        #define SEL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SEL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SEL_DM_RES_UP          PIN_DM_RES_UP
        #define SEL_DM_RES_DWN         PIN_DM_RES_DWN
        #define SEL_DM_OD_LO           PIN_DM_OD_LO
        #define SEL_DM_OD_HI           PIN_DM_OD_HI
        #define SEL_DM_STRONG          PIN_DM_STRONG
        #define SEL_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SEL_MASK               SEL__MASK
#define SEL_SHIFT              SEL__SHIFT
#define SEL_WIDTH              1u

/* Interrupt constants */
#if defined(SEL__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SEL_SetInterruptMode() function.
     *  @{
     */
        #define SEL_INTR_NONE      (uint16)(0x0000u)
        #define SEL_INTR_RISING    (uint16)(0x0001u)
        #define SEL_INTR_FALLING   (uint16)(0x0002u)
        #define SEL_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SEL_INTR_MASK      (0x01u) 
#endif /* (SEL__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SEL_PS                     (* (reg8 *) SEL__PS)
/* Data Register */
#define SEL_DR                     (* (reg8 *) SEL__DR)
/* Port Number */
#define SEL_PRT_NUM                (* (reg8 *) SEL__PRT) 
/* Connect to Analog Globals */                                                  
#define SEL_AG                     (* (reg8 *) SEL__AG)                       
/* Analog MUX bux enable */
#define SEL_AMUX                   (* (reg8 *) SEL__AMUX) 
/* Bidirectional Enable */                                                        
#define SEL_BIE                    (* (reg8 *) SEL__BIE)
/* Bit-mask for Aliased Register Access */
#define SEL_BIT_MASK               (* (reg8 *) SEL__BIT_MASK)
/* Bypass Enable */
#define SEL_BYP                    (* (reg8 *) SEL__BYP)
/* Port wide control signals */                                                   
#define SEL_CTL                    (* (reg8 *) SEL__CTL)
/* Drive Modes */
#define SEL_DM0                    (* (reg8 *) SEL__DM0) 
#define SEL_DM1                    (* (reg8 *) SEL__DM1)
#define SEL_DM2                    (* (reg8 *) SEL__DM2) 
/* Input Buffer Disable Override */
#define SEL_INP_DIS                (* (reg8 *) SEL__INP_DIS)
/* LCD Common or Segment Drive */
#define SEL_LCD_COM_SEG            (* (reg8 *) SEL__LCD_COM_SEG)
/* Enable Segment LCD */
#define SEL_LCD_EN                 (* (reg8 *) SEL__LCD_EN)
/* Slew Rate Control */
#define SEL_SLW                    (* (reg8 *) SEL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SEL_PRTDSI__CAPS_SEL       (* (reg8 *) SEL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SEL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SEL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SEL_PRTDSI__OE_SEL0        (* (reg8 *) SEL__PRTDSI__OE_SEL0) 
#define SEL_PRTDSI__OE_SEL1        (* (reg8 *) SEL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SEL_PRTDSI__OUT_SEL0       (* (reg8 *) SEL__PRTDSI__OUT_SEL0) 
#define SEL_PRTDSI__OUT_SEL1       (* (reg8 *) SEL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SEL_PRTDSI__SYNC_OUT       (* (reg8 *) SEL__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SEL__SIO_CFG)
    #define SEL_SIO_HYST_EN        (* (reg8 *) SEL__SIO_HYST_EN)
    #define SEL_SIO_REG_HIFREQ     (* (reg8 *) SEL__SIO_REG_HIFREQ)
    #define SEL_SIO_CFG            (* (reg8 *) SEL__SIO_CFG)
    #define SEL_SIO_DIFF           (* (reg8 *) SEL__SIO_DIFF)
#endif /* (SEL__SIO_CFG) */

/* Interrupt Registers */
#if defined(SEL__INTSTAT)
    #define SEL_INTSTAT            (* (reg8 *) SEL__INTSTAT)
    #define SEL_SNAP               (* (reg8 *) SEL__SNAP)
    
	#define SEL_0_INTTYPE_REG 		(* (reg8 *) SEL__0__INTTYPE)
#endif /* (SEL__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SEL_H */


/* [] END OF FILE */
