
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
void init_mtu0(void);   /*For ADC*/
void MyCallback(void *pArgs);   /*For ADC*/

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
void my_sci_callback(void *pArgs);
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
// uint8_t HMI_n_order[13] = {0x6E,0x30,0x2E,0x76,0x61,0x6C,0x3D,0x30,0x30,0x30,0xff,0xff,0xff};
// uint8_t HMI_z_order[13] = {0x7A,0x30,0x2E,0x76,0x61,0x6C,0x3D,0x30,0x30,0x30,0xff,0xff,0xff};
static const uint8_t HexChar[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/* Handle storage. Needs to persist as long as SCI calls are going to be made.*/
static sci_hdl_t   g_my_sci_handle;
/*For UART. End*/

/*Custome function declaration start*/
void chtx(float val_data, int mode);
void zxclac(float val_data, int mode);
void chzx(float val_data, int mode);
int dp_count(float val);
// void adc_channel_switch(void);
/*Custome function declaration end*/

/*Custome global variable declaration start*/
int refresh_delay=2000;
float global_temp;		//p40
float global_humi;		//p41
float global_phph;		//p42
float global_illu;		//p43

float global_temp_adj=0;			//adjust temperature
float global_humi_adj=0;			//adjust temperature
float global_phph_adj=0;			//adjust temperature
float global_illu_adj=0;			//adjust temperature
/*Custome global variable declaration end*/

/******************************************************************************
* Function Name : main
* Declaration   : void main(void)
* Description   : This function is main processing
* Arguments     : none
* Return value  : none
******************************************************************************/

void main(void){
    Rx64MInitPorts();
    UARTInit();
	ADCInit();		
	ADCStart();
#if 0
    sci_err_t   my_sci_err;
        /* Wait to get a character from the terminal so we know that it is ready. */
        do
        {
        my_sci_err = R_SCI_Receive(g_my_sci_handle, &my_char, 1);
        } while (SCI_ERR_INSUFFICIENT_DATA == my_sci_err);
#endif
	
    while (1){
		global_temp=0.0171*g_data0+global_temp_adj;
		global_humi=0.0244*g_data1+global_humi_adj;
		global_phph=0.0034*g_data2+global_phph_adj;
		global_illu=0.3663*g_data3+global_illu_adj;
		
			chtx(global_temp,0);
		delay1s(refresh_delay);
			zxclac(global_temp,0);
		delay1s(refresh_delay);
			chtx(global_humi,1);
		delay1s(refresh_delay);
			zxclac(global_humi,1);
		delay1s(refresh_delay);
			chtx(global_phph,2);
		delay1s(refresh_delay);
			zxclac(global_phph,2);
		delay1s(refresh_delay);
			chtx(global_illu,3);
		delay1s(refresh_delay);
			zxclac(global_illu,3);
		delay1s(refresh_delay);
		printf("\n\n");
    }

}

int dp_count(float val){
	int order = 1;
	while(val>=10){
		val /= 10;
		order++;
	}
	return order;
}

/**	change t?.txt on screen			
	data_pre_count: xxx.x =3; xx.x=2 	
	array length = data_pre_count+14	
	mode=t?.txt						
	t0= temperature		(0)c			
	t1= humidity		(1)%			
	t2= illumination	(2)w/m2			
	t3= pH				(3) 			**/

void chtx(float val_data, int mode){
	int data_pre_count = dp_count(val_data);
	uint8_t cmd_send[20];
	if(mode==2){
		data_pre_count -= 2;
		sprintf(cmd_send,"t%d.txt=\"%.0f\"",mode,val_data);
	}
	else{
		sprintf(cmd_send,"t%d.txt=\"%.1f\"",mode,val_data);
	}
	cmd_send[14+data_pre_count-3]=0xff;
	cmd_send[14+data_pre_count-2]=0xff;
	cmd_send[14+data_pre_count-1]=0xff;
	R_SCI_Send(g_my_sci_handle,cmd_send,14+data_pre_count);
}

void zxclac(float val_data, int mode){
	switch(mode){
		case 0:
			if(3*val_data>180){
				val_data=180;
				chzx(val_data,mode);
			}
			else{
				chzx(3*val_data,mode);
			}
			break;
		case 1:
			chzx(1.8*val_data,mode);
			break;
		case 2:
			if(val_data<4){
				val_data=0;
				chzx(val_data,mode);
			}
			else if(val_data>10){
				val_data=180;
				chzx(val_data,mode);
			}
			else{
				chzx(30*val_data-120,mode);
			}
			break;
		case 3:
			chzx(0.12*val_data,mode);
			break;
		default:
			chzx(270,0);
			chzx(270,1);
			chzx(270,2);
			chzx(270,3);
			chtx(999,0);
			chtx(999,1);
			chtx(999,2);
			chtx(999,3);
	}
}

void chzx(float angle, int mode){
	uint8_t cmd_send[20];
	sprintf(cmd_send,"z%d.val=%.0f",mode,angle);
	if(angle<10){
		cmd_send[10]=0xff;
		cmd_send[9]=0xff;
		cmd_send[8]=0xff;
		R_SCI_Send(g_my_sci_handle,cmd_send,11);
	}
	else if(10<=angle && angle<100){
		cmd_send[11]=0xff;
		cmd_send[10]=0xff;
		cmd_send[9]=0xff;
		R_SCI_Send(g_my_sci_handle,cmd_send,12);
	} 
	else if(100<=angle){
		cmd_send[12]=0xff;
		cmd_send[11]=0xff;
		cmd_send[10]=0xff;
		R_SCI_Send(g_my_sci_handle,cmd_send,13);
	}
}
/**
For printing array
	printf("\n");
	printf("\n");
	printf("array length:%d\n",sizeof(cmd_send));
	for(int i=0;i<sizeof(cmd_send);i++){
		printf("%x",cmd_send[i]);
		printf("|");
	}
	printf("\n");
	for(int j=0;j<sizeof(cmd_send);j++){
		printf("%c",cmd_send[j]);
	}
	printf("\n");
	printf("\n");
**/
/*****************************************************************************/
/*Functions for . Begin*/
/*****************************************************************************/

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

/*
void HMI_page(uint8_t page_id){
	
	if (page_id<10)
	{
	U16toStr(page_id,HexToChar_buff);
	HMI_page_order[5]=0x30;
	HMI_page_order[6]=HexToChar_buff[0];
	R_SCI_Send(g_my_sci_handle,HMI_page_order,10);
	}
	
	if (page_id>10)
	{
	U16toStr(page_id,HexToChar_buff);
	HMI_page_order[5]=HexToChar_buff[0];
	HMI_page_order[6]=HexToChar_buff[1];
	R_SCI_Send(g_my_sci_handle,HMI_page_order,10);
	}
	
}

void HMI_n_value(uint8_t n_id,uint16_t n_value){
	U16toStr(n_id,HexToChar_buff);
	HMI_n_order[1]=HexToChar_buff[0];
	
	if (n_value<10)
	{
	U16toStr(n_value,HexToChar_buff);
	HMI_n_order[7]=0x30;
	HMI_n_order[8]=0x30;
	HMI_n_order[9]=HexToChar_buff[0];
	R_SCI_Send(g_my_sci_handle,HMI_n_order,13);
	}
	
	if (100>n_value>10)
	{
	U16toStr(n_value,HexToChar_buff);
	HMI_n_order[7]=0x30;
	HMI_n_order[8]=HexToChar_buff[0];
	HMI_n_order[9]=HexToChar_buff[1];
	R_SCI_Send(g_my_sci_handle,HMI_n_order,13);
	}
	
	if (n_value>100)
	{
	U16toStr(n_value,HexToChar_buff);
	HMI_n_order[7]=HexToChar_buff[0];
	HMI_n_order[8]=HexToChar_buff[1];
	HMI_n_order[9]=HexToChar_buff[2];
	R_SCI_Send(g_my_sci_handle,HMI_n_order,13);
	}
	
}

void HMI_z_value(uint8_t z_id,uint16_t z_value){
	U16toStr(z_id,HexToChar_buff);
	HMI_z_order[1]=HexToChar_buff[0];
	
	if (z_value<10)
	{
	U16toStr(z_value,HexToChar_buff);
	HMI_z_order[7]=0x30;
	HMI_z_order[8]=0x30;
	HMI_z_order[9]=HexToChar_buff[0];
	R_SCI_Send(g_my_sci_handle,HMI_z_order,13);
	}
	
	if (100>z_value>10)
	{
	U16toStr(z_value,HexToChar_buff);
	HMI_z_order[7]=0x30;
	HMI_z_order[8]=HexToChar_buff[0];
	HMI_z_order[9]=HexToChar_buff[1];
	R_SCI_Send(g_my_sci_handle,HMI_z_order,13);
	}
	
	if (z_value>100)
	{
	U16toStr(z_value,HexToChar_buff);
	HMI_z_order[7]=HexToChar_buff[0];
	HMI_z_order[8]=HexToChar_buff[1];
	HMI_z_order[9]=HexToChar_buff[2];
	R_SCI_Send(g_my_sci_handle,HMI_z_order,13);
	}
	
}
*/

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
        adc_err = R_ADC_Open(0, ADC_MODE_SS_MULTI_CH, &config, MyCallback);
        while (ADC_SUCCESS != adc_err)
        {
            /* Error - loop here for debug */
        }

        /* Enable channel */
				                    
		// ch_cfg.chan_mask = ADC_MASK_CH4;                     
		ch_cfg.chan_mask = ADC_MASK_CH0|ADC_MASK_CH1|ADC_MASK_CH2|ADC_MASK_CH3; 
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
    adc_err_t adc_err;
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

/*****************************************************************************
* Function Name: mtu0_tgia0_isr
* Description  : Interrupt service routine for MTU0 TGRA compare match.
*                This simply demonstrates how to register an ISR for
*                interrupt MTU0 TGIA0. Every 10 times the interrupt occurs
*                LED2 is toggled.
* Arguments    : none
* Return Value : none
******************************************************************************/
/*
#pragma interrupt mtu0_tgia0_isr(vect=VECT(MTU0,TGIA0))
static void mtu0_tgia0_isr(void){
    static uint16_t cnt = 0;

    if ((cnt++ % 10) == 0)
    {
        LED2 ^= 1;   // Toggle LED2 every 10 timer matches
    }

    if ((cnt% 100) == 0)    {
        SendADCValue(g_data0,0);
        SendADCValue(g_data1,1);
        SendADCValue(g_data2,2);
        SendADCValue(g_data3,3);
    }
}*/
/*****************************************************************************/
/*Functions for ADC. End*/
/*****************************************************************************/



/*****************************************************************************/
/*Functions for UART.Begin*/
/*****************************************************************************/

/*****************************************************************************
* Function Name: ADCInit
* Description  :
* Arguments   :
* Return Value : none
******************************************************************************/
/*
static void SendADCValue(const uint16_t adc_value,int mode){ 
	// char adc_str[20];
	switch(mode){
		case 0:
			global_adc_val0=adc_value;
			break;
		case 1:
			global_adc_val1=adc_value;
			break;
		case 2:
			global_adc_val2=adc_value;
			break;
		case 3:
			global_adc_val3=adc_value;
			break;
		default:
			global_adc_val0=adc_value;	
	}
   
    // sprintf(adc_str, " ADC: %03XH       \r\n", adc_value);
	
    //R_SCI_Send(g_my_sci_handle, (uint8_t*) adc_str, sizeof(adc_str));

}*/

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
        sci_err_t   my_sci_err;

    /**********************************************************************************/
        /* Set up the configuration data structure for asynchronous (UART) operation. */
        my_sci_config.async.baud_rate    = 9600;
        my_sci_config.async.clk_src      = SCI_CLK_INT;
        my_sci_config.async.data_size    = SCI_DATA_8BIT;
        my_sci_config.async.parity_en    = SCI_PARITY_OFF;
        my_sci_config.async.parity_type  = SCI_EVEN_PARITY;
        my_sci_config.async.stop_bits    = SCI_STOPBITS_1;
        my_sci_config.async.int_priority = 3;    // 1=lowest, 15=highest

        /* OPEN ASYNC CHANNEL
        *  Provide address of the config structure,
        *  the callback function to be assigned,
        *  and the location for the handle to be stored.*/     /*Use channel 7*/
        my_sci_err = R_SCI_Open(SCI_CH7, SCI_MODE_ASYNC, &my_sci_config, my_sci_callback, &g_my_sci_handle);

        /* If there were an error this would demonstrate error detection of API calls. */
        if (SCI_SUCCESS != my_sci_err)
        {
            nop(); // Your error handling code would go here.
        }


    /* If there were an error this would demonstrate error detection of API calls. */
        if (SCI_SUCCESS != my_sci_err)
        {
        nop(); // Your error handling code would go here.
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
void my_sci_callback(void *pArgs){
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

    /*For SCI-UART*/
        /* Set RXD7 pin */  /*P92*/
        MPC.P92PFS.BYTE = 0x0A;
        PORT9.PMR.BYTE |= 0x04;    // Set P92 mode to peripheral operation

	
	/*Send data to screen at P90*/
        /* Set TXD7 pin */  /*P90*/
        PORT9.PODR.BYTE |= 0x01;
        MPC.P90PFS.BYTE = 0x0A;
        PORT9.PMR.BYTE |= 0x01;  // Set P90 mode to peripheral operation
        PORT9.PDR.BYTE |= 0x01;

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




