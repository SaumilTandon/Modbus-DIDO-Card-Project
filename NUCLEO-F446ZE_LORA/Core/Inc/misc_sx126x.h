#ifndef MISC_SX126X_H
#define MISC_SX126X_H

#include <stdint.h>
#include <stdbool.h>

bool misc_sx126x_init(uint8_t sf);

bool misc_sx126x_transmit(
        uint8_t *data,
        uint16_t len,
        uint32_t timeout);

void misc_sx126x_receive(
        uint32_t timeout);

void misc_sx126x_irq_cb(void);

#endif
