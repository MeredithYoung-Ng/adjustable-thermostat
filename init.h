#ifndef _INIT_H_
#define _INIT_H_

#include "fsl_debug_console.h"
#include "board.h"
#include "board_LED.h"
#include "fsl_adc16.h"
#include "fsl_pit.h"
#include "fsl_dac.h"
#include "converter.h"
#include "seg_lib.h"

#define ADC0_channelgroup 0U
#define ADC0_channel 1U
#define PIT0 kPIT_Chnl_0
#define PIT1 kPIT_Chnl_1
#define PIT2 kPIT_Chnl_2

#define NoPush 0U
#define MaybePush 1U
#define Pushed 3U
#define MaybeNoPush 4U


extern adc16_config_t adc0_config;
extern adc16_channel_config_t adc0_channel;
extern pit_config_t pit0_config;
extern dac_config_t dac0_config;
extern volatile int value;
extern volatile int avg;
extern volatile int debouncer;
extern volatile int fanBoundary;
extern volatile int pushStatesw2;
extern volatile int pushedsw2;


void ADC0_IRQHandler(void);

void PIT0_IRQHandler(void);

void PIT1_IRQHandler(void);

void PIT2_IRQHandler(void);

void PORTC_IRQHandler(void);

void NMI_Handler(void);

void PIT0_init(void);

void PIT1_init(void);
	
void PIT2_init(void);	
	
void ADC0_init(void);

void DAC0_init(void);

void buttons_init(void);

void segment_init(void);

void DAC0_set_value(uint16_t value);



#endif /* _INIT_H_ */

