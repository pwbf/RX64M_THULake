/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cmt.c
* Version      : 1.8.0
* Device(s)    : R5F564MLCxFC
* Description  : This file implements device driver for r_cmt.
* Creation Date: 2020-04-24
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cmt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_r_cmt_Create
* Description  : This function initializes the CMTW0 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_r_cmt_Create(void)
{
    /* Disable CMWI0 interrupt */
    IEN(CMTW0,CMWI0) = 0U;

    /* Disable IC0I0 interrupt */
    IEN(PERIB,INTB168) = 0U;

    /* Disable IC1I0 interrupt */
    IEN(PERIB,INTB169) = 0U;

    /* Disable OC0I0 interrupt */
    IEN(PERIB,INTB170) = 0U;

    /* Disable OC1I0 interrupt */
    IEN(PERIB,INTB171) = 0U;

    /* Cancel CMTW stop state in LPC */
    MSTP(CMTW0) = 0U;

    /* Stop CMTW0 count */
    CMTW0.CMWSTR.BIT.STR = 0U;
 
    /* Set timer I/O control register */
    CMTW0.CMWIOR.WORD = _0010_CMTW_CMWIOR_IC0E_ENABLE | _0000_CMTW_CMWIOR_IC0_RISE | _0020_CMTW_CMWIOR_IC1E_ENABLE | 
                        _0000_CMTW_CMWIOR_IC1_RISE | _1000_CMTW_CMWIOR_OC0E_ENABLE | _0000_CMTW_CMWIOR_OC0_RETAIN | 
                        _2000_CMTW_CMWIOR_OC1E_ENABLE | _0000_CMTW_CMWIOR_OC1_RETAIN | _8000_CMTW_CMWIOR_CMWE_ENABLE;

    /* Set compare match register */
    CMTW0.CMWCOR = _000002ED_CMTW0_CMWCOR_VALUE;

    /* Set output compare register 0 */
    CMTW0.CMWOCR0 = _0000000A_CMTW0_CMWOCR0_VALUE;

    /* Set output compare register 1 */
    CMTW0.CMWOCR1 = _0000000A_CMTW0_CMWOCR1_VALUE;

    /* Set control registers */
    CMTW0.CMWCR.WORD = _0000_CMTW_CMWCR_CLOCK_PCLK8 | _0008_CMTW_CMWCR_CMWIE_ENABLE | _0010_CMTW_CMWCR_IC0IE_ENABLE | 
                       _0020_CMTW_CMWCR_IC1IE_ENABLE | _0040_CMTW_CMWCR_OC0IE_ENABLE | _0080_CMTW_CMWCR_OC1IE_ENABLE | 
                       _0000_CMTW_CMWCR_COUNTER_SIZE_32 | _0000_CMTW_CMWCR_CCLR_ENABLE_CMWCOR;

    /* Set CMWI0 priority level */
    IPR(CMTW0,CMWI0) = _0F_CMTW_PRIORITY_LEVEL15;

    /* Set IC0I0 interrupt and priority level */
    ICU.SLIBR168.BYTE = 0x29U;
    IPR(PERIB,INTB168) = _0F_CMTW_PRIORITY_LEVEL15;

    /* Set IC1I0 interrupt and priority level */
    ICU.SLIBR169.BYTE = 0x2AU;
    IPR(PERIB,INTB169) = _0F_CMTW_PRIORITY_LEVEL15;

    /* Set OC0I0 interrupt and priority level */
    ICU.SLIBR170.BYTE = 0x2BU;
    IPR(PERIB,INTB170) = _0F_CMTW_PRIORITY_LEVEL15;

    /* Set OC1I0 interrupt and priority level */
    ICU.SLIBR171.BYTE = 0x2CU;
    IPR(PERIB,INTB171) = _0F_CMTW_PRIORITY_LEVEL15;

    /* Set TIC0 pin */
    MPC.PC6PFS.BYTE = 0x1DU;
    PORTC.PMR.BYTE |= 0x40U;

    /* Set TIC1 pin */
    MPC.PE6PFS.BYTE = 0x1DU;
    PORTE.PMR.BYTE |= 0x40U;

    /* Set TOC0 pin */
    MPC.PC7PFS.BYTE = 0x1DU;
    PORTC.PMR.BYTE |= 0x80U;

    /* Set TOC1 pin */
    MPC.PE7PFS.BYTE = 0x1DU;
    PORTE.PMR.BYTE |= 0x80U;

    R_r_cmt_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_r_cmt_Start
* Description  : This function starts the CMTW0 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_r_cmt_Start(void)
{
    /* Enable CMWI0 interrupt in ICU */
    IEN(CMTW0,CMWI0) = 1U;

    /* Enable IC0I0 interrupt in ICU */
    IEN(PERIB,INTB168) = 1U;

    /* Enable IC1I0 interrupt in ICU */
    IEN(PERIB,INTB169) = 1U;

    /* Enable OC0I0 interrupt in ICU */
    IEN(PERIB,INTB170) = 1U;

    /* Enable OC1I0 interrupt in ICU */
    IEN(PERIB,INTB171) = 1U;

    /* Start CMTW0 count */
    CMTW0.CMWSTR.BIT.STR = 1U;
}

/***********************************************************************************************************************
* Function Name: R_r_cmt_Stop
* Description  : This function stop the CMT0 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_r_cmt_Stop(void)
{
    /* Stop CMTW0 count */
    CMTW0.CMWSTR.BIT.STR = 0U;

    /* Disable CMWI0 interrupt in ICU */
    IEN(CMTW0,CMWI0) = 0U;

    /* Disable IC0I0 interrupt in ICU */
    IEN(PERIB,INTB168) = 0U;

    /* Disable IC1I0 interrupt in ICU */
    IEN(PERIB,INTB169) = 0U;

    /* Disable OC0I0 interrupt in ICU */
    IEN(PERIB,INTB170) = 0U;

    /* Disable OC1I0 interrupt in ICU */
    IEN(PERIB,INTB171) = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */   

