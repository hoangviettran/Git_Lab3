/*
 * fsm.c
 *
 *  Created on: 5 Oct 2022
 *      Author: hoang
 */


#include "fsm.h"

#define COUNTER     10000 // set timer for manual mode (fsm_simple_buttons_run())
#define COUNTDOWN   1000  // set timer for automatic mode (fsm_simple_buttons_run())
//automatic mode
void fsm_automatic_run(){
	switch(state){
	case AUTO_DEC:
		if(timer1_flag == 1){
			if(counter > 0) counter--;
			setTimer1(COUNTDOWN);
		}
		if(isButton1Pressed() == 1){
		    counter = 0;
		    state = RS;
		}
		if(isButton2Pressed() == 1){
			setTimer1(COUNTER);
			counter++;
			if(counter >= 10) counter = 0;
			state = INC;
		}
		if(isButton3Pressed() == 1){
			setTimer1(COUNTER);
			counter--;
			if(counter < 0) counter = 9;
			state = DEC;
		}
		break;
	default:
		break;
	}
}
// manual mode
void fsm_simple_buttons_run(){
	switch(state){
	case INIT:
		counter = 0;
		state = RS;
		break;
	case INC:
		if(timer1_flag == 1){
			state = AUTO_DEC;
			counter--;
			if(counter < 0) counter = 9;
			setTimer1(COUNTDOWN);
		}
		if(isButton1Pressed() == 1){
			counter = 0;
			state = RS;
		}
		if(isButton2Pressed() == 1){
			setTimer1(COUNTER);
			counter++;
			if(counter >= 10) counter = 0;
		}
		if(isButton3Pressed() == 1){
			setTimer1(COUNTER);
			counter--;
			if(counter < 0) counter = 9;
			state = DEC;
		}
		break;
	case DEC:
		if(timer1_flag == 1){
			state = AUTO_DEC;
			counter--;
			if(counter < 0) counter = 9;
			setTimer1(COUNTDOWN);
		}
		if(isButton1Pressed() == 1){
			counter = 0;
			state = RS;
		}
		if(isButton2Pressed() == 1){
			setTimer1(COUNTER);
			counter++;
			if(counter >= 10) counter = 0;
			state = INC;
		}
		if(isButton3Pressed() == 1){
			setTimer1(COUNTER);
			counter--;
			if(counter < 0) counter = 9;
		}
		break;
	case RS:
		if(isButton2Pressed() == 1){
			setTimer1(COUNTER);
			counter++;
			if(counter >= 10) counter = 0;
			state = INC;
		}
		if(isButton3Pressed() == 1){
			setTimer1(COUNTER);
			counter--;
			if(counter < 0) counter = 9;
			state = DEC;
		}
		break;
	}
	default:
		break;
}
