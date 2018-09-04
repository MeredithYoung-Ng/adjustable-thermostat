#include "init.h"

adc16_config_t adc0_config;
adc16_channel_config_t adc0_channel;
pit_config_t pit0_config;
dac_config_t dac0_config;	
volatile int value; //raw value from 1 sample
volatile int prevPrevAvg = -1; 
volatile int prevAvg = -1;
volatile int avg = -1; //average temperature
volatile int stable = 1; 
volatile int debouncer = 1; //for sw3
volatile int fanBoundary = 75; 
volatile int pushStatesw2 = 0;
volatile int pushedsw2 = 0;


void ADC0_init(void)
{
			ADC16_GetDefaultConfig(&adc0_config);
				
			adc0_config.resolution = kADC16_ResolutionDF16Bit;
			ADC16_Init(ADC0, &adc0_config);
			ADC16_EnableHardwareTrigger(ADC0, false); /* Make sure the software trigger is used. */
			if (kStatus_Success == ADC16_DoAutoCalibration(ADC0))
			{
					PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
			}else{
					PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
			}
			adc0_channel.channelNumber = ADC0_channel;
			adc0_channel.enableInterruptOnConversionCompleted = true;
			adc0_channel.enableDifferentialConversion = false;
}

void buttons_init(void)
{
			NVIC_EnableIRQ(PORTC_IRQn);
			SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
			PORTC->PCR[6] |= PORT_PCR_MUX(001);
			PORTC->PCR[6] |= 3; //Pull up resistor
			PORTC->PCR[6] |= (10)<<16; 
			PORTC->PCR[6] |= (0)<<24;
	
			PORTA->PCR[4] |= PORT_PCR_MUX(001); 
			PORTA->PCR[4] |= 3;
			PORTA->PCR[4] |= (10)<<16;
			PORTA->PCR[4] |= (0)<<24;
	
			PTA->PDDR = 0;
			PTC->PDDR = 0;
}

void DAC0_init(void)
{
			DAC_GetDefaultConfig(&dac0_config);
			DAC_Init(DAC0, &dac0_config);
			DAC_Enable(DAC0,true);
			DAC0_set_value(0);
}


void DAC0_set_value(uint16_t value)
{
			DAC0->DAT[0].DATL = (uint8_t)(0xFFU & value); //bits 11-8
			DAC0->DAT[0].DATH = (uint8_t)((0xF00U & value)>>8); //bits 7-0
}


void PIT0_init(void)
{
			pit0_config.enableRunInDebug=true;
			PIT_Init(PIT,&pit0_config);
			PIT->MCR = 0x00;
			PIT_SetTimerPeriod(PIT, PIT0, DEFAULT_SYSTEM_CLOCK*2);
			PIT_EnableInterrupts(PIT, PIT0, kPIT_TimerInterruptEnable);	
			PIT_ClearStatusFlags(PIT,PIT0,kPIT_TimerFlag);
			EnableIRQ(PIT0_IRQn);	
}

void PIT1_init(void)
{
			pit0_config.enableRunInDebug=true;
			PIT_Init(PIT,&pit0_config);
			PIT->MCR = 0x00;
			PIT_SetTimerPeriod(PIT, PIT1, DEFAULT_SYSTEM_CLOCK);
			PIT_EnableInterrupts(PIT, PIT1, kPIT_TimerInterruptEnable);	
			PIT_ClearStatusFlags(PIT,PIT1,kPIT_TimerFlag);
			EnableIRQ(PIT1_IRQn);
			debouncer = 1;
}

void PIT2_init(void)
{
			pit0_config.enableRunInDebug=true;
			PIT_Init(PIT,&pit0_config);
			PIT->MCR = 0x00;
			PIT_SetTimerPeriod(PIT, PIT2, DEFAULT_SYSTEM_CLOCK/4 );
			PIT_EnableInterrupts(PIT, PIT2, kPIT_TimerInterruptEnable);	
			PIT_ClearStatusFlags(PIT,PIT2,kPIT_TimerFlag);
			EnableIRQ(PIT2_IRQn);
			pushStatesw2 = 0;
			pushedsw2=0;
}


void segment_init(void)
{
			NVIC_EnableIRQ(PORTB_IRQn);
			SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 
			SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
			PORTB->PCR[2] |= PORT_PCR_MUX(001);
			PORTB->PCR[3] |= PORT_PCR_MUX(001);
			PORTB->PCR[10] |= PORT_PCR_MUX(001);
			PORTB->PCR[11] |= PORT_PCR_MUX(001);
			PORTB->PCR[20] |= PORT_PCR_MUX(001);
			PORTB->PCR[19] |= PORT_PCR_MUX(001);
			PORTB->PCR[18] |= PORT_PCR_MUX(001);
		
			PTB->PDDR |= (1<<19);	//D1
			PTB->PDDR |= (1<<2);  //D2
			PTB->PDDR |= (1<<10);	//D3
			PTB->PDDR |= (1<<11);	//D4
			PTB->PDDR |= (1<<20);	//D5
			PTB->PDDR |= (1<<18);	//D6
			PTB->PDDR |= (1<<3);	//D7
	
			PTB->PSOR |= (1<<19);
			PTB->PSOR |= (1<<2);
			PTB->PSOR |= (1<<10);
			PTB->PSOR |= (1<<11);
			PTB->PSOR |= (1<<20);
			PTB->PSOR |= (1<<18);
			PTB->PSOR |= (1<<3);
	
	
	//Toggleing for port D
	PORTD->PCR[0] |= PORT_PCR_MUX(001); //Segment 8 - 3
	PTD->PDDR |= (1<<0);
	PORTD->PCR[1] |= PORT_PCR_MUX(001); //Segment 12 - 1
	PTD->PDDR |= (1<<1);
	PORTD->PCR[2] |= PORT_PCR_MUX(001); //Segment 9 - 2
	PTD->PDDR |= (1<<2);
	PORTD->PCR[3] |= PORT_PCR_MUX(001); //Segment 6 - 4
	PTD->PDDR |= (1<<3);
}


void ADC0_IRQHandler(void)
{
  /* Update value with read conversion result to clear the conversion completed flag. */
	value = ADC16_GetChannelConversionValue(ADC0,ADC0_channelgroup);
}


void PORTC_IRQHandler(void){	
			PORTC->PCR[6] |= PORT_PCR_ISF(1);
}

void NMI_Handler(void){
			if(debouncer){
				fanBoundary--;
				if(fanBoundary<0) fanBoundary=0;	
				debouncer = 0;
			}
			MCM->ISCR = MCM_ISCR_NMI(0);
}


void PIT0_IRQHandler(void)
	{
	if (stable != 0) {
		if (avg != -1) {
			// Set [prevPrevAvg] and [prevAvg]
			prevPrevAvg = prevAvg;
			prevAvg = avg;	
		}	
	}
		
	// Array for ADC output readings
	int * values = malloc(10 * sizeof(int));
	
	for(int i = 0; i<10;i++){
		ADC16_SetChannelConfig(ADC0, ADC0_channelgroup, &adc0_channel); 
		EnableIRQ(ADC0_IRQn);
		while(ADC16_GetStatusFlags(ADC0));
		DisableIRQ(ADC0_IRQn);
		// Save ADC output value into array
		values[i] = value;
	}
	// Find average of [values] with min and max elements removed
	int rawAvg = removeMinMax(values, 10);
	
	// Convert [rawAvg] to Fahrenheit
	avg = raw_to_temp(rawAvg);
	
	if ((prevAvg == -1) && (prevPrevAvg == -1)) {
		prevAvg = avg;
		prevPrevAvg = avg;
	}
	
	// Stabilize for cases where previous and previous previous averages are in different ranges
	if ((stable == 1) && (((avg - prevAvg) > 10) || ((avg - prevAvg) < 10)) && (((avg - prevPrevAvg) > 10) || ((avg - prevPrevAvg) < 10))) {
		avg = prevAvg;
		prevAvg = avg;
		prevPrevAvg = prevAvg;
		stable = 0;
	} else if (stable == 0) {
		// Reset stable
		stable = 1;
	}

	//debug_printf("ADC raw output average: %llu\r\n",rawAvg);
	//debug_printf("ADC temp output average: %llu\r\n",avg);
		
	if(avg<fanBoundary){ //MATH: Vin/3.3V*4096
			DAC0_set_value(0U); //0v
		}else if (avg>=fanBoundary && avg < (fanBoundary+5)){
			DAC0_set_value(868U); //0.7v
		}	else if (avg>=(fanBoundary+5) && avg <(fanBoundary+10)){
			DAC0_set_value(992U); //0.8v
		}	else if (avg>=(fanBoundary+10) && avg <(fanBoundary+15)){
			DAC0_set_value(1117U); //0.9v
		}	else{
			DAC0_set_value(1242U); //1.0v
		}			
	PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF(1);
	free(values);
}

void PIT1_IRQHandler(void)
{
	
	debouncer = 1;
	PIT->CHANNEL[1].TFLG = PIT_TFLG_TIF(1);
}

void PIT2_IRQHandler(void)
{
		pushedsw2 = !(PTC->PDIR&0x40);
			switch(pushStatesw2){ //checking for all the possible states
				case NoPush:
					 if (pushedsw2) pushStatesw2=MaybePush;
						else pushStatesw2=NoPush;
          break;

				 case MaybePush:
						if (pushedsw2) {
							 pushStatesw2=Pushed;   
							 fanBoundary++;		
						}
						else pushStatesw2=NoPush;
						break;

				 case Pushed:  
						if (pushedsw2) pushStatesw2=Pushed; 
						else pushStatesw2=MaybeNoPush;    
						break;

				 case MaybeNoPush:
						if (pushedsw2) pushStatesw2=Pushed; 
						else pushStatesw2=NoPush;    
						break;
			}
			if(fanBoundary>=100) fanBoundary=99;
			PIT->CHANNEL[2].TFLG = PIT_TFLG_TIF(1);
}
