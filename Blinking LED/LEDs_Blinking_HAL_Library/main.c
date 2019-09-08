#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common


void configureLEDPins(void);
void msDelay(uint32_t msTime);

int main(void){
	//Configure LEDS pins as Digital Output (PIN_D_12 to 15)
	configureLEDPins();
	//Define a delay function
	
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
		msDelay(1000); // 1 sec
	}
	
}

void configureLEDPins(void){
	
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_InitTypeDef myLEDConfig; //Struct used for Pin configuration and initialization
	myLEDConfig.Mode = GPIO_MODE_OUTPUT_PP; //set as output
	myLEDConfig.Pin=GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15; // which pins will be set
	
	
	HAL_GPIO_Init(GPIOD,&myLEDConfig); //initializations functions of the config above

}

void msDelay(uint32_t msTime){
	
	for(uint32_t i=0; i<msTime*4000;i++);
}
