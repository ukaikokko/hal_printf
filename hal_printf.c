#include "hal_printf.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

volatile static bool flag = true;
static bool isEnableDMA = false;
static bool isInitialized = false;

UART_HandleTypeDef *HUART = NULL;

HAL_StatusTypeDef HAL_printf(const char *format, ...) {
  if (!isInitialized) {
    return false;
  }

  static char result[100];

  while (!flag)
    ;

  va_list args;
  va_start(args, format);

  int len = vsnprintf(result, sizeof(result), format, args);

  va_end(args);

  if (len <= 0 || len >= sizeof(result)) {
    return HAL_ERROR;
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
    return status;
  }

  if (!isEnableDMA) {
    flag = true;
  }

  return HAL_OK;
}

void HAL_printf_SetInstance(UART_HandleTypeDef *huart) {
  HUART = huart;
  isInitialized = (huart != NULL);
}

void HAL_printf_UART_Callback(UART_HandleTypeDef *huart) {
  if (HUART != NULL && huart->Instance == HUART->Instance) {
    flag = true;
  }
}

HAL_StatusTypeDef HAL_printf_EnableDMA(void) {
  HAL_StatusTypeDef status;
  status = HAL_UART_RegisterCallback(HUART, HAL_UART_TX_COMPLETE_CB_ID,
                                     &HAL_printf_UART_Callback);

  if (status != HAL_OK) {
    return status;
  } else {
    isEnableDMA = true;
    return HAL_OK;
  }
}
