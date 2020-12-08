#include <stdio.h>
#include <string.h>
#include <stdbool.h>


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
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
void main(void);
void init_mtu0(void);   			/*For ADC*/
void MyCallback(void *pArgs);   	/*For ADC*/

// uint8_t HLbyte(uint8_t HIGH, uint8_t LOW);

/******************************************************************************
Private global variables and functions
******************************************************************************/

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
#define LED_System				(PORTE.PODR.BIT.B0)
#define LED_LoRa_join				(PORTE.PODR.BIT.B1)
#define LED_LoRa_tx				(PORTE.PODR.BIT.B2)
#define LED_LoRa_rx				(PORTE.PODR.BIT.B3)
#define LED_Sens_tx				(PORTE.PODR.BIT.B4)
#define LED_Sens_rx				(PORTE.PODR.BIT.B5)
#define LED_work				(PORTE.PODR.BIT.B6)
#define LED7					(PORTE.PODR.BIT.B7)

#define LED_System_PDR			(PORTE.PDR.BIT.B0)
#define LED_LoRa_join_PDR       	(PORTE.PDR.BIT.B1)
#define LED_LoRa_tx_PDR 		(PORTE.PDR.BIT.B2)
#define LED_LoRa_rx_PDR			(PORTE.PDR.BIT.B3)
#define LED_Sens_tx_PDR			(PORTE.PDR.BIT.B4)
#define LED_Sens_rx_PDR			(PORTE.PDR.BIT.B5)
#define LED_work_PDR			(PORTE.PDR.BIT.B6)
#define LED7_PDR			(PORTE.PDR.BIT.B7)

#define LED_ON          (0)
#define LED_OFF         (1)

#define mergePH			(*(psensorData + 3)<<8 | *(psensorData + 4))		//High byte + Low bytes > pH
#define mergeDO			(*(psensorData + 5)<<8 | *(psensorData + 6))		//High byte + Low bytes > Do
#define mergeCO			(*(psensorData + 7)<<8 | *(psensorData + 8))		//High byte + Low bytes > Co
#define mergeTP			(*(psensorData + 9)<<8 | *(psensorData + 10))		//High byte + Low bytes > Tp

#define finalData_phF	(*(pclacData+0) = mergePH / 100	)
#define finalData_phS	(*(pclacData+1) = mergePH % 100	)
#define finalData_doF	(*(pclacData+2) = mergeDO / 100	)
#define finalData_doS	(*(pclacData+3) = mergeDO % 100	)
#define finalData_coF	(*(pclacData+4) = mergeCO / 1000	)
#define finalData_coS	(*(pclacData+5) = mergeCO % 1000	)
#define finalData_tpF	(*(pclacData+6) = mergeTP / 100	)
#define finalData_tpS	(*(pclacData+7) = mergeTP % 100	)

#define DEBUG_MODE	(0)
#define MODE_SEA_WATER	(0) // 0 for normal water, 1 for sea water