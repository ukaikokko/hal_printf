#pragma once

#include "usart.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

HAL_StatusTypeDef HAL_printf(const char *format, ...);
void HAL_printf_SetInstance(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_printf_EnableDMA();

#ifdef __cplusplus
}
#endif
