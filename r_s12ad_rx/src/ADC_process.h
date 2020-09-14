#include "platform.h"
#include "r_s12ad_rx_config.h"
#include "r_s12ad_rx_if.h"
#include "global_var.h"

#define DebugModeEnabled (1)

extern void ADCInit(void);
extern void ADCStart(void);
// void adc_clacTemp(void);
// void adc_out(void);
void adc_clacTemp(void);
void init_mtu0(void);   /*For ADC*/
void ADC_READ(void *pArgs);   /*For ADC*/

uint16_t  g_data0;  // Global variable for saving result of ADC CH0 conversions
uint16_t  g_data1;  // Global variable for saving result of ADC CH1 conversions
uint16_t  g_data2;  // Global variable for saving result of ADC CH2 conversions
uint16_t  g_data3;  // Global variable for saving result of ADC CH3 conversions
uint16_t  g_data4;  // Global variable for saving result of ADC CH4 conversions
uint16_t  g_data5;  // Global variable for saving result of ADC CH5 conversions

float  Tch0_adj=0;
float  Tch1_adj=0;
float  Tch2_adj=0;
float  Tch3_adj=0;
float  Tch4_adj=0;
float  Tch5_adj=0;
/*
uint16_t sum0=0;
uint16_t sum1=0;
uint16_t sum2=0;
uint16_t sum3=0;
uint16_t sum4=0;
uint16_t sum5=0;*/
