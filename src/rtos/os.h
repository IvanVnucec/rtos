#ifndef OS_H
#define OS_H


/**
 * \file            os.h
 * \brief           OS header file
 */


/*******************************************************************************************************
 *                         INCLUDE FILES
 ******************************************************************************************************/
#include <stdint.h>

#include "libopencm3/cm3/cortex.h"
#include "os_errors.h"
#include "os_forward.h"
#include "mutex_forward.h"


/*******************************************************************************************************
 *                         CONSTANTS
 ******************************************************************************************************/
#define TRUE (1ul)
#define FALSE (0ul)

#define NULL  ((void *)0)

#define OS_ENTER_CRITICAL(x) (cm_disable_interrupts(x))
#define OS_EXIT_CRITICAL(x)  (cm_enable_interrupts(x))

#define OS_SCHED_FREQ_HZ	(1000ul)
#define OS_MS_TO_TICKS(ms)	((ms) * OS_SCHED_FREQ_HZ / 1000ul)

#define OS_IDLE_TASK_PRIORITY 	(0ul)


/*******************************************************************************************************
 *                         DATA STRUCTURES
 ******************************************************************************************************/
enum OS_TaskState_ENUM {
    OS_TASK_STATE_DORMANT,
    OS_TASK_STATE_READY,
    OS_TASK_STATE_RUNNING,
    OS_TASK_STATE_PENDING
};


struct OS_TCB_STRUCT {
    uint32_t *sp;
    OS_TaskState_E taskState;
    uint32_t taskPriority;
    uint32_t taskTick;
    uint8_t *taskName;
    OS_Mutex_S *mutex;
    OS_TCB_S *TCBNext;
    OS_TCB_S *mutexPendingNext;
};


/*******************************************************************************************************
 *                         GLOBAL AND STATIC VARIABLES
 ******************************************************************************************************/


/*******************************************************************************************************
 *                         PUBLIC FUNCTION PROTOTYPES
 ******************************************************************************************************/
void OS_TaskCreate(OS_TCB_S *taskTCB, 
    void (*taskPointer)(void), 
    uint32_t taskPriority, 
    uint8_t *taskName,
    uint32_t *taskStack, 
    uint32_t taskStackSize,
    OS_Error_E *err);

void OS_Schedule(void);
void OS_Init(OS_Error_E *err);
void OS_EnableScheduler(OS_Error_E *err);
void OS_DisableScheduler(OS_Error_E *err);
uint32_t OS_getOSTickCounter(void);
void OS_delayTicks(uint32_t ticks);
void OS_delayTime(uint32_t hours, 
    uint32_t minutes, 
    uint32_t seconds, 
    uint32_t miliseconds);
    
void OS_TaskTerminate(void);
void OS_TickHandler(void);

void PendSV_Handler(void);
void SysTick_Handler(void);


#endif /* #ifndef OS_H */
