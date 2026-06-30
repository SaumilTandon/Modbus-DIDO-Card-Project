#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"

#define UART_PORT UART_NUM_2
#define TX_PIN 17
#define RX_PIN 16

void app_main(void)
{
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_driver_install(UART_PORT, 1024, 1024, 0, NULL, 0);

    uart_param_config(UART_PORT, &uart_config);

    uart_set_pin(UART_PORT,
                 TX_PIN,
                 RX_PIN,
                 UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);

    uint8_t rx_buffer[100];

    while (1)
    {
        const char *msg = "Hello\n";

        uart_write_bytes(UART_PORT,
                         msg,
                         strlen(msg));

        printf("Sent: Hello\n");

        int len = uart_read_bytes(UART_PORT,
                                  rx_buffer,
                                  sizeof(rx_buffer) - 1,
                                  pdMS_TO_TICKS(1000));

        if (len > 0)
        {
            rx_buffer[len] = '\0';

            printf("Received: %s\n", rx_buffer);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}