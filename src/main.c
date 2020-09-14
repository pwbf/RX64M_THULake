
/*******************************************************************************
* File Name     : main.c
* Version       : 1.00
* Device(s)     : RX family
* Tool-Chain    : C/C++ Compiler Package for RX Family
* OS            :
* H/W Platform  : RX family board
* Description   :
* Operation     :
*
* Limitations   :
******************************************************************************/
/******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 2018.11.13 V1.00    First Release
*               :
*               :
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/
#define ETHERNET_FUNCTION_ENABLE 0

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>



#if ETHERNET_FUNCTION_ENABLE

/*For Ethernet*/
#include "r_t4_itcpip.h"
#include "r_sys_time_rx_if.h"
#include "echo_srv_sample.h"
#endif

/*For SCI*/
#include "r_sci_rx_if.h"        // The SCI module API interface file.
#include "r_byteq_if.h"         // The BYTEQ module API interface file.
#include "r_sci_rx_config.h"    // User configurable options for the SCI module

/*For LoRa*/
#include "LoRa.h"

/*For Sensor*/
#include "Sensor.h"

// uint8_t sensorSenduint8(uint8_t func);
// void sensorRead(uint8_t status);

/******************************************************************************
Macro definitions
******************************************************************************/
#if ETHERNET_FUNCTION_ENABLE
#if (APPLICATION_T4_CHANNEL_NUM  == (2))
#define T4_WORK_SIZE (9112)  /* Maximum size used in echo server sample program */
#elif (APPLICATION_T4_CHANNEL_NUM == (1))
#define T4_WORK_SIZE (4412)  /* Maximum size used in echo server sample program */
#endif
#endif

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
extern void echo_srv(void);

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
void main(void);
void init_mtu0(void);   			/*For ADC*/
void MyCallback(void *pArgs);   	/*For ADC*/

// uint8_t HLbyte(uint8_t HIGH, uint8_t LOW);

/******************************************************************************
Private global variables and functions
******************************************************************************/
#if ETHERNET_FUNCTION_ENABLE
static UW tcpudp_work[T4_WORK_SIZE / 4 + 1];
#endif

/*For UART.Begin*/
void my_sci_callback_ch1(void *pArgs);
void my_sci_callback_ch2(void *pArgs);
void my_sci_callback_ch7(void *pArgs);
static void Rx64MInitPorts(void);
static void UARTInit(void);

/* Handle storage. Needs to persist as long as SCI calls are going to be made.*/
static sci_hdl_t   g_my_sci_handle;
static sci_hdl_t   g_my_sci_handle_ch1;		//For LoRa
static sci_hdl_t   g_my_sci_handle_ch2;		//For Sensor
/*For UART. End*/

/*Custome global variable declaration end*/
#define LED1            (PORTE.PODR.BIT.B1)
#define LED_ON          (0)
#define LED_OFF         (1)

#define DEBUG_MODE	(0)
/******************************************************************************
* Function Name : main
* Declaration   : void main(void)
* Description   : This function is main processing
* Arguments     : none
* Return value  : none
******************************************************************************/

uint8_t rtnSend = 0;
uint8_t RecValue[1] = {0};
uint8_t rtnData[13];
uint8_t sendCMD[40];
	int i = 0;
uint8_t *pValue = &RecValue;
int rtnRecieve;
void LORA_Recieve(uint8_t status);

void LoRaJoin(){
	printf("Send: mac join abp\n");
	rtnSend = R_SCI_Send(g_my_sci_handle_ch1,"mac join abp",12);
	R_BSP_SoftwareDelay (1, BSP_DELAY_SECS);
	LORA_Recieve(rtnSend);
}


void LORA_Recieve(uint8_t status){
	*pValue = &RecValue;
	printf("Send Status=0x%02X\n",status);
	printf("Return:\n");
	while(rtnSend == SCI_SUCCESS){
		rtnRecieve = R_SCI_Receive(g_my_sci_handle_ch1,pValue,1);
		if(rtnRecieve == SCI_SUCCESS){
			printf("%c",RecValue[0]);
		}
		else{
			//printf("Receive Status=0x%02X\n",rtnRecieve);
			break;
		}
	}	
}

uint8_t sensorSend(){
	uint8_t cmd[8];
	sprintf(cmd,"%c%c%c%c%c%c%c%c",SENS_ADDR,SENS_FUNC_READ,SENS_REG_READ_STARTH,SENS_REG_READ_STARTL,SENS_REG_COUNTH,SENS_REG_COUNTL,0x40,0x08);
	R_SCI_Send(g_my_sci_handle_ch2,cmd,HOST_SEND_LENGTH);
	return 0;
}

void sensorRead(uint8_t status){
	*pValue = &RecValue;
	while(status == SCI_SUCCESS){
		rtnRecieve = R_SCI_Receive(g_my_sci_handle_ch2,pValue,1);
		if(rtnRecieve == SCI_SUCCESS){
			rtnData[i++] = RecValue[0];
			printf("0X%2x",RecValue[0]);
		}
		else{
			i=0;
			printf("Receive Status=0x%02X\n",rtnRecieve);
			break;
		}
		R_BSP_SoftwareDelay (100, BSP_DELAY_MILLISECS);
	}	
}


void main(void){
	PORTE.PDR.BIT.B1=1;
	
	Rx64MInitPorts();
	UARTInit();
	LoRaJoin();
	R_BSP_SoftwareDelay (1, BSP_DELAY_SECS);
	
	LED1=LED_OFF;
	sensorSend();
	R_BSP_SoftwareDelay (1, BSP_DELAY_SECS);
	
    while (1){
		LED1=LED_ON;
		printf("sensorRead\n");
		sensorRead(0);
		if(rtnData[12] != 0x00){
			break;
		}
	}
    
	sprintf(sendCMD,"mac tx ucnf 2 %02x%02x%02x%02x%02x%02x%02x%02x",
	rtnData[3],rtnData[4],
	rtnData[5],rtnData[6],
	rtnData[7],rtnData[8],
	rtnData[9],rtnData[10]);
	printf("Send Data\n");
	rtnSend = R_SCI_Send(g_my_sci_handle_ch1,sendCMD,40);
	R_BSP_SoftwareDelay (1, BSP_DELAY_SECS);
	LORA_Recieve(rtnSend);
	
	printf("\n\nEnded\n");

	LED1=LED_OFF;
	R_BSP_SoftwareDelay (100, BSP_DELAY_MILLISECS);
}

/*****************************************************************************/
/*Functions for . Begin*/
/*****************************************************************************/


/*****************************************************************************
* Function Name: init_mtu0
* Description  : This function inits MTU0 to periodically trigger ADC
conversion
*                when a a compare match with the TGRA register occurs. For
*                demonstration purposes it also enables the MTU0 TGIA0
*                (TGRA input capture/compare match) interrupt which
*                causes the registered interrupt handler mtu0_tgia0_isr()
*                below to be called and toggles LED2 each time 10 TGRA matches
*                occur.
* Arguments    : none
* Return Value : none
******************************************************************************/
void init_mtu0(void){
    SYSTEM.PRCR.WORD = 0xA502;
    MSTP(MTU0) = 0;             // Release from module stop state.
    SYSTEM.PRCR.WORD = 0xA500;

    MTU.TSTRA.BYTE = 0x00;      // Stop MTU counters

    // Timer Control Reg (TCR)
    // CCLR[2:0] = 001: TCNT cleared by TGRA compare match/input capture
    // CKEG[1:0] = 00 : Count at rising edge
    // TPSC[2:0] = 011: Time Prescaler Select; Internal clock: counts on PCLKA/64
    MTU0.TCR.BYTE = 0x23;

    MTU0.TIORH.BYTE = 0x00;     // IO control A/B output prohibited
    MTU0.TIORL.BYTE = 0x00;     // IO control C/D output prohibited

    MTU0.TMDR1.BYTE = 0x00;     // Normal mode

    MTU0.TCNT = 0;              // Clear timer counter
    MTU0.TGRA = 60000;          // Set the compare match count value

    MTU0.TIER.BIT.TTGE = 1;     // Trigger ADC on TRGA compare match (TRGA0N sync trigger)

    /* Enable the TGIA0 (TGRA input capture/compare match) interrupt which will
     * cause the mtu0_tgia0_isr() ISR below to be called each time a TGRA compare
     * match occurs. Note that this is not required to periodically start the ADC
     * conversion (that occurs because MTU0.TIER.BIT.TTGE is set above whenever a
     * compare match occurs). */
    IR(MTU0,TGIA0) = 0;         // Clear the interrupt status flag
    IPR(MTU0,TGIA0) = 9;        // Set the interrupt source priority
    IEN(MTU0,TGIA0) = 1;        // Enable the interrupt request
    MTU0.TIER.BIT.TGIEA = 1;    // Enable TGIA interrupts

    MTU.TSTRA.BYTE = 0x01;      // Start counting on MTU0
}

/*****************************************************************************/
/*Functions for ADC. End*/
/*****************************************************************************/



/*****************************************************************************/
/*Functions for UART.Begin*/
/*****************************************************************************/

/*****************************************************************************
* Function Name: SendSCIVersion
* Description  :
* Arguments   :
* Return Value : none
******************************************************************************/
static void SendSCIVersion(void){
        uint32_t    my_version;
        //uint8_t     my_char;
        uint8_t version_str[12] = {0};

        /* Get module software version using the API function provided. */
        my_version = R_SCI_GetVersion();

        /* Demonstrate parsing and formatting of version number. */
        sprintf((char *)version_str, "SCIv%1.0hu.%2.2hu\r\n", ((my_version >> 16)&0xf), (my_version & 0xff));

    #if 0
    sci_err_t   my_sci_err;
        /* Wait to get a character from the terminal so we know that it is ready. */
        do
        {
        my_sci_err = R_SCI_Receive(g_my_sci_handle, &my_char, 1);
        } while (SCI_ERR_INSUFFICIENT_DATA == my_sci_err);
    #endif

        /* Now send the version string out through the serial port to the terminal. */
        R_SCI_Send(g_my_sci_handle, version_str, 10);

}

/*****************************************************************************
* Function Name: UARTInit
* Description  :
* Arguments   :
* Return Value : none
******************************************************************************/
static void UARTInit(void){
        sci_cfg_t   my_sci_config;
        sci_err_t   my_sci_err_ch1;
        sci_err_t   my_sci_err_ch2;

    /**********************************************************************************/
        /* Set up the configuration data structure for asynchronous (UART) operation. */
        my_sci_config.async.baud_rate    = 9600;
        my_sci_config.async.clk_src      = SCI_CLK_INT;
        my_sci_config.async.data_size    = SCI_DATA_8BIT;
        my_sci_config.async.parity_en    = SCI_PARITY_OFF;
        my_sci_config.async.parity_type  = SCI_EVEN_PARITY;
        my_sci_config.async.stop_bits    = SCI_STOPBITS_1;
        my_sci_config.async.int_priority = 15;    // 1=lowest, 15=highest

        /* OPEN ASYNC CHANNEL
        *  Provide address of the config structure,
        *  the callback function to be assigned,
        *  and the location for the handle to be stored.*/     
		
		/*Use channel 1 & 2*/
		my_sci_err_ch1 = R_SCI_Open(SCI_CH1, SCI_MODE_ASYNC, &my_sci_config, my_sci_callback_ch1, &g_my_sci_handle_ch1);
		my_sci_err_ch2 = R_SCI_Open(SCI_CH2, SCI_MODE_ASYNC, &my_sci_config, my_sci_callback_ch2, &g_my_sci_handle_ch2);

        /* If there were an error this would demonstrate error detection of API calls. */
        if (SCI_SUCCESS != my_sci_err_ch1)
        {
			printf("SCI_Open_Ch1_Error!!\n");
        }
		
		if (SCI_SUCCESS != my_sci_err_ch2)
        {
			printf("SCI_Open_Ch2_Error!!\n");
        }
}

/*****************************************************************************
* Function Name: my_sci_callback
* Description  : This is a template for an SCI Async Mode callback function.
* Arguments    : pArgs -
*                    pointer to sci_cb_args_t structure cast to a void. Structure
*                    contains event and associated data.
* Return Value : none
******************************************************************************/
void my_sci_callback_ch2(void *pArgs){
	sci_cb_args_t   *args;

    args = (sci_cb_args_t *)pArgs;

    if (args->event == SCI_EVT_RX_CHAR)
    {
        /* From RXI interrupt; received character data is in args->byte */
        nop();
    }
    else if (args->event == SCI_EVT_RXBUF_OVFL)
    {
        /* From RXI interrupt; rx queue is full; 'lost' data is in args->byte
           You will need to increase buffer size or reduce baud rate */
        nop();
    }
    else if (args->event == SCI_EVT_OVFL_ERR)
    {
        /* From receiver overflow error interrupt; error data is in args->byte
           Error condition is cleared in calling interrupt routine */
        nop();
    }
    else if (args->event == SCI_EVT_FRAMING_ERR)
    {
        /* From receiver framing error interrupt; error data is in args->byte
           Error condition is cleared in calling interrupt routine */
        nop();
    }
    else if (args->event == SCI_EVT_PARITY_ERR)
    {
        /* From receiver parity error interrupt; error data is in args->byte
           Error condition is cleared in calling interrupt routine */
        nop();
    }
}

void my_sci_callback_ch1(void *pArgs){
	sci_cb_args_t   *args;

    args = (sci_cb_args_t *)pArgs;

    if (args->event == SCI_EVT_RX_CHAR)
    {
        /* From RXI interrupt; received character data is in args->byte */
        nop();
    }
    else if (args->event == SCI_EVT_RXBUF_OVFL)
    {
        /* From RXI interrupt; rx queue is full; 'lost' data is in args->byte
           You will need to increase buffer size or reduce baud rate */
        nop();
    }
    else if (args->event == SCI_EVT_OVFL_ERR)
    {
        /* From receiver overflow error interrupt; error data is in args->byte
           Error condition is cleared in calling interrupt routine */
        nop();
    }
    else if (args->event == SCI_EVT_FRAMING_ERR)
    {
        /* From receiver framing error interrupt; error data is in args->byte
           Error condition is cleared in calling interrupt routine */
        nop();
    }
    else if (args->event == SCI_EVT_PARITY_ERR)
    {
        /* From receiver parity error interrupt; error data is in args->byte
           Error condition is cleared in calling interrupt routine */
        nop();
    }
}


/*****************************************************************************/
/*Functions for UART.End*/
/*****************************************************************************/

/*****************************************************************************
* Function Name: sci_rx65N_init_ports
* Description  : This function initializes the port pins associated with SCI
*                channel 2, which is connected to the USB serial port Virtual
*                COM Interface.
* Arguments    : none
* Return Value : none
******************************************************************************/
static void Rx64MInitPorts(void){
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); // Use BSP function to unlock the MPC register.

	/*Sensor*/
	/*For SCI-UART_ch2*/
        /* Set RXD2 pin */  /*P52*/
        MPC.P52PFS.BYTE = 0x0A;
        PORT5.PMR.BYTE |= 0x04;    // Set P52 mode to peripheral operation
        /* Set TXD2 pin */  /*P50*/
        PORT5.PODR.BYTE |= 0x01;
        MPC.P50PFS.BYTE = 0x0A;
        PORT5.PMR.BYTE |= 0x01;  // Set P50 mode to peripheral operation
        PORT5.PDR.BYTE |= 0x01;	
		
	/*LoRa*/
	/*For SCI-UART_ch1*/ 
        /* Set RXD1 pin */  /*P15*/
        MPC.P15PFS.BYTE = 0x0A;
        PORT1.PMR.BYTE |= 0x20;    // Set P21 mode to peripheral operation

        /* Set TXD1 pin */  /*P26*/
        PORT2.PODR.BYTE |= 0x40;
        MPC.P26PFS.BYTE = 0x0A;
        PORT2.PMR.BYTE |= 0x40;  // Set P26 mode to peripheral operation
        PORT2.PDR.BYTE |= 0x40;

        return;
}






