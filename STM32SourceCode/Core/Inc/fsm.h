/*
 * fsm.h
 *
 *  Created on: 5 Oct 2022
 *      Author: hoang
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "global.h"
#include "software_timer.h"
#include "main.h"
#include "button.h"
#include "display7SEG.h"

void Seg7Scan();

void fsm_automatic_run();

void fsm_manual_run();

void fsm_simple_buttons_run();

#endif /* INC_FSM_H_ */
