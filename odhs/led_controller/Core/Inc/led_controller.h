/*
 * led_controller.h
 *
 *  Created on: Oct 12, 2026
 *      Author: priyanshu
 */

#ifndef INC_LED_CONTROLLER_H_
#define INC_LED_CONTROLLER_H_
#include <stdlib.h>
#include "stm32h7xx_hal.h"
struct LED_struct{
	int led_no;
	GPIO_TypeDef *port;
	uint16_t pin;
	GPIO_PinState status;
};

typedef  struct LED_struct LED;


struct LED_Handler{
	int max_size;
	int n;
	LED *leds;
};
void init(struct LED_Handler *Handler){
	Handler->n = -1;
	if(Handler->max_size <= 0){
		Handler->max_size = 3;
	}
	Handler->leds = calloc(Handler->max_size, sizeof(LED));
}
void addLED(struct LED_Handler *Handler, LED led){
	if(Handler->n +1 < Handler->max_size){
		led.led_no = Handler->n+1;
		(led.status) = GPIO_PIN_RESET;
		Handler->leds[++Handler->n] = led;
	}else{
		Handler->max_size *= 2;
		LED  *tmp = realloc(Handler->leds, Handler->max_size*sizeof(LED));
		if(tmp == NULL){
			exit (-2);
		}
		Handler->leds = tmp;
		addLED(Handler, led);
	}
}
LED createLED(GPIO_TypeDef *port, uint16_t pin){
	LED l = {0,port,pin,GPIO_PIN_RESET};
	return l;
}

void  setAll(struct LED_Handler *Handler){
	for(int i = 0; i <= Handler->n;i++){
		HAL_GPIO_WritePin(Handler->leds[i].port,Handler->leds[i].pin, GPIO_PIN_SET);
		(Handler->leds[i].status) = GPIO_PIN_SET;
	}
}
void  resetAll(struct LED_Handler *Handler){
	for(int i = 0; i <= Handler->n;i++){
		HAL_GPIO_WritePin(Handler->leds[i].port,Handler->leds[i].pin, GPIO_PIN_RESET);
		(Handler->leds[i].status) =GPIO_PIN_RESET;
	}
}
void  toggleAll(struct LED_Handler *Handler){
	for(int i = 0; i <= Handler->n;i++){
		HAL_GPIO_TogglePin(Handler->leds[i].port,Handler->leds[i].pin);
		(Handler->leds[i].status) = (Handler->leds[i].status) == GPIO_PIN_SET?GPIO_PIN_RESET:GPIO_PIN_SET;
	}
}


void  setI(struct LED_Handler *Handler, int i){
		HAL_GPIO_WritePin(Handler->leds[i].port,Handler->leds[i].pin, GPIO_PIN_SET);
		(Handler->leds[i].status) =GPIO_PIN_SET;
}
void  resetI(struct LED_Handler *Handler, int i){
		HAL_GPIO_WritePin(Handler->leds[i].port,Handler->leds[i].pin, GPIO_PIN_RESET);
		(Handler->leds[i].status) =GPIO_PIN_RESET;
}
void  toggleI(struct LED_Handler *Handler, int i){
		HAL_GPIO_TogglePin(Handler->leds[i].port,Handler->leds[i].pin);
		(Handler->leds[i].status) = (Handler->leds[i].status) == GPIO_PIN_SET?GPIO_PIN_RESET:GPIO_PIN_SET;
}


void clear(struct LED_Handler *Handler){
	free(Handler->leds);
	Handler = NULL;
}





#endif /* INC_LED_CONTROLLER_H_ */
