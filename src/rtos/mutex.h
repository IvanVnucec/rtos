#ifndef MUTEX_H
#define MUTEX_H


/**
 * \file            mutex.h
 * \brief           Mutex header file
 */


/*******************************************************************************************************
 *                         INCLUDE FILES
 ******************************************************************************************************/
#include "os.h"
#include "os_forward.h"
#include "mutex_forward.h"


/*******************************************************************************************************
 *                         CONSTANTS
 ******************************************************************************************************/

/*******************************************************************************************************
 *                         DATA STRUCTURES
 ******************************************************************************************************/
enum OS_MutexState_ENUM {
	OS_MUTEX_STATE_FREE,
	OS_MUTEX_STATE_OWNED
};


struct OS_Mutex_STRUCT {
	OS_MutexState_E state;
	OS_TCB_S *owner;
	uint32_t num_of_pending_tasks;	/* TODO: Do we need this variable? IvanVnucec */
	uint32_t isInitialized;
	uint32_t prioInversion;
	uint32_t oldOwnerTaskPriority;
	uint32_t isPrioInversion;
};


enum OS_MutexError_STRUCT {
	OS_MUTEX_ERROR_NONE,
	OS_MUTEX_ERROR_NULL_PTR,
	OS_MUTEX_ERROR_TIMEOUT,
	OS_MUTEX_ERROR_NOT_OWNER_POST,
	OS_MUTEX_ERROR_NOT_INITIALIZED
};


/*******************************************************************************************************
 *                         GLOBAL AND STATIC VARIABLES
 ******************************************************************************************************/

/*******************************************************************************************************
 *                         PUBLIC FUNCTION PROTOTYPES
 ******************************************************************************************************/
void OS_MutexInit(OS_Mutex_S *mutex, uint32_t prioInversion, OS_MutexError_E *err);
void OS_MutexPend(OS_Mutex_S *mutex, uint32_t timeout, OS_MutexError_E *err);
void OS_MutexPost(OS_Mutex_S *mutex, OS_MutexError_E *err);


#endif /* #ifndef MUTEX_H */
