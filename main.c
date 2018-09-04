#include "init.h"
#include "converter.h"
#include "seg_lib.h"

int main()
{
		__disable_irq();
		//initialize digit
		digit = malloc(8*sizeof(int));
		
		//initialize the peripherals
		hardware_init();
		ADC0_init();
		PIT0_init();
		PIT1_init();
		PIT2_init();
		DAC0_init();
		buttons_init();
		segment_init();
		if(LED_Initialize()){return 0;}
	
		//set prioities for all our interrupts
		NVIC_SetPriority(PORTC_IRQn, 4U);
		NVIC_SetPriority(ADC0_IRQn,-3U);
		NVIC_SetPriority(PIT0_IRQn,-2U);
		NVIC_SetPriority(PIT1_IRQn,4U);
		NVIC_SetPriority(PIT2_IRQn,4U);
		
		//set local variables
		uint8_t msg;
		int start = 0;
		int temp[4]; //stores the digits to display in an array
		debug_printf("Press 1 to start project\r\n");
		
		while (!start){
					msg = GETCHAR(); //wait for user to start program
					if (msg == '1'){
						start = 1;
					}
		}
		__enable_irq();
		PIT_StartTimer(PIT,PIT0);
		PIT_StartTimer(PIT,PIT1);
		PIT_StartTimer(PIT,PIT2);
		for(int j=0;j<DEFAULT_SYSTEM_CLOCK;j++){}; //Busy waits for initialization and all values to be set
		while(1){
			temp[3] = avg%10;
			temp[2] = avg/10;
			temp[1] = fanBoundary%10;
			temp[0] = fanBoundary/10;
			for (int i=0;i<=3;i++){
				digit[0]=i+1;
				switch(temp[i]){
					case 0:
						setZero();
						break;
					case 1:
						setOne();
						break;
					case 2:
						setTwo();
						break;
					case 3:
						setThree();
						break;
					case 4:
						setFour();
						break;
					case 5:
						setFive();
						break;
					case 6:
						setSix();
						break;
					case 7:
						setSeven();
						break;
					case 8:
						setEight();
						break;
					case 9:
						setNine();
						break;
					default:
						PRINTF("Digit out of bounds");
				}
				for(int i=0;i<20202;i++){}
				set_display();
			}
		}
		free(digit); //for completion
		return 0;
}






