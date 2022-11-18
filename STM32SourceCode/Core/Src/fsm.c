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

void clearAllLED(){
	HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_RESET ) ;
	HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_RESET ) ;
	HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_RESET ) ;
	HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_RESET ) ;
	HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_RESET ) ;
	HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_RESET ) ;
}

//automatic mode
void fsm_automatic_run(){
	switch(state){
	case NOR:
		ModeValue = 1;
		updateClockBuffer();
		if(timer0_flag == 1){
			counter++;
			counter_1++;
			//horizontal traffic light
		    if(counter <= RED_Time_value){
		    	Horizontal_TrafficLight = RED_Time_value - counter;
			    HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_SET ) ;
	    	    HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_RESET ) ;
		    }
		    else if(counter <= RED_Time_value + YELLOW_Time_value){
				Horizontal_TrafficLight = RED_Time_value + YELLOW_Time_value - counter;
				HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_RESET ) ;
				HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_SET ) ;
				HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_RESET ) ;
		    }
		    else if(counter <= RED_Time_value + YELLOW_Time_value + GREEN_Time_value){
				Horizontal_TrafficLight = RED_Time_value + YELLOW_Time_value + GREEN_Time_value - counter;
			    HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_RESET ) ;
				HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_SET ) ;
			}
			if(counter >= RED_Time_value + YELLOW_Time_value + GREEN_Time_value) counter = 0;
			//vertical traffic light
		    if(counter_1 <= YELLOW_Time_value){
		    	Vertical_TrafficLight = YELLOW_Time_value - counter_1;
				HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_RESET ) ;
				HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_SET ) ;
				HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_RESET ) ;
		    }
		    else if(counter_1 <= GREEN_Time_value + YELLOW_Time_value){
				Vertical_TrafficLight = GREEN_Time_value + YELLOW_Time_value - counter_1;
			    HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_RESET ) ;
				HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_SET ) ;
		    }
		    else if(counter_1 <= RED_Time_value + YELLOW_Time_value + GREEN_Time_value){
				Vertical_TrafficLight = RED_Time_value + YELLOW_Time_value + GREEN_Time_value - counter_1;
			    HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_SET ) ;
	    	    HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_RESET ) ;
			}
			if(counter_1 >= RED_Time_value + YELLOW_Time_value + GREEN_Time_value) counter_1 = 0;
			setTimer0(1000);
		}
		if(isButton1Pressed() == 1){
			setTimer0(1000);
			counter = 0;
			counter_1 = 0;
			Set_time = RED_Time_value;
		    state = RED_M;
			//clear all the led
			clearAllLED();
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
		state = NOR;
		break;
	case RED_M:
		ModeValue = 2;
		updateClockBuffer();
		if(isButton2Pressed() == 1){
			Set_time++;
			if(Set_time>= 100) Set_time = 0;
		}
		if(isButton3Pressed() == 1){
			RED_Time_value = Set_time;
		}
		if(timer0_flag == 1){
			HAL_GPIO_TogglePin(RED_GPIO_Port, RED_Pin);
			HAL_GPIO_TogglePin(RED_1_GPIO_Port, RED_1_Pin);
			setTimer0(250);
		}
		if(isButton1Pressed() == 1){
			setTimer0(250);
			Set_time = YELLOW_Time_value;
			state = YELLOW_M;
			//clear all the led
			clearAllLED();
		}
		break;
	case YELLOW_M:
		ModeValue = 3;
		updateClockBuffer();
		if(isButton2Pressed() == 1){
			Set_time++;
			if(Set_time>= 100) Set_time = 0;
		}
		if(isButton3Pressed() == 1){
			YELLOW_Time_value = Set_time;
		}
		if(timer0_flag == 1){
			HAL_GPIO_TogglePin(YELLOW_GPIO_Port, YELLOW_Pin);
			HAL_GPIO_TogglePin(YELLOW_1_GPIO_Port, YELLOW_1_Pin);
			setTimer0(250);
		}
		if(isButton1Pressed() == 1){
			setTimer0(250);
			Set_time = GREEN_Time_value;
			state = GREEN_M;
			//clear all the led
			clearAllLED();
		}
		break;
	case GREEN_M:
		ModeValue = 4;
		updateClockBuffer();
		if(timer0_flag == 1){
			HAL_GPIO_TogglePin(GREEN_GPIO_Port, GREEN_Pin);
			HAL_GPIO_TogglePin(GREEN_1_GPIO_Port, GREEN_1_Pin);
			setTimer0(250);
		}
		if(isButton1Pressed() == 1){
			setTimer0(250);
			Set_time = 0;
			state = NOR;
			//clear all the led
			clearAllLED();
		}
		break;
	default:
		break;
	}
}
