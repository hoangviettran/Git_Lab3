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
		if(timer0_flag == 1){
			counter++;
		    if(counter <= 5){
		    	Horizontal_TrafficLight = 5-counter;
	   		    //display7SEG(5-counter);
			    HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_SET ) ;
	    	    HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_RESET ) ;
			    if(counter <= 2){
			    	Vertial_TrafficLight = 2 - counter;
    			    //display7SEG_1(2-counter);
				    HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_RESET ) ;
				    HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_SET ) ;
				    HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_RESET ) ;
				}
				else{
					Vertial_TrafficLight = 5 - counter;
					//display7SEG_1(5-counter);
					HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_RESET ) ;
					HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_RESET ) ;
					HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_SET ) ;
				}
		    }
		    else if(counter <= 7){
				Horizontal_TrafficLight = 7 - counter;
		    	//display7SEG(7-counter);
				HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_RESET ) ;
				HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_SET ) ;
				HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_RESET ) ;

				Vertial_TrafficLight = 10 - counter;
				//display7SEG_1(10-counter);
				HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_SET ) ;
				HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_RESET ) ;
		    }
		    else if(counter <= 10){
				Horizontal_TrafficLight = 10 - counter;
		    	//display7SEG(10-counter);
			    HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_RESET ) ;
				HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_SET ) ;
				Vertial_TrafficLight = 10 - counter;
				//display7SEG_1(10-count);
			}
			if(counter >= 10) counter = 0;
			setTimer0(1000);
		}
		if(isButton1Pressed() == 1){
			setTimer0(1000);
			counter = 0;
			Set_time = 5;
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
		counter = 0;
		state = NOR;
		break;
	case RED_M:
		ModeValue = 2;
		updateClockBuffer();
		if(isButton2Pressed() == 1){
			RED_Time_value++;
			if(RED_Time_value >= 100) RED_Time_value = 0;
		}
		if(isButton3Pressed() == 1){
			Set_time = RED_Time_value;
			counter = 0;
		}
		if(timer0_flag == 1){
			counter++;
		    if(counter <= Set_time){
		    	Horizontal_TrafficLight = Set_time-counter;
	   		    //display7SEG(5-counter);
			    HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_SET ) ;
	    	    HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_RESET ) ;
			    if(counter <= Set_time/3){
			    	Vertial_TrafficLight = Set_time/3 - counter;
    			    //display7SEG_1(2-counter);
				    HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_RESET ) ;
				    HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_SET ) ;
				    HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_RESET ) ;
				}
				else{
					Vertial_TrafficLight = Set_time - counter;
					//display7SEG_1(5-counter);
					HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_RESET ) ;
					HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_RESET ) ;
					HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_SET ) ;
				}
		    }
		    else if(counter <= Set_time*4/3){
				Horizontal_TrafficLight = Set_time*4/3 - counter;
		    	//display7SEG(7-counter);
				HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_RESET ) ;
				HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_SET ) ;
				HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_RESET ) ;

				Vertial_TrafficLight = Set_time*2 - counter;
				//display7SEG_1(10-counter);
				HAL_GPIO_WritePin ( RED_1_GPIO_Port , RED_1_Pin , GPIO_PIN_SET ) ;
				HAL_GPIO_WritePin ( YELLOW_1_GPIO_Port , YELLOW_1_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( GREEN_1_GPIO_Port , GREEN_1_Pin , GPIO_PIN_RESET ) ;
		    }
		    else if(counter <= Set_time*2){
				Horizontal_TrafficLight = Set_time*2 - counter;
		    	//display7SEG(10-counter);
			    HAL_GPIO_WritePin ( RED_GPIO_Port , RED_Pin , GPIO_PIN_RESET ) ;
			    HAL_GPIO_WritePin ( YELLOW_GPIO_Port , YELLOW_Pin , GPIO_PIN_RESET ) ;
				HAL_GPIO_WritePin ( GREEN_GPIO_Port , GREEN_Pin , GPIO_PIN_SET ) ;
				Vertial_TrafficLight = Set_time*2 - counter;
				//display7SEG_1(10-count);
			}
			if(counter >= Set_time*2) counter = 0;
			setTimer0(1000);
		}
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
