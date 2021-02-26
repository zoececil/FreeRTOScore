#ifndef INC_TASK_H
#define INC_TASK_H
#include "FreeRTOS.h"

#define taskENTER_CRITICAL()    portENTER_CRITICAL()
#define taskEXIT_CRITICAL()    portEXIT_CRITICAL()
#define taskENTER_CRITICAL_FROM_ISR()    portSET_INTERRUPT_MASK_FROM_ISR()
#define taskEXIT_CRITICAL_FROM_ISR(x)    portCLEAR_INTERRUPT_MASK_FROM_ISR(x)

#define tskIDLE_PRIORITY			       ( ( UBaseType_t ) 0U )
#define taskYIELD()    portYIELD()
typedef struct tskTaskControlBlock
{
	volatile StackType_t    *pxTopOfStack;    /* 栈顶指针 */
	ListItem_t			    xStateListItem;   /* 任务节点 */
    StackType_t             *pxStack;         /* 任务栈起始地址 */
	char                    pcTaskName[ configMAX_TASK_NAME_LEN ];  /* 任务名称，字符串形式 */
	TickType_t xTicksToDelay; /* 用于延时 */
	UBaseType_t			uxPriority;
} tskTCB;
typedef tskTCB TCB_t;

/* 任务句柄 */
typedef void * TaskHandle_t;

#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic(	TaskFunction_t pxTaskCode,
					            const char * const pcName,
                                const uint32_t ulStackDepth,
					            void * const pvParameters,
								UBaseType_t uxPriority,              /* 任务优先级，数值越大，优先级越高 */
					            StackType_t * const puxStackBuffer,
					            TCB_t * const pxTaskBuffer );
#endif /* configSUPPORT_STATIC_ALLOCATION */
static void prvInitialiseNewTask( 	TaskFunction_t pxTaskCode,              /* 任务入口 */
									const char * const pcName,              /* 任务名称，字符串形式 */
									const uint32_t ulStackDepth,            /* 任务栈大小，单位为字 */
									void * const pvParameters,              /* 任务形参 */
									UBaseType_t uxPriority,              /* 任务优先级，数值越大，优先级越高 */
									TaskHandle_t * const pxCreatedTask,     /* 任务句柄 */
									TCB_t *pxNewTCB );
void prvInitialiseTaskLists( void );                                
void vTaskStartScheduler( void );
void vTaskSwitchContext( void );
void vTaskDelay( const TickType_t xTicksToDelay );
void xTaskIncrementTick( void );
static portTASK_FUNCTION( prvIdleTask, pvParameters );
static void prvAddNewTaskToReadyList( TCB_t *pxNewTCB );
#endif /* INC_TASK_H */

