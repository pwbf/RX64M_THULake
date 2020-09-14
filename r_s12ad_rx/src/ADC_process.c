#include "ADC_process.h"

void adc_out(void){
	//adc_avg();
	#if DebugModeEnabled
		printf("===================\n");
		printf("Ch0: %d | Temp:%f\n",g_data0,g_data0*0.061-50);
		printf("Ch1: %d | Temp:%f\n",g_data1,g_data1*0.061-50);
		printf("Ch2: %d | Temp:%f\n",g_data2,g_data2*0.061-50);
		printf("Ch3: %d | Temp:%f\n",g_data3,g_data3*0.061-50);
		printf("Ch4: %d | Temp:%f\n",g_data4,g_data4*0.061-50);
		printf("Ch5: %d | Temp:%f\n",g_data5,g_data5*0.061-50);
		printf("===================\n");
		printf("\n");
	#endif
}

void adc_clacTemp(void){
	sprintf(adc_send,"%05.1f,%05.1f,%05.1f,%05.1f,%05.1f,%05.1f",
	Tch0_adj+g_data0*0.061-50,
	Tch1_adj+g_data1*0.061-50,
	Tch2_adj+g_data2*0.061-50,
	Tch3_adj+g_data3*0.061-50,
	Tch4_adj+g_data4*0.061-50,
	Tch5_adj+g_data5*0.061-50
	);
	//adc_out();
}
/*
void adc_avg(void){
	int data_count=0;
	if(g_data0||g_data1||g_data2||g_data3||g_data4||g_data5){
		sum0+=g_data0;
		sum1+=g_data1;
		sum2+=g_data2;
		sum3+=g_data3;
		sum4+=g_data4;
		sum5+=g_data5;
		data_count++;
	}
	if(data_count==200){
		g_data0_avg=(sum0/200)+g_data0_adj;
		g_data1_avg=(sum1/200)+g_data1_adj;
		g_data2_avg=(sum2/200)+g_data2_adj;
		g_data3_avg=(sum3/200)+g_data3_adj;
		g_data4_avg=(sum4/200)+g_data4_adj;
		g_data5_avg=(sum5/200)+g_data5_adj;
		sum0=0;
		sum1=0;
		sum2=0;
		sum3=0;
		sum4=0;
		sum5=0;
		data_count=0;
	}
}*/

/*****************************************************************************
* Function Name: ADCStart
* Description  :
* Arguments   :
* Return Value : none
******************************************************************************/
void ADCStart(void){
        adc_err_t       adc_err;

        /* Initialize trigger source (MTU0) */
        init_mtu0();

        /* Enable triggers in ADC */   /*Enables to start A/D conversion with TRIG, */
        adc_err = R_ADC_Control(0, ADC_CMD_ENABLE_TRIG, FIT_NO_PTR);
        while (ADC_SUCCESS != adc_err){
        /* Error - loop here for debug */
        }

}
/*****************************************************************************
* Function Name: ADCInit
* Description  :
* Arguments   :
* Return Value : none
******************************************************************************/
void ADCInit(void){
        adc_err_t       adc_err;
        adc_err_t       adc_err0;
        adc_err_t       adc_err1;
        adc_err_t       adc_err2;
        adc_err_t       adc_err3;
        adc_err_t       adc_err4;
        adc_err_t       adc_err5;
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

        adc_err = R_ADC_Open(0, ADC_MODE_SS_MULTI_CH, &config, ADC_READ);
        while (ADC_SUCCESS != adc_err){
            /* Error - loop here for debug */
        }

        /* Enable channel */
				                    
		// ch_cfg.chan_mask = ADC_MASK_CH4;                     
		ch_cfg.chan_mask = ADC_MASK_CH0|ADC_MASK_CH1|ADC_MASK_CH2|ADC_MASK_CH3|ADC_MASK_CH4|ADC_MASK_CH5; 
		// ch_cfg.chan_mask = ADC_MASK_CH0; 
		// select channel 0 1 2 3 4 5(POT) (PDF r01an1666ej0301-rx p48)
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
			printf("adc_error");
        }
		
}

/*****************************************************************************
* Function Name: ADC_READ
* Description  : This function is called at interrupt level when an ADC
*                conversion completes.
* Arguments    : pArgs -
*                    pointer to adc_cb_args_t structure
* Return Value : none
******************************************************************************/
void ADC_READ(void *pArgs){
    // adc_err_t adc_err;
    adc_err_t adc_scan_err;
    adc_err_t adc_err0;
    adc_err_t adc_err1;
    adc_err_t adc_err2;
    adc_err_t adc_err3;
    adc_err_t adc_err4;
    adc_err_t adc_err5;
    adc_cb_args_t *args = (adc_cb_args_t *)pArgs;

    if ((0 == args->unit) && (ADC_EVT_SCAN_COMPLETE == args->event)){
        /* Read conversion value and store in global variable */
		adc_err0 = R_ADC_Read(0, ADC_REG_CH0, &g_data0);   /*Use CH0*/
		adc_err1 = R_ADC_Read(0, ADC_REG_CH1, &g_data1);   /*Use CH1*/
		adc_err2 = R_ADC_Read(0, ADC_REG_CH2, &g_data2);   /*Use CH2*/
		adc_err3 = R_ADC_Read(0, ADC_REG_CH3, &g_data3);   /*Use CH3*/
		adc_err4 = R_ADC_Read(0, ADC_REG_CH4, &g_data4);   /*Use CH4*/
		adc_err5 = R_ADC_Read(0, ADC_REG_CH5, &g_data5);   /*Use CH5*/

        while (ADC_SUCCESS != adc_err0){
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
    //MTU0.TGRA = 60000;          // Set the compare match count value

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

