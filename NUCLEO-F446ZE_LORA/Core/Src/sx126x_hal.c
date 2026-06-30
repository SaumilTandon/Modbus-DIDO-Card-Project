#include "sx126x_hal.h"
#include "misc_sx126x_hal.h"

sx126x_hal_status_t sx126x_hal_write(
        const void *context,
        const uint8_t *command,
        const uint16_t command_length,
        const uint8_t *data,
        const uint16_t data_length)
{
    (void)context;

    if(misc_sx126x_hal_write(
            command,
            command_length,
            data,
            data_length) == false)
    {
        return SX126X_HAL_STATUS_ERROR;
    }

    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_read(
        const void *context,
        const uint8_t *command,
        const uint16_t command_length,
        uint8_t *data,
        const uint16_t data_length)
{
    (void)context;

    if(misc_sx126x_hal_read(
            command,
            command_length,
            data,
            data_length) == false)
    {
        return SX126X_HAL_STATUS_ERROR;
    }

    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_reset(
        const void *context)
{
    (void)context;

    if(misc_sx126x_hal_reset() == false)
    {
        return SX126X_HAL_STATUS_ERROR;
    }

    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_wakeup(
        const void *context)
{
    (void)context;

    if(misc_sx126x_hal_wakeup() == false)
    {
        return SX126X_HAL_STATUS_ERROR;
    }

    return SX126X_HAL_STATUS_OK;
}
