#include "stm32f4xx_hal.h"

void GPIO_config(void);
void ADC_config(void);
void Systick_Config(void);

ADC_HandleTypeDef myADCtypeDef; //defined globaly so we can use it in multiple functions

uint32_t myAdcValue;

int main(void){
	
	HAL_Init();
	GPIO_config();
	ADC_config();
	Systick_Config();
	
	while(1){
		
		//1.Read ADC value
		HAL_ADC_Start(&myADCtypeDef);
		if(HAL_ADC_PollForConversion(&myADCtypeDef,5) == HAL_OK){
			myAdcValue = HAL_ADC_GetValue(&myADCtypeDef);
		}
		HAL_ADC_Stop(&myADCtypeDef);
		//2. 100ms Delay
		
		HAL_Delay(100);
	}

}

void GPIO_config(void){

	__HAL_RCC_GPIOA_CLK_ENABLE(); //enable clock of port A
	
	GPIO_InitTypeDef myADCpin;
	myADCpin.Pin=GPIO_PIN_0;
	myADCpin.Mode=GPIO_MODE_ANALOG;
	myADCpin.Pull=GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOA,&myADCpin);
	
}

void ADC_config(void){

	__HAL_RCC_ADC1_CLK_ENABLE();
	
	myADCtypeDef.Instance = ADC1; 
	myADCtypeDef.Init.Resolution= ADC_RESOLUTION8b;
	myADCtypeDef.Init.EOCSelection= ADC_EOC_SINGLE_CONV;
	myADCtypeDef.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	
  HAL_ADC_Init(&myADCtypeDef);
	
	ADC_ChannelConfTypeDef myADCchannelTypeDef;
	myADCchannelTypeDef.Channel = ADC_CHANNEL_0;
	myADCchannelTypeDef.Rank = 1;
	myADCchannelTypeDef.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	
	
	HAL_ADC_ConfigChannel(&myADCtypeDef,&myADCchannelTypeDef);
		
}
void Systick_Config(void){
	
	//Set clock source and speed
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	
	//Systick interrupt priority and enable
	HAL_NVIC_SetPriority(SysTick_IRQn,0,0);
	HAL_NVIC_EnableIRQ(SysTick_IRQn);
	
}

void SysTick_Handler(void){

	HAL_IncTick();
}
