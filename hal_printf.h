#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void HAL_printf(const char *format, ...);
HAL_StatusTypeDef HAL_printf_EnableDMA(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif
