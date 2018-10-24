#ifndef SLIDER_H
#define SLIDER_H
#include "can/CAN_driver.h"

typedef struct slider_position
{
    uint8_t left;
    uint8_t right;
} slider_status;

slider_status slider_get_status(void);
void slider_transmit_position(void);

#endif
