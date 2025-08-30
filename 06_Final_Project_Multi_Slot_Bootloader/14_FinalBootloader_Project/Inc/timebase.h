/*
 * timebase.h
 *
 *  Created on: Aug 24, 2025
 *      Author: Engr_Moneeb
 */


#ifndef TIMEBASE_H_
#define TIMEBASE_H_

#include <stdint.h>

uint32_t get_tick(void);

void delay(uint32_t delay);

void timebase_init(void);


#endif /* TIMEBASE_H_ */
