/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer 
*
* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_cmtw_rx_config.h
* Description  : Configures the r_cmtw_rx code.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 29.08.2014 1.00    First GSCE Release.
***********************************************************************************************************************/
#ifndef CMTW_RX_CONFIG_H
#define CMTW_RX_CONFIG_H

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/
/* Parameter checking configuration */
#define CMTW_CFG_PARAM_CHECKING_ENABLE      (BSP_CFG_PARAM_CHECKING_ENABLE)

/* Acquire lock configuration */
#define CMTW_CGF_REQUIRE_LOCK               (1)

/* Enable the CMTW channels used */
#define CMTW_CFG_USE_CH0                    (1)
#define CMTW_CFG_USE_CH1                    (1)

/* Interrupt level configuration for CMTW timers */
#define CWTW_CFG_IPR_CM_CH0                 (3)
#define CMTW_CFG_IPR_OC0_CH0                (3)
#define CMTW_CFG_IPR_OC1_CH0                (3)
#define CMTW_CFG_IPR_IC0_CH0                (3)
#define CMTW_CFG_IPR_1C1_CH0                (3)
#define CWTW_CFG_IPR_CM_CH1                 (3)
#define CMTW_CFG_IPR_OC0_CH1                (3)
#define CMTW_CFG_IPR_OC1_CH1                (3)
#define CMTW_CFG_IPR_IC0_CH1                (3)
#define CMTW_CFG_IPR_1C1_CH1                (3)

#endif /* CMTW_RX_CONFIG_H */


