#include "hal_printf.h"

#include "usart.h"
#include <stdarg.h>
#include <stdio.h>

void HAL_printf(const char *format, ...) {
  char result[100];

  va_list args;
  va_start(args, format);

  int len = vsnprintf(result, sizeof(result), format, args);

  va_end(args);

  if (len <= 0 || len >= sizeof(result)) {
    return;
  }

  HAL_UART_Transmit(&huart2, (const uint8_t *)result, (uint16_t)len, 100);
}
