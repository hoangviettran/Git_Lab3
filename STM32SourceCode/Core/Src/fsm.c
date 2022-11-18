/*
 * fsm.c
 *
 *  Created on: 5 Oct 2022
 *      Author: hoang
 */


#include "fsm.h"

int numOfLed = 0;
void Seg7Scan(){
	if(timer1_flag == 1){
			  if(numOfLed == 0){
					setTimer1 (140);
					update7SEG(1);
					numOfLed = 1;
			  }
			  else if(numOfLed == 1){
					setTimer1 (140);
					update7SEG(2);
					numOfLed = 2;
			  }
			  else if(numOfLed == 2){
					setTimer1 (140);
					update7SEG(3);
					numOfLed = 3;
			  }
			  else if(numOfLed == 3){
					setTimer1 (140);
					update7SEG(4);
					numOfLed = 4;
			  }
			  else if(numOfLed == 4){
					setTimer1 (140);
					update7SEG(5);
					numOfLed = 5;
			  }
			  else if(numOfLed == 5){
					setTimer1 (140);
					update7SEG(6);
					numOfLed = 6;
			  }
			  else{
					setTimer1 (140);
					update7SEG(0);
					numOfLed = 0;
			  }
	}
}


//automatic mode
void fsm_automatic_run(){
	switch(state){
	case NOR:
		ModeValue = 1;
		updateClockBuffer();
		if(isButton1Pressed() == 1){
		    state = RED_M;
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
		state = NOR;
		break;
	case RED_M:
		ModeValue = 2;
		updateClockBuffer();
		if(isButton1Pressed() == 1){
			state = YELLOW_M;
		}
		break;
	case YELLOW_M:
		ModeValue = 3;
		updateClockBuffer();
		if(isButton1Pressed() == 1){
			state = GREEN_M;
		}
		break;
	case GREEN_M:
		ModeValue = 4;
		updateClockBuffer();
		if(isButton1Pressed() == 1){
			state = NOR;
		}
		break;
	default:
		break;
	}
}
