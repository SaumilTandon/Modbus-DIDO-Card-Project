#ifndef MISC_SX126X_HAL_H
#define MISC_SX126X_HAL_H

#include <stdbool.h>
#include <stdint.h>

bool misc_sx126x_hal_init(void);
bool misc_sx126x_hal_deinit(void);

bool misc_sx126x_hal_reset(void);
bool misc_sx126x_hal_wakeup(void);

bool misc_sx126x_hal_write(
        const uint8_t *command,
        const uint16_t command_length,
        const uint8_t *data,
        const uint16_t data_length);

bool misc_sx126x_hal_read(
        const uint8_t *command,
        const uint16_t command_length,
        uint8_t *data,
        const uint16_t data_length);

#endif
