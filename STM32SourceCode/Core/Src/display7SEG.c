/*
 * display7SEG.c
 *
 *  Created on: Nov 5, 2022
 *      Author: tran
 */


#include "display7SEG.h"
#include "main.h"
#include "global.h"

const int MAX_LED = 5;
int index_led = 0;
int led_buffer[5] = {0,0,0,0,0};
//ex5
void updateClockBuffer(){
    led_buffer[0] = Horizontal_TrafficLight;
    led_buffer[1] = Vertial_TrafficLight;
    led_buffer[2] = ModeValue;
    switch(ModeValue){
    case 1:
    	led_buffer[3] = 0;
    	led_buffer[4] = 0;
    	break;
    case 2:
    	led_buffer[3] = RED_Time_value/10;
        led_buffer[4] = RED_Time_value%10;
       	break;
    case 3:
    	led_buffer[3] = YELLOW_Time_value/10;
        led_buffer[4] = YELLOW_Time_value%10;
       	break;
    case 4:
    	led_buffer[3] = GREEN_Time_value/10;
        led_buffer[4] = GREEN_Time_value%10;
       	break;
    default:
    	led_buffer[3] = 0;
        led_buffer[4] = 0;
       	break;
    }
}

void update7SEG(int index){
	switch(index){
	case 0:
		HAL_GPIO_WritePin ( EN1_GPIO_Port , EN1_Pin , GPIO_PIN_RESET ) ;
        HAL_GPIO_WritePin ( EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN4_GPIO_Port , EN4_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN5_GPIO_Port , EN5_Pin , GPIO_PIN_SET ) ;
		display7Seg(led_buffer[0]);
		break;
	case 1:
		HAL_GPIO_WritePin ( EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN2_GPIO_Port , EN2_Pin , GPIO_PIN_RESET ) ;
        HAL_GPIO_WritePin ( EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN4_GPIO_Port , EN4_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN5_GPIO_Port , EN5_Pin , GPIO_PIN_SET ) ;
		display7Seg(led_buffer[1]);
		break;
	case 2:
		HAL_GPIO_WritePin ( EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN3_GPIO_Port , EN3_Pin , GPIO_PIN_RESET ) ;
        HAL_GPIO_WritePin ( EN4_GPIO_Port , EN4_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN5_GPIO_Port , EN5_Pin , GPIO_PIN_SET ) ;
		display7Seg(led_buffer[2]);
		break;
	case 3:
		HAL_GPIO_WritePin ( EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN4_GPIO_Port , EN4_Pin , GPIO_PIN_RESET ) ;
        HAL_GPIO_WritePin ( EN5_GPIO_Port , EN5_Pin , GPIO_PIN_SET ) ;
		display7Seg(led_buffer[3]);
		break;
	case 4:
		HAL_GPIO_WritePin ( EN1_GPIO_Port , EN1_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN2_GPIO_Port , EN2_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN3_GPIO_Port , EN3_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN4_GPIO_Port , EN4_Pin , GPIO_PIN_SET ) ;
        HAL_GPIO_WritePin ( EN5_GPIO_Port , EN5_Pin , GPIO_PIN_RESET ) ;
		display7Seg(led_buffer[4]);
		break;
	default:
		break;
	}
}


void display7Seg(int num){
	switch(num){
	case 0:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_SET ) ;
		break;
	case 1:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_SET ) ;
		break;
	case 2:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_RESET ) ;
		break;
	case 3:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_RESET ) ;
		break;
	case 4:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_RESET ) ;
		break;
	case 5:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_RESET ) ;
		break;
	case 6:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_RESET ) ;
		break;
	case 7:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_SET ) ;
		break;
	case 8:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_RESET ) ;
		break;
	case 9:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_SET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_RESET ) ;
		break;
	default:
		HAL_GPIO_WritePin ( A_GPIO_Port , A_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( B_GPIO_Port , B_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( C_GPIO_Port , C_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( D_GPIO_Port , D_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( E_GPIO_Port , E_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( F_GPIO_Port , F_Pin , GPIO_PIN_RESET ) ;
		HAL_GPIO_WritePin ( G_GPIO_Port , G_Pin , GPIO_PIN_RESET ) ;

	}
}
