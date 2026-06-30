#include "misc_sx126x_hal.h"

#include "main.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

extern SPI_HandleTypeDef hspi1;

/*********************************************************************
 * Private Functions
 *********************************************************************/

static bool misc_sx126x_hal_ready(uint32_t timeout)
{
    uint32_t tick_start = HAL_GetTick();

    while((HAL_GetTick() - tick_start) < timeout)
    {
        if(HAL_GPIO_ReadPin(
                SX1262_BUSY_GPIO_Port,
                SX1262_BUSY_Pin)
                == GPIO_PIN_RESET)
        {
            return true;
        }
    }

    return false;
}

static void misc_sx126x_hal_select(void)
{
    HAL_GPIO_WritePin(
            SX1262_NSS_GPIO_Port,
            SX1262_NSS_Pin,
            GPIO_PIN_RESET);
}

static void misc_sx126x_hal_deselect(void)
{
    HAL_GPIO_WritePin(
            SX1262_NSS_GPIO_Port,
            SX1262_NSS_Pin,
            GPIO_PIN_SET);
}

/*********************************************************************
 * Public Functions
 *********************************************************************/

bool misc_sx126x_hal_init(void)
{
    return true;
}




bool misc_sx126x_hal_reset(void)
{
    HAL_GPIO_WritePin(
            SX1262_RESET_GPIO_Port,
            SX1262_RESET_Pin,
            GPIO_PIN_RESET);

    HAL_Delay(10);

    HAL_GPIO_WritePin(
            SX1262_RESET_GPIO_Port,
            SX1262_RESET_Pin,
            GPIO_PIN_SET);

    HAL_Delay(20);

    return true;
}

bool misc_sx126x_hal_wakeup(void)
{
    uint8_t wakeup = 0x00;

    misc_sx126x_hal_select();

    HAL_SPI_Transmit(
            &hspi1,
            &wakeup,
            1,
            HAL_MAX_DELAY);

    misc_sx126x_hal_deselect();

    HAL_Delay(1);

    return misc_sx126x_hal_ready(1000);
}

bool misc_sx126x_hal_write(
        const uint8_t *command,
        const uint16_t command_length,
        const uint8_t *data,
        const uint16_t data_length)
{
    if(misc_sx126x_hal_ready(5000) == false)
    {
        return false;
    }

    misc_sx126x_hal_select();

    if(command_length > 0)
    {
        if(HAL_SPI_Transmit(
                &hspi1,
                (uint8_t*)command,
                command_length,
                HAL_MAX_DELAY) != HAL_OK)
        {
            misc_sx126x_hal_deselect();
            return false;
        }
    }

    if(data_length > 0)
    {
        if(HAL_SPI_Transmit(
                &hspi1,
                (uint8_t*)data,
                data_length,
                HAL_MAX_DELAY) != HAL_OK)
        {
            misc_sx126x_hal_deselect();
            return false;
        }
    }

    misc_sx126x_hal_deselect();

    return true;
}

bool misc_sx126x_hal_read(
        const uint8_t *command,
        const uint16_t command_length,
        uint8_t *data,
        const uint16_t data_length)
{
    uint8_t dummy[data_length];

    memset(dummy, 0x00, data_length);

    if(misc_sx126x_hal_ready(5000) == false)
    {
        return false;
    }

    misc_sx126x_hal_select();

    if(command_length > 0)
    {
        if(HAL_SPI_Transmit(
                &hspi1,
                (uint8_t*)command,
                command_length,
                HAL_MAX_DELAY) != HAL_OK)
        {
            misc_sx126x_hal_deselect();
            return false;
        }
    }

    if(data_length > 0)
    {
        if(HAL_SPI_TransmitReceive(
                &hspi1,
                dummy,
                data,
                data_length,
                HAL_MAX_DELAY) != HAL_OK)
        {
            misc_sx126x_hal_deselect();
            return false;
        }
    }

    misc_sx126x_hal_deselect();

    return true;
}

bool misc_sx126x_hal_deinit()
{
	HAL_SPI_DeInit(&hspi1);
	return true;
}
