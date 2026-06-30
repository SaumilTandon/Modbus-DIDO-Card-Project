
#include <stdio.h>

#include "wifi_ap.h"
#include "web_server.h"
#include "driver/uart.h"
#include "driver/gpio.h"


#define UART_PORT UART_NUM_2
#define TXD_PIN   GPIO_NUM_17
#define RXD_PIN   GPIO_NUM_16

void uart_init_custom(void)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_driver_install(UART_PORT, 1024, 0, 0, NULL, 0);
    uart_param_config(UART_PORT, &uart_config);
    uart_set_pin(UART_PORT, TXD_PIN, RXD_PIN,
                 UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);
}

void app_main(void)
{
    printf("Starting DYULABS Dashboard...\n");

    uart_init_custom();

    wifi_init_softap();
    start_webserver();

    uint8_t rx_buffer[128];

    while (1)
    {
        
        const char *msg = "PING\r\n";

        uart_write_bytes(UART_PORT,
                         msg,
                         strlen(msg));

        printf("ESP32 Sent: %s", msg);
        fflush(stdout);

        int len = uart_read_bytes(
            UART_PORT,
            rx_buffer,
            sizeof(rx_buffer) - 1,
            pdMS_TO_TICKS(300)
        );

        if(len > 0)
        {
            rx_buffer[len] = '\0';
            printf("STM32 Response: %s", rx_buffer);
            fflush(stdout);
        }

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}