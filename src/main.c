
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

/*For ADC*/
#include "platform.h"
#include "r_s12ad_rx_config.h"
#include "r_s12ad_rx_if.h"

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

/*For ADC.Begin*/
uint16_t  g_data0;  // Global variable for saving result of ADC CH0 conversions
uint16_t  g_data1;  // Global variable for saving result of ADC CH1 conversions
uint16_t  g_data2;  // Global variable for saving result of ADC CH2 conversions
uint16_t  g_data3;  // Global variable for saving result of ADC CH3 conversions
uint16_t  g_data;  // Global variable for saving result of ADC CH0 conversions
static void ADCInit(void);
static void ADCStart(void);
/*For ADC.End*/


/*For UART.Begin*/
void my_sci_callback_ch1(void *pArgs);
void my_sci_callback_ch2(void *pArgs);
void my_sci_callback_ch7(void *pArgs);
static void Rx64MInitPorts(void);
static void UARTInit(void);
static void SendADCValue(const uint16_t adc_value,int mode);
static void SendSCIVersion(void);

void U16toStr(uint16_t value, uint8_t *buff);
void HMI_n_value(uint8_t n_id,uint16_t n_value);
void HMI_z_value(uint8_t z_id,uint16_t z_value);
void delay1s(uint8_t tmp);
void HMI_page(uint8_t page_id);
/*for hmi test*/
uint8_t HexToChar_buff[4] = {0x00,0x00,0x00,0x00};
uint8_t HMI_page_order[10] = {0x70,0x61,0x67,0x65,0x20,0x30,0x30,0xff,0xff,0xff};
static const uint8_t HexChar[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/* Handle storage. Needs to persist as long as SCI calls are going to be made.*/
static sci_hdl_t   g_my_sci_handle;
static sci_hdl_t   g_my_sci_handle_ch1;		//For LoRa
static sci_hdl_t   g_my_sci_handle_ch2;		//For Sensor
/*For UART. End*/

/*Custome global variable declaration start*/
int refresh_delay=1000;
float global_f1_temp=0;			//p40
float global_f1_humi=0;			//p41
float global_f1_phph=0;			//p42
float global_env_temp=0;		//p
float global_env_humi=0;		//p
float global_env_illu=0;		//p43

float global_f1_temp_adj=-15;			//adjust field 1 temperature
float global_f1_humi_adj=+40;			//adjust field 1 humidity
float global_f1_phph_adj=-1.1;			//adjust field 1 ph
float global_env_temp_adj=0;			//adjust enviroment temperature
float global_env_humi_adj=0;			//adjust enviroment humidity
float global_env_illu_adj=0;			//adjust enviroment illumination

uint8_t bt_str_send[24];
uint8_t f1t[4]={'0','0','.','0'};			//10 Field 1 temperature value			[xx.x]
uint8_t f1h[3]={'0','0','0'};				//11 Field 1 humidity value				[xxx]
uint8_t f1p[4]={'0','0','.','0'};			//12 Field 1 ph value					[xx.x]
uint8_t evt[4]={'0','0','.','0'};			//100 Enviroment temperature value		[xx.x]
uint8_t evh[3]={'0','0','0'};				//101 Enviroment humidity value			[xxx]
uint8_t evi[6]={'0','0','0','0','.','0'};	//103 Enviroment illumination value		[xxxx.x]

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
	delay1s(1000);
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
	ADCInit();		
	ADCStart();
	LoRaJoin();
	delay1s(1000);
	
	LED1=LED_OFF;
	sensorSend();
	delay1s(1000);
	
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
	delay1s(1000);
	LORA_Recieve(rtnSend);
	
	printf("\n\nEnded\n");

	LED1=LED_OFF;
	R_BSP_SoftwareDelay (100, BSP_DELAY_MILLISECS);
}

/*****************************************************************************/
/*Functions for . Begin*/
/*****************************************************************************/

// uint16_t HLbyte(uint8_t HIGH, uint8_t LOW){
	// uint16_t
	// return 0;
// }

void U16toStr(uint16_t value, uint8_t *buff){
 uint8_t i;
 uint8_t j;
 int8_t temp;

 if (value == 0)
 {
  buff[0] = '0';
  buff[1] = 0;
  return;
 }

 i = 0;
 while (value)
 {
  buff[i] = HexChar[value % 10];
  value /= 10;
  i++;
 }

 buff[i] = 0;

 for (j = 0; j < (i / 2); j++)
 {
  temp = buff[j];
  buff[j] = buff[i - j -1];
  buff[i - j -1] = temp;
 }
}

void delay1s(unsigned int tmp){
    unsigned int i,j;
    i=tmp;
    while(i--){
        j=80404;
        while(j--);
    }
}



/*****************************************************************************
* Function Name: ADCStart
* Description  :
* Arguments   :
* Return Value : none
******************************************************************************/
static void ADCStart(void){
        adc_err_t       adc_err;

        /* Initialize trigger source (MTU0) */
        init_mtu0();

        /* Enable triggers in ADC */   /*Enables to start A/D conversion with TRIG, */
        adc_err = R_ADC_Control(0, ADC_CMD_ENABLE_TRIG, FIT_NO_PTR);
        while (ADC_SUCCESS != adc_err)
        {
        /* Error - loop here for debug */
        }

}


/*****************************************************************************
* Function Name: ADCInit
* Description  :
* Arguments   :
* Return Value : none
******************************************************************************/
static void ADCInit(void){
        adc_err_t       adc_err;
        adc_err_t       adc_err0;
        adc_err_t       adc_err1;
        adc_err_t       adc_err2;
        adc_err_t       adc_err3;
        adc_cfg_t       config;     // Open() configuration
        adc_ch_cfg_t    ch_cfg;     // Control() channel configuration

        /* Clear all members of the adc_cfg_t structure */
        memset(&config, 0, sizeof(config));
        config.resolution =  ADC_RESOLUTION_12_BIT;     // 12 bit resolution
        config.alignment = ADC_ALIGN_RIGHT;             // conversions are right-aligned
        config.add_cnt = ADC_ADD_OFF;                   // no addition on conversions
        config.clearing = ADC_CLEAR_AFTER_READ_OFF;     // data remains in register after reading
        config.trigger = ADC_TRIG_SYNC_TRG0AN;          // trigger from mtu
        config.trigger_groupb = ADC_TRIG_NONE;          // group mode not used
        config.priority = 3;                            // interrupt priority 3 (1=low, 15=high)
        config.priority_groupb = 0;                     // group mode not used

        // adc_err = R_ADC_Open(0, ADC_MODE_SS_ONE_CH, &config, MyCallback);
        // adc_err = R_ADC_Open(0, ADC_MODE_SS_MULTI_CH, &config, MyCallback);
        adc_err = R_ADC_Open(0, ADC_MODE_SS_MULTI_CH, &config, MyCallback);
        while (ADC_SUCCESS != adc_err)
        {
            /* Error - loop here for debug */
        }

        /* Enable channel */
				                    
		// ch_cfg.chan_mask = ADC_MASK_CH4;                     
		ch_cfg.chan_mask = ADC_MASK_CH0|ADC_MASK_CH1|ADC_MASK_CH2|ADC_MASK_CH3; 
		// ch_cfg.chan_mask = ADC_MASK_CH0; 
		// select channel 0 1 2 3 (POT) (PDF r01an1666ej0301-rx p48)
        ch_cfg.priority_groupa = ADC_GRPA_PRIORITY_OFF;      // group mode not used
        ch_cfg.chan_mask_groupb = ADC_MASK_GROUPB_OFF;       // group mode not used
        ch_cfg.add_mask = ADC_MASK_ADD_OFF;                  // no channels using addition
        ch_cfg.diag_method = ADC_DIAG_OFF;                   // self-diagnosis off
        ch_cfg.anex_enable = false;                          // no external amplifier
        ch_cfg.sample_hold_mask = ADC_MASK_SAMPLE_HOLD_OFF;  // Bypass chnl-dedicated S&H circuits
        ch_cfg.sample_hold_states = ADC_SST_SH_CNT_DEFAULT;  // default sample & hold states

        adc_err = R_ADC_Control(0, ADC_CMD_ENABLE_CHANS, &ch_cfg);
        while (ADC_SUCCESS != adc_err){
        /* Error - loop here for debug */
			printf("Hi");
        }
		
}


/*****************************************************************************
* Function Name: MyCallback
* Description  : This function is called at interrupt level when an ADC
*                conversion completes.
* Arguments    : pArgs -
*                    pointer to adc_cb_args_t structure
* Return Value : none
******************************************************************************/
void MyCallback(void *pArgs){
    // adc_err_t adc_err;
    adc_err_t adc_scan_err;
    adc_err_t adc_err0;
    adc_err_t adc_err1;
    adc_err_t adc_err2;
    adc_err_t adc_err3;
    adc_cb_args_t *args = (adc_cb_args_t *)pArgs;

    if ((0 == args->unit) && (ADC_EVT_SCAN_COMPLETE == args->event))
    {
        /* Read conversion value and store in global variable */
		adc_err0 = R_ADC_Read(0, ADC_REG_CH0, &g_data0);   /*Use CH0*/
		adc_err1 = R_ADC_Read(0, ADC_REG_CH1, &g_data1);   /*Use CH1*/
		adc_err2 = R_ADC_Read(0, ADC_REG_CH2, &g_data2);   /*Use CH2*/
		adc_err3 = R_ADC_Read(0, ADC_REG_CH3, &g_data3);   /*Use CH3*/
		// adc_err = R_ADC_ReadAll(&g_data);   /*Read All*/
        while (ADC_SUCCESS != adc_err0)
        {
            /* Error - loop here for debug */
        }
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
        LED0 = ~LED0;         // Toggle LED to demonstrate callback execution.
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
        LED0 = ~LED0;         // Toggle LED to demonstrate callback execution.
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


    /*For ADC*/
		
		/*Setting for P40 as AN000*/
        MPC.P40PFS.BYTE = 0x80;     // Pin Func Select P40 AN000; POT on
        PORT4.PDR.BIT.B0 = 0;       // set AN pin direction to input (default)
        PORT4.PMR.BIT.B0 = 1;       // set AN pin mode to peripheral
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); // Re-lock the MPC register.
		
		/*Setting for P41 as AN001*/
        MPC.P40PFS.BYTE = 0x80;     // Pin Func Select P41 AN001; POT on
        PORT4.PDR.BIT.B1 = 0;       // set AN pin direction to input (default)
        PORT4.PMR.BIT.B1 = 1;       // set AN pin mode to peripheral
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); // Re-lock the MPC register.
		
		/*Setting for P42 as AN002*/
        MPC.P40PFS.BYTE = 0x80;     // Pin Func Select P42 AN002; POT on
        PORT4.PDR.BIT.B2 = 0;       // set AN pin direction to input (default)
        PORT4.PMR.BIT.B2 = 1;       // set AN pin mode to peripheral
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); // Re-lock the MPC register.
		
		/*Setting for P43 as AN003*/
        MPC.P40PFS.BYTE = 0x80;     // Pin Func Select P43 AN003; POT on
        PORT4.PDR.BIT.B3 = 0;       // set AN pin direction to input (default)
        PORT4.PMR.BIT.B3 = 1;       // set AN pin mode to peripheral
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); // Re-lock the MPC register.

        /*Setting for P44 as AN004*/
        MPC.P44PFS.BYTE = 0x80;     // Pin Func Select P44 AN004; POT on
        PORT4.PDR.BIT.B4 = 0;       // set AN pin direction to input (default)
        PORT4.PMR.BIT.B4 = 1;       // set AN pin mode to peripheral
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); // Re-lock the MPC register.
		
        return;
}






