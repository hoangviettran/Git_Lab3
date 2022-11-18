/*
 * button.c
 *
 *  Created on: Nov 5, 2022
 *      Author: tran
 */


#include "button.h"

int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;

int KeyReg0[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int KeyReg3[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int TimerForKeyPress[3] = {300, 300, 300};

//button1 = MODE, button2 = INC, button3 = SET
int isButton1Pressed(){
	if(button1_flag == 1){
		button1_flag = 0;
		return 1;
	}
	return 0;
}

int isButton2Pressed(){
	if(button2_flag == 1){
		button2_flag = 0;
		return 1;
	}
	return 0;
}

int isButton3Pressed(){
	if(button3_flag == 1){
		button3_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int i){
	switch(i){
	case 0:
		button1_flag = 1;
		break;
	case 1:
		button2_flag = 1;
		break;
	case 2:
		button3_flag = 1;
		break;
	default:
		break;
	}
}


void getKeyInput(){
	for(int i = 0; i < 3; i++){
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		if(i == 0){
			KeyReg2[i] = HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin);
		}
		else if(i == 1){
			KeyReg2[i] = HAL_GPIO_ReadPin(INC_GPIO_Port, INC_Pin);
		}
		else if(i == 2){
			KeyReg2[i] = HAL_GPIO_ReadPin(SET_GPIO_Port, SET_Pin);
		}
		if((KeyReg0[i] == KeyReg1[i]) && ( KeyReg1[i] == KeyReg2[i])){
			if(KeyReg3[i] != KeyReg2[i]){
				KeyReg3[i] = KeyReg2[i];
				if(KeyReg2[i] == PRESSED_STATE){
					subKeyProcess(i);
					TimerForKeyPress[i] = 300;
				}
			}
			else{
				//handle the long press behavior
				TimerForKeyPress[i]--;
				if(TimerForKeyPress[i] == 0){
					KeyReg3[i] = NORMAL_STATE;
				}
			}
		}
	}

}
