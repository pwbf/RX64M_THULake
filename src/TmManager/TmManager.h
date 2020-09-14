
#ifndef CMTW_MANAGER_H
#define CMTW_MANAGER_H

/********************************************************************/
/* (0) Include.Begin*/
/********************************************************************/
#include "r_cmtw_rx_if.h"

/********************************************************************/
/* (0) Include.End*/
/********************************************************************/

/********************************************************************/
/* (1) Definitions.Begin*/
/********************************************************************/
#define COUNTER_NUM 4

#define COUNTER_NUM_ERR	0xFF

/********************************************************************/
/* (1) Definitions.End*/
/********************************************************************/




/********************************************************************/
/* (2) VARIABLES. Begin*/
/********************************************************************/
extern uint32_t Down1ms[];


/********************************************************************/
/* (2) VARIABLES. End*/
/********************************************************************/


/********************************************************************/
/* (3) Constants.Begin*/
/********************************************************************/

/********************************************************************/
/* (3) Constants.End*/
/********************************************************************/


/*********************************************************************/
/* (4) Exported Functions Prototype. Begin*/
/*********************************************************************/
extern void CmtwInit(void);
extern uint8_t StartCountDown(uint32_t msec);
extern uint32_t CheckCountDown(uint8_t num);
extern void DelayMs(uint32_t msec);
/*********************************************************************/
/* (4) Exported Functions Prototype. End*/
/*********************************************************************/





#endif 
