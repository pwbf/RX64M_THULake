#include "main_self.h"

/*General Setting section start*/
#define		WATCH_DOG		1500
#define		RTN_LENGTH		13
#define		TOTAL_POINT		7
#define		SoftwareRST		TOTAL_POINT

uint16_t	NULL_COUNTER	= 0;
uint8_t		ROUND_TIMER		= 0;
uint8_t		LOCAL_LOOP		= 0;
uint8_t		POINT_LOC		= 1;

/*General Setting section end*/

uint8_t rtnSend = 0;
uint8_t RecValue[1] = {0};
uint8_t sensorData[RTN_LENGTH];
uint8_t *psensorData = sensorData;
uint8_t sendCMD[40];
uint8_t *pValue = &RecValue;
uint8_t rtnRecieve;
uint8_t clacData[8] = {0};
uint8_t *pclacData = clacData;

uint64_t GLOBALCOUNTER = 0;

void LED(int x,int y,int z,int a,int b){
     if(x==1 && y==0 && z==0 && a==0 && b==0){
	     return LED_LoRa_join=LED_ON;
     }
     else if(x==0 && y==1 && z==0 && a==0 && b==0){
	     return LED_LoRa_tx=LED_ON;
     }
     else if(x==0 && y==0 && z==1 && a==0 && b==0){
	     return LED_LoRa_rx=LED_ON;
     }
     else if(x==0 && y==0 && z==0 && a==1 && b==0){
	     return LED_Sens_tx=LED_ON;
     }
     else if(x==0 && y==0 && z==0 && a==0 && b==1){
	     return LED_Sens_rx=LED_ON;
     }
     else if(x==0 && y==0 && z==0 && a==0 && b==0){
	     return LED_LoRa_join = LED_LoRa_tx = LED_LoRa_rx = LED_Sens_tx = LED_Sens_rx = LED_OFF;
	     
     }
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

void LoRaJoin(void){
	printf("Send: mac join abp\n");
	
	LED_LoRa_join = LED_OFF;
	rtnSend = R_SCI_Send(g_my_sci_handle_ch1,"mac join abp",12);
	R_BSP_SoftwareDelay (1, BSP_DELAY_SECS);
	LORA_Recieve(rtnSend);
	
	LED_LoRa_join = LED_ON;
}

uint8_t sensorSend(void){
	uint8_t cmd[8];
	sprintf(cmd,"%c%c%c%c%c%c%c%c",SENS_ADDR,SENS_FUNC_READ,SENS_REG_READ_STARTH,SENS_REG_READ_STARTL,SENS_REG_COUNTH,SENS_REG_COUNTL,0x40,0x08);
	R_SCI_Send(g_my_sci_handle_ch2,cmd,HOST_SEND_LENGTH);
	return 0;
}

void sensorRead(uint8_t status){
	uint8_t index = 0;
	*pValue = &RecValue;
	while(status == SCI_SUCCESS){
		rtnRecieve = R_SCI_Receive(g_my_sci_handle_ch2,pValue,1);
		if(rtnRecieve == SCI_SUCCESS){
			// sensorData[index++] = RecValue[0];
			*(psensorData + index++) = RecValue[0];
			printf("0x%02X ",RecValue[0]);
		}
		else{
			index=0;
			//printf(".");
			// printf("Receive Status=0x%02X\n",rtnRecieve);
			break;
		}
		R_BSP_SoftwareDelay (100, BSP_DELAY_MILLISECS);
	}
}

void SoftwareReset(void){
	LED7 = LED_ON;
	R_BSP_SoftwareDelay(200, BSP_DELAY_MILLISECS);
	LED7 = LED_OFF;
	R_BSP_SoftwareDelay(200, BSP_DELAY_MILLISECS);
	SYSTEM.PRCR.WORD = 0xA502;
	SYSTEM.SWRR = 0xA501;
	SYSTEM.PRCR.WORD = 0xA500;
}


void main(void){
	Rx64MInitPorts();
	
	LED_System = LED_ON;
        LED_work = LED_ON;
	LED7 = LED_ON;
	R_BSP_SoftwareDelay (500, BSP_DELAY_MILLISECS);
	
	LED_System = LED_OFF;
	LED_work = LED_OFF;
	LED7 = LED_OFF;
	R_BSP_SoftwareDelay (500, BSP_DELAY_MILLISECS);
	
	UARTInit();
	LoRaJoin();
	
	LED(1,0,0,0,0);                          //LoRa Join
	R_BSP_SoftwareDelay (1, BSP_DELAY_SECS);
	LED(0,0,0,0,0);
	
	LED_System = LED_ON;
	
    while (1){
		ROUND_TIMER = 0;
		while(ROUND_TIMER++ < 6){
			NULL_COUNTER = 0;
			printf("Send cmd to sensor\n");
			LED(0,0,0,1,0);                           //sensor TX
			sensorSend();
			R_BSP_SoftwareDelay (1, BSP_DELAY_SECS);
			LED(0,0,0,0,0);
			printf("Read sensor\n");
	    	while (1){
				LED(0,0,0,0,1);                            //sensor RX
				sensorRead(0);
				if(*(psensorData + 2) == 0x08){
					printf("\nGot it!\n");
					break;
				}
				else{
					if(++NULL_COUNTER >= WATCH_DOG){
						printf("\nTimeout!\n");
						break;
					}
					R_BSP_SoftwareDelay(10, BSP_DELAY_MILLISECS);
					//printf("NULL_COUNTER = %d\n",NULL_COUNTER); //Time wait for sensor
				}
			}
			LED(0,0,0,0,0);
			
			printf("PH: %d(0x%04X)\n", mergePH, mergePH);
			printf("DO: %d(0x%04X)\n", mergeDO, mergeDO);
			printf("COND: %d(0x%04X)\n", mergeCO, mergeCO);
			printf("TEMP: %d(0x%04X)\n", mergeTP, mergeTP);
			
			printf("Pack command for LoRa\n");
			sprintf(sendCMD,"mac tx ucnf 2 %02d%02d%02d%02d%02d%01d%03d%02d%02d",
				POINT_LOC,
				finalData_phF, finalData_phS,
				finalData_doF, finalData_doS,
				finalData_coF, finalData_coS,
				finalData_tpF, finalData_tpS);
				
			printf("Reset flag\n");	
			*(psensorData + 2) = 0x00;
			
			/*printf("Flush buffer\n");
			for(LOCAL_LOOP=0; LOCAL_LOOP < RTN_LENGTH; LOCAL_LOOP++)
				sensorData[LOCAL_LOOP] = 0x00;
			*/
				LED_work = LED_ON;
			R_BSP_SoftwareDelay (6, BSP_DELAY_SECS);
				LED_work = LED_OFF;
		}
    
		printf("LoRa send ptLoc = %d\n",POINT_LOC);
		LED(0,1,0,0,0);                          //LoRa TX
		rtnSend = R_SCI_Send(g_my_sci_handle_ch1,sendCMD,40);
		R_BSP_SoftwareDelay (1, BSP_DELAY_SECS);
		LED(0,0,0,0,0);
		LED(0,0,1,0,0);                          //LoRa RX
		R_BSP_SoftwareDelay (200, BSP_DELAY_MILLISECS);
		LORA_Recieve(rtnSend);
	
	if(POINT_LOC >= TOTAL_POINT){
		POINT_LOC = 1;
	}
	else{
		POINT_LOC++;
	}	
		printf("GLOBALCOUNTER = %d\n", ++GLOBALCOUNTER);
		LED(0,0,0,0,0);
	}
}


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
	
	LED_System_PDR		= 0x1;
	LED_LoRa_join_PDR	= 0x1;
	LED_LoRa_tx_PDR		= 0x1;
	LED_LoRa_rx_PDR		= 0x1;
	LED_Sens_tx_PDR		= 0x1;
	LED_Sens_rx_PDR		= 0x1;
	LED_work_PDR		= 0x1;
	LED7_PDR			= 0x1;
	
        return;
}
