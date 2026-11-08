#pragma once

#include "usart.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

HAL_StatusTypeDef HAL_printf(const char *format, ...);
void HAL_printf_SetInstance(UART_HandleTypeDef *huart);

#if USE_HAL_UART_REGISTER_CALLBACKS == 1U
HAL_StatusTypeDef HAL_printf_EnableDMA(void);
#endif

#ifdef __cplusplus
}
#endif
