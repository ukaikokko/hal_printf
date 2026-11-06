#include "hal_printf.h"

#include "usart.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

volatile static bool flag = true;
static bool isEnableDMA = false;
UART_HandleTypeDef *HUART = NULL;

void HAL_printf(const char *format, ...) {
  static char result[100];

  while (!flag)
    ;

  va_list args;
  va_start(args, format);

  int len = vsnprintf(result, sizeof(result), format, args);

  va_end(args);

  if (len <= 0 || len >= sizeof(result)) {
    return;
  }

  flag = false;
  HAL_StatusTypeDef status;
  if (isEnableDMA) {
    status =
        HAL_UART_Transmit_DMA(HUART, (const uint8_t *)result, (uint16_t)len);
  } else {
    status =
        HAL_UART_Transmit(HUART, (const uint8_t *)result, (uint16_t)len, 100);
  }

  if (status != HAL_OK) {
    flag = true;
  }
}

HAL_StatusTypeDef HAL_printf_EnableDMA(UART_HandleTypeDef *huart) {
  isEnableDMA = true;
  HUART = huart;
  return HAL_UART_RegisterCallback(HUART, HAL_UART_TX_COMPLETE_CB_ID,
                                   &HAL_printf_UART_Callback);
}

void HAL_printf_UART_Callback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART2) {
    flag = true;
  }
}
