#include <includes.h>
#include	<stdio.h>
#include	<stdarg.h>
#include	<stddef.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
 
/*
*********************************************************************************************************
*                         	                   VARIABLES
*********************************************************************************************************
*/
 
 
 
 
static  OS_TCB	App_TaskStartTCB;
static  OS_TCB	PollingTCB;
static  OS_TCB	CountingTCB;
static  OS_TCB	LED_TCB;
static  CPU_STK   App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];
static  CPU_STK   PollingStk[APP_CFG_TASK_START_STK_SIZE];
static  CPU_STK   LEDStk[APP_CFG_TASK_START_STK_SIZE];
static  CPU_STK   CountingStk[APP_CFG_TASK_START_STK_SIZE];
CPU_INT08U j;
static  CPU_INT08U  toggle_value;
 
CPU_INT08U costs[3] = {4, 3, 1};
 
 
/*
*********************************************************************************************************
*                                     	FUNCTION PROTOTYPES
*********************************************************************************************************
*/
 
static  void  App_TaskCreate  (void);
static  void  App_ObjCreate   (void);
static  void  Polling  	(void);
static  void  LED     	    (void);
static  void  Counting    	(void);
static  void  App_TaskStart   (void  *p_arg);
 
 
/*
*********************************************************************************************************
*                                            	main()
*
* Description : This is the standard entry point for C code.
*
* Arguments   : none
*********************************************************************************************************
*/
OS_ERR  	os_err;
CPU_TS  	ts;
OS_MUTEX	Multiplier_Mutex;
 
static  CPU_INT16U bottles;
static  CPU_INT16U cans;
static  CPU_INT08U  sodas;
static  CPU_INT32U sales;
static  CPU_INT32U quantity;
 
 
int  main (void)
{
   
 ConfigINT0(EXT_INT_PRI_0|RISING_EDGE_INT|EXT_INT_ENABLE);
ConfigINT1(EXT_INT_PRI_1|RISING_EDGE_INT|EXT_INT_ENABLE);
ConfigINT2(EXT_INT_PRI_2|RISING_EDGE_INT|EXT_INT_ENABLE);
	CPU_Init();                                                       	/* Initialize the uC/CPU services                       	*/
 
	BSP_IntDisAll();
 
	OSInit(&os_err);                                                  	/* Init uC/OS-III.	                                      */
 
	OSTaskCreate((OS_TCB  	*)&App_TaskStartTCB,                    	/* Create the start task                                	*/
             	(CPU_CHAR	*)"Start",
             	(OS_TASK_PTR  )App_TaskStart,
             	(void    	*)0,
             	(OS_PRIO  	)APP_CFG_TASK_START_PRIO,
             	(CPU_STK 	*)&App_TaskStartStk[0],
             	(CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE_LIMIT,
             	(CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE,
             	(OS_MSG_QTY   )0u,
             	(OS_TICK  	)0u,
             	(void    	*)0,
             	(OS_OPT   	)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
             	(OS_ERR  	*)&os_err);
 
	OSStart(&os_err);                                                 	/* Start multitasking (i.e. give control to uC/OS-III). 	*/
 
	(void)&os_err;
 
	return (0);
}
 
/*$PAGE*/
/*
*********************************************************************************************************
*                                      	STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*           	initialize the ticker only once multitasking has started.
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*********************************************************************************************************
*/
 
 
 
static  void  App_TaskStart (void *p_arg)
{
   
    (void)p_arg;
 
	BSP_InitIO();                                                   	/* Initialize BSP functions                             	*/
 
	Mem_Init();           	                                  /* Initialize memory managment module               	*/
	Math_Init();                                            	/* Initialize mathematical module                   	*/
 
#if (OS_CFG_STAT_TASK_EN > 0u)
	OSStatTaskCPUUsageInit(&os_err);                           	/* Determine CPU capacity                           	*/
#endif
 
#ifdef CPU_CFG_INT_DIS_MEAS_EN
	CPU_IntDisMeasMaxCurReset();
#endif
 
	App_TaskCreate();                                       	/* Create Application tasks                         	*/
 
	App_ObjCreate();                                        	/* Create Application kernel objects                	*/
 
   
    OSTaskSemPend(0, OS_OPT_PEND_BLOCKING, &ts ,&os_err);
}
 
/*
*********************************************************************************************************
*                                      	AppTaskCreate()
*
* Description : Create application tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s) 	: none.
*********************************************************************************************************
*/
 
static  void  App_TaskCreate (void)
{
   
    OSMutexCreate (&Multiplier_Mutex, "Multipler Mutex", &os_err);
   
    
    OSMutexPost (&Multiplier_Mutex, OS_OPT_PEND_BLOCKING, &os_err);
   
    
        OSTaskCreate((OS_TCB  	*)&PollingTCB,                    	/* Create the start task                                	*/
             	(CPU_CHAR	*)"Polling Task",
             	(OS_TASK_PTR  )Polling,
             	(void    	*)0,
             	(OS_PRIO  	)APP_CFG_POLLING_PRIO,
             	(CPU_STK 	*)&PollingStk[0],
             	(CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE_LIMIT,
             	(CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE,
             	(OS_MSG_QTY   )0u,
             	(OS_TICK  	)0u,
             	(void    	*)0,
             	(OS_OPT   	)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
             	(OS_ERR  	*)&os_err);
           
        
        OSTaskCreate((OS_TCB      *)&LED_TCB,                    	/* Create the start task                                	*/
             	(CPU_CHAR	*)"LED",
             	(OS_TASK_PTR  )LED,
             	(void    	*)0,
             	(OS_PRIO  	)APP_CFG_LED_PRIO,
             	(CPU_STK 	*)&LEDStk[0],
             	(CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE_LIMIT,
             	(CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE,
             	(OS_MSG_QTY   )0u,
             	(OS_TICK  	)0u,
             	(void    	*)0,
             	(OS_OPT   	)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
             	(OS_ERR  	*)&os_err);
      
        OSTaskCreate((OS_TCB  	*)&CountingTCB,                    	/* Create the start task                                	*/
             	(CPU_CHAR	*)"Counting",
             	(OS_TASK_PTR  ) Counting,
             	(void    	*)0,
             	(OS_PRIO  	)APP_CFG_COUNTING_PRIO,
             	(CPU_STK 	*)&CountingStk[0],
             	(CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE_LIMIT,
             	(CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE,
             	(OS_MSG_QTY   )100u,
             	(OS_TICK  	)0u,
             	(void    	*)0,
   	          (OS_OPT   	)(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
             	(OS_ERR  	*)&os_err);
       
        
}
 
 
/*
*********************************************************************************************************
*        	                              App_ObjCreate()
*
* Description : Create application kernel objects tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s) 	: none.
*********************************************************************************************************
*/
 
static  void  App_ObjCreate (void)
{
}
 
 
 
 
void Polling(void)
{
         
    while(DEF_ON)
	{
    	if(BTN1!=0)
    	{
        	OSTaskQPost(&CountingTCB, 4, 1u, OS_OPT_POST_FIFO, &os_err);
    	}
    	if(BTN2!=0)
    	{
        	OSTaskQPost(&CountingTCB, 3, 1u, OS_OPT_POST_FIFO, &os_err);
    	}
    	if(BTN3!=0)
    	{
        	OSTaskQPost(&CountingTCB, 1, 1u, OS_OPT_POST_FIFO, &os_err);
    	}
    	else
    	{
        	OSTaskSemPost(&LED_TCB, OS_OPT_NONE, &os_err );
    	}
    	if(SW1 != 0)
    	{
        	toggle_value = 1;
    	}
    	else
    	{
        	toggle_value = 0;
    	}
       
        OSTimeDlyHMSM(0u,0u,0u,100u, OS_OPT_TIME_HMSM_STRICT, &os_err);  
        Nop();
	}
}

 
void LED(void)
{
	int b;
	CPU_INT08U Temp;
	while(DEF_ON)
	{
       
        if(toggle_value)
    	{
      	Temp = quantity; 
        }
    	else
    	{
      	Temp = sales;
        }
    	for(b=1;b<=8;b++,Temp/=2)
    	{
        	LED_Off(b);
        	if(Temp%2)
        	{
            	LED_On(b);
        	}
    	}
    	OSTaskSemPend(0, OS_OPT_PEND_BLOCKING, &ts, &os_err);
	}
}
 /*This task counts the amount of items that are sold. With each button
  *pressed dependant on the button. If BTN1 is pressed case 1 is used 
  *which adds a “soda”. 
void Counting(void)
{
   CPU_INT08U message;
   while(DEF_ON)
   {
    	message = OSTaskQPend( 0, OS_OPT_PEND_BLOCKING, &j, &ts, &os_err);
       
        switch (message)
    	{
        	case 4:
                bottles++;
            	break;
           
            case 3:
                cans++;
            	break;
        	case 1:
            	sodas++;
            	break;            
        }                
        quantity++;
    	sales += message;
    	OSTaskSemPost(&LED_TCB, OS_OPT_NONE, &os_err);
   }
   
}
 
 /* This is code that would have been used if interrupts did work out.
void BSP_INT1Handler(void)
{
	OS_ERR err;
	OSTaskQPost(&CountingTCB,3,1,OS_OPT_POST_FIFO,&os_err);
   
}
 
void BSP_INT0Handler(void)
{
	OS_ERR err;
	OSTaskQPost(&CountingTCB,4,1,OS_OPT_POST_FIFO,&os_err);
 
}
void BSP_INT2Handler(void)
{
	OS_ERR err;
	OSTaskQPost(&CountingTCB,1,1,OS_OPT_POST_FIFO,&os_err);
 
}*/
 

