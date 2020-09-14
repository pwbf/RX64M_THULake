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
* File Name    : r_cmt_user.c
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
* Function Name: R_r_cmt_Create_UserInit
* Description  : This function adds user code after initializing the CMTW0 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_r_cmt_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_r_cmt_cmwi0_interrupt
* Description  : This function is CMWI0 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_CMTW0_CMWI0
#pragma interrupt r_r_cmt_cmwi0_interrupt(vect=VECT(CMTW0,CMWI0),fint)
#else
#pragma interrupt r_r_cmt_cmwi0_interrupt(vect=VECT(CMTW0,CMWI0))
#endif
static void r_r_cmt_cmwi0_interrupt(void)
{
    /* Start user code for r_r_cmt_cmwi0_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_r_cmt_ic0i0_interrupt
* Description  : This function is IC0I0 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_PERIB_INTB168
#pragma interrupt r_r_cmt_ic0i0_interrupt(vect=VECT(PERIB,INTB168),fint)
#else
#pragma interrupt r_r_cmt_ic0i0_interrupt(vect=VECT(PERIB,INTB168))
#endif
static void r_r_cmt_ic0i0_interrupt(void)
{
    /* Start user code for r_r_cmt_ic0i0_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_r_cmt_ic1i0_interrupt
* Description  : This function is IC1I0 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_PERIB_INTB169
#pragma interrupt r_r_cmt_ic1i0_interrupt(vect=VECT(PERIB,INTB169),fint)
#else
#pragma interrupt r_r_cmt_ic1i0_interrupt(vect=VECT(PERIB,INTB169))
#endif
static void r_r_cmt_ic1i0_interrupt(void)
{
    /* Start user code for r_r_cmt_ic1i0_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_r_cmt_oc0i0_interrupt
* Description  : This function is OC0I0 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_PERIB_INTB170
#pragma interrupt r_r_cmt_oc0i0_interrupt(vect=VECT(PERIB,INTB170),fint)
#else
#pragma interrupt r_r_cmt_oc0i0_interrupt(vect=VECT(PERIB,INTB170))
#endif
static void r_r_cmt_oc0i0_interrupt(void)
{
    /* Start user code for r_r_cmt_oc0i0_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_r_cmt_oc1i0_interrupt
* Description  : This function is OC0I0 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_PERIB_INTB171
#pragma interrupt r_r_cmt_oc1i0_interrupt(vect=VECT(PERIB,INTB171),fint)
#else
#pragma interrupt r_r_cmt_oc1i0_interrupt(vect=VECT(PERIB,INTB171))
#endif
static void r_r_cmt_oc1i0_interrupt(void)
{
    /* Start user code for r_r_cmt_oc1i0_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */   




