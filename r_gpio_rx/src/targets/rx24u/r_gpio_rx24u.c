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
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx24u.c
* Description  : Data for r_gpio_rx driver specific to RX24U.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.12.2016 1.00    First Release
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

#if defined(BSP_MCU_RX24U)

/* Public interface header file for this package. */
#include "r_gpio_rx_if.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* These arrays hold which pins have extra functionality. For example, not all pins have the option of enabling
 * open-drain N-channel output instead of the default CMOS output. Each entry in the array corresponds to a port.
 * Each bit in each entry corresponds to a pin on that port. If bit 3 of array entry [4] was set to 1 then that would
 * mean that PORT 4 PIN 3 supported the feature that array represented.
 *
 * These arrays are only used when GPIO_CFG_PARAM_CHECKING_ENABLE is set to 1 (checking enabled). If you know that
 * your code does not need to check the pins then you can set this macro to 0 and save a little execution time
 * and ROM space.
 *
 * Note: These arrays are defined for the largest package part. For smaller packages where some pins do not exist,
 *       pin checking is filtered by the enumerated port_pin list for that package as defined in r_gpio_rx24u.h.
 */

#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
const uint8_t g_gpio_open_drain_n_support[GPIO_INFO_NUM_PORTS] =
{
    0x07,     //PORT0   P00 to P02
    0xFF,     //PORT1   P10 to P17
    0xFF,     //PORT2   P20 to P27
    0xFF,     //PORT3   P30 to P37
    0x00,     //PORT4   None
    0x00,     //PORT5   None
    0x00,     //PORT6   None
    0x7F,     //PORT7   P70 to P76
    0x1F,     //PORT8   P80 to P84
    0x7F,     //PORT9   P90 to P96
    0xFF,     //PORTA   PA0 to PA7
    0xFF,     //PORTB   PB0 to PB7
    0x7F,     //PORTC   PC0 to PC6
    0xFF,     //PORTD   PD0 to PD7
    0x7B,     //PORTE   PE0, PE1, PE3 to PE6
    0x0F,     //PORTF   PF0 to PF3
    0x07,     //PORTG   PG0 to PG2
};

const uint8_t g_gpio_open_drain_p_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0x00,     //PORT1   None
    0x00,     //PORT2   None
    0x00,     //PORT3   None
    0x00,     //PORT4   None
    0x00,     //PORT5   None
    0x00,     //PORT6   None
    0x00,     //PORT7   None
    0x00,     //PORT8   None
    0x00,     //PORT9   None
    0x00,     //PORTA   None
    0x00,     //PORTB   None
    0x00,     //PORTC   None
    0x00,     //PORTD   None
    0x00,     //PORTE   None
    0x00,     //PORTF   None
    0x00,     //PORTG   None
};

const uint8_t g_gpio_pull_up_support[GPIO_INFO_NUM_PORTS] =
{
    0x07,     //PORT0   P00 to P02
    0xFF,     //PORT1   P10 to P17
    0xFF,     //PORT2   P20 to P27
    0xFF,     //PORT3   P30 to P37
    0xFF,     //PORT4   P40 to P47
    0x3F,     //PORT5   P50 to P55
    0x3F,     //PORT6   P60 to P65
    0x7F,     //PORT7   P70 to P76
    0x1F,     //PORT8   P80 to P84
    0x7F,     //PORT9   P90 to P96
    0xFF,     //PORTA   PA0 to PA7
    0xFF,     //PORTB   PB0 to PB7
    0x7F,     //PORTC   PC0 to PC6
    0xFF,     //PORTD   PD0 to PD7
    0x7B,     //PORTE   PE0, PE1, PE3 to PE6
    0x0F,     //PORTF   PF0 to PF3
    0x07,     //PORTG   PG0 to PG2
};

const uint8_t g_gpio_dscr_support[GPIO_INFO_NUM_PORTS] =
{
    0x07,     //PORT0   P00 to P02
    0xFF,     //PORT1   P10 to P17
    0xFF,     //PORT2   P20 to P27
    0x3F,     //PORT3   P30 to P35
    0x00,     //PORT4   None
    0x00,     //PORT5   None
    0x00,     //PORT6   None
    0x01,     //PORT7   P70
    0x1D,     //PORT8   P80, P82 to P84
    0x40,     //PORT9   P96
    0xFF,     //PORTA   PA0 to PA7
    0xD9,     //PORTB   PB0, PB3, PB4, PB6, PB7
    0x7F,     //PORTC   PC0 to PC6
    0xF7,     //PORTD   PD0 to PD2, PD4 to PD7
    0x7B,     //PORTE   PE0, PE1, PE3 to PE6
    0x0F,     //PORTF   PF0 to PF3
    0x07,     //PORTG   PG0 to PG2
};

#endif

#endif

