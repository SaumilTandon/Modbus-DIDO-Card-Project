#include "misc_sx126x.h"

#include "sx126x.h"
#include "sx126x_hal.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart3;
static volatile bool tx_done = false;
static volatile bool rx_done = false;

bool misc_sx126x_init(uint8_t sf)
{
    tx_done = false;
    rx_done = false;

    sx126x_hal_reset(NULL);

    HAL_Delay(100);

    sx126x_set_standby(
            NULL,
            SX126X_STANDBY_CFG_RC);

    sx126x_set_reg_mode(
            NULL,
            SX126X_REG_MODE_DCDC);

    sx126x_set_pkt_type(
            NULL,
            SX126X_PKT_TYPE_LORA);


    sx126x_chip_status_t chip_status;

    sx126x_get_status(
            NULL,
            &chip_status);

    char txt[50];

    sprintf(txt,
            "MODE=%d CMD=%d\r\n",
            chip_status.chip_mode,
            chip_status.cmd_status);

    HAL_UART_Transmit(
            &huart3,
            (uint8_t*)txt,
            strlen(txt),
            HAL_MAX_DELAY);


    sx126x_set_rf_freq(
            NULL,
            867000000);
    sx126x_set_tx_params(
            NULL,
            22,
            SX126X_RAMP_200_US);
    sx126x_set_buffer_base_address(
            NULL,
            0x00,
            0x00);
    sx126x_set_dio_irq_params(
            NULL,
            SX126X_IRQ_TX_DONE,
            SX126X_IRQ_TX_DONE,
            SX126X_IRQ_NONE,
            SX126X_IRQ_NONE);

    return true;
}


bool misc_sx126x_transmit(
        uint8_t *data,
        uint16_t len,
        uint32_t timeout)
{
    tx_done = false;

    sx126x_write_buffer(
            NULL,
            0x00,
            data,
            len);

    sx126x_set_tx(
            NULL,
            timeout);

    return true;
}



void misc_sx126x_receive(
        uint32_t timeout)
{
    (void)timeout;
}



void misc_sx126x_irq_cb(void)
{
    sx126x_irq_mask_t irq_status;

    sx126x_get_irq_status(
            NULL,
            &irq_status);

    sx126x_clear_irq_status(
            NULL,
            SX126X_IRQ_ALL);

    if(irq_status & SX126X_IRQ_TX_DONE)
    {
        tx_done = true;

        uart_print("TX DONE\r\n");
    }

    if(irq_status & SX126X_IRQ_RX_DONE)
    {
        rx_done = true;

        char txt[] = "RX DONE\r\n";

        HAL_UART_Transmit(
                &huart3,
                (uint8_t*)txt,
                sizeof(txt)-1,
                HAL_MAX_DELAY);
    }
}
