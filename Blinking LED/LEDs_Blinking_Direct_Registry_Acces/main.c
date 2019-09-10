#include "stm32f4xx.h"             


void configureLEDPins(void);
void msDelay(uint32_t msTime);

int main(void){
	//Configure LEDS pins as Digital Output (PIN_D_12 to 15)
	configureLEDPins();
	//Define a delay function
	
	while(1)
	{
		GPIOD->ODR ^=(0xFUL<<12);
		msDelay(1000); // 1 sec
	}
	
}

void configureLEDPins(void){
	RCC->AHB1ENR |=(1<<3);
	//Set mode as output for GPIOD Pins 12-15
	GPIOD->MODER &=~(0xFFu<<12*2);
	GPIOD->MODER |=(0x55u<<12*2);

}

void msDelay(uint32_t msTime){
	
	for(uint32_t i=0; i<msTime*4000;i++);
}
