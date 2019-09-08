#include "stm32f4xx_hal.h"

void GPIO_config(void);
void ADC_config(void);
void Systick_Config(void);
void msDelay(uint32_t msTime);

ADC_HandleTypeDef myADCtypeDef; //defined globaly so we can use it in multiple functions

uint32_t myAdcValue;

int main(void){
	
	HAL_Init(); //remove HAL init
	GPIO_config();
	ADC_config();
	Systick_Config();
	
	while(1){
			
		//1.Start ADC
		ADC1->CR2 |= ADC_CR2_ADON; //Start ADC1
		ADC1->CR2 |= (1<<30);
		
		//Stabilize the ADC clock
		uint32_t counter = (ADC_STAB_DELAY_US*(SystemCoreClock/1000000U);
		while(counter != 0U)
		{
			counter--;
		}
		//Poll for end of conversion
		uint32_t tickstart = 0U;
		tickstart = HAL_GetTick(); //replace HAL_GetTick()
		while(ADC1->SR&0x2) !=0x2)
		{
				if( HAL_GetTick() - tickstart ) > 10 )
				{
					break;
				}
		}
		
		//Read ADC value
		myAdcValue = ADC1 -> DR;
		
		//Stop the ADC
		ADC1->CR2 &= ~ADC_CR2_ADON;
		
		//Clear all flags
		ADC1->SR = 0x00;
		
		//2. 100ms delay
		msDelay(100); 		//replace HAL_delay
		
		
		
	}

}

void GPIO_config(void){
	
	RCC->AHB1ENR |=0x01; // IO Port A clock Enable
	
	GPIOA->MODER |=0x03; // Set Analog Mode for PIN 0
	GPIOA->PUPDR &=~(0x00000003); // Set No Pull-up , No Pull-down for PIN 0
	
	
}

void ADC_config(void){
	
	RCC->APB2ENR |= (0x00000100); // Enable ADC1 Clock
	
	//ADC Basic Config
	
	ADC1->CR1 = (0x02<<24);		//Set the resolution to 8 bits + channel 0 
	ADC1->CR2 = (0x01<<10); 	//End of Conversion (EOC) flag at the end of regular channel conversion
	ADC1->SMPR2 = 1;					//Sample time of 15 clock cycles.
	ADC1->SQR1 = (0x0 << 20);	//Numer of conversion = 1
	ADC1->SQR3 = 0x00;				//Sequencier to conversion channel 0 first(it is the only one)
	
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
void msDelay(uint32_t msTime){
	
	for(uint32_t i=0; i<msTime*4000;i++);
}