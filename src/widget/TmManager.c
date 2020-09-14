

/********************************************************************/
 /* (0) Includes.Begin */
/********************************************************************/
#include "TmManager.h"


/********************************************************************/
 /* (0) Includes.End */
/********************************************************************/



/********************************************************************/
/* (1) Definitions. Begin*/
/********************************************************************/

/*Typedef definitions*/



/*Macro definitions*/


/********************************************************************/
/* (1) Definitions. End*/
/********************************************************************/


/*********************************************************************/
 /* (2) Global variables .Begin */
/*********************************************************************/
uint32_t Down1ms[COUNTER_NUM] = {0};



/*********************************************************************/
 /* (2) Global variables .End */
/*********************************************************************/



/*********************************************************************/
 /* (3) Private variables and functions. Begin*/
/*********************************************************************/

/*********************************************************************/
 /* (3) Private variables and functions. End*/
/*********************************************************************/




/*********************************************************************/
/* (4) Private Functions Implementation. Begin*/
/*********************************************************************/
/*Every 1ms*/
void Cmtw0Callback(void *pdata)
{
	int8_t n;
	cmtw_callback_data_t *p_cb_data = (cmtw_callback_data_t *)pdata;

	if(p_cb_data->event == CMTW_EVENT_CM){
		for(n = 0; n < COUNTER_NUM-1; n++){
			if(Down1ms[n]) 		Down1ms[n]--;
		}
	}
	
#if 0
	cmtw_callback_data_t *p_cb_data = (cmtw_callback_data_t *)pdata;
	p_cb_data.channel = p_cb_data->channel;
	p_cb_data.event = p_cb_data->event;
	p_cb_data.count = p_cb_data->count;
#endif	

}

/*********************************************************************/
/* (4) Private Functions Implementation. End*/
/*********************************************************************/



/*********************************************************************/
/* (5) Public Function Implementation. Begin*/
/*********************************************************************/

void CmtwInit(void)
{
	cmtw_err_t rc;
	cmtw_channel_settings_t ch;
	/* Clear all fields of the cmtw_channel_settings_t structure */
	memset(&ch, 0, sizeof(ch));

	/* Setup for 1 ms compare match with callback */
	ch.time_unit = CMTW_TIME_MSEC;
	ch.clock_divisor = CMTW_CLK_DIV_8;
	ch.clear_source = CMTW_CLR_CMT;
	ch.cm_timer.time = 1;
	ch.cm_timer.actions = CMTW_ACTION_CALLBACK;
	rc = R_CMTW_Open(CMTW_CHANNEL_0, &ch, &Cmtw0Callback);

	if (CMTW_SUCCESS != rc)
	{
		printf("R_CMTW_Open Error in CmtwInit.\r\n");
		/* Handle the error */
	}

	/* And start it */
	rc = R_CMTW_Control(CMTW_CHANNEL_0, CMTW_CMD_START);
	if (CMTW_SUCCESS != rc)
	{
		printf("R_CMTW_Control Error in CmtwInit.\r\n");
		/* Handle the error */
	}
}


uint8_t StartCountDown(uint32_t msec)
{
	uint8_t RetCode = COUNTER_NUM_ERR;

	for(uint8_t num = 0; num < COUNTER_NUM-1; num++){
		if(Down1ms[num] == 0){
			Down1ms[num] = msec;
			RetCode = num;
			return RetCode;
		}	
	}
	
	return RetCode;
}

uint32_t CheckCountDown(uint8_t num)
{
	if(num < COUNTER_NUM-1)
		return Down1ms[num];
	else{
		printf("Err num in CheckCountDown().\r\n");
		return 0;
	}	
}

void DelayMs(uint32_t msec)
{
	R_BSP_SoftwareDelay(msec, BSP_DELAY_MILLISECS);
}

/*********************************************************************/
/* (5) Public Function Implementation. End*/
/*********************************************************************/



