#ifndef INC_FREERTOS_H
#define INC_FREERTOS_H

#include "FreeRTOSConfig.h"
#include "projdefs.h"
#include "portable.h"
#include "list.h"

#ifndef configUSE_TIME_SLICING
	#define configUSE_TIME_SLICING 1
#endif

#endif /* INC_FREERTOS_H */
