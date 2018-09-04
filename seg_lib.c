#include "seg_lib.h" 

int *digit; //contains the mappings to the segments in order to display a digit
//digit[0] is what digit to write to
unsigned int segments[8] = {0,19,2,10,11,20,18,3}; //GPIO pins used for project

void set_display(){
	if (!digit[0]){ //check for reset
		resetDigit();
	}
	switch(digit[0]){
		case 1:
			PTD->PCOR = (1<<1);
			PTD->PSOR = (1<<0);
			PTD->PSOR = (1<<2);
			PTD->PSOR = (1<<3);
			break;
		case 2:
			PTD->PCOR = (1<<2);
			PTD->PSOR = (1<<0);
			PTD->PSOR = (1<<1);
			PTD->PSOR = (1<<3);
			break;
		case 3:
			PTD->PCOR = (1<<0);
			PTD->PSOR = (1<<1);
			PTD->PSOR = (1<<2);
			PTD->PSOR = (1<<3);
			break;
		case 4:
			PTD->PCOR = (1<<3);
			PTD->PSOR = (1<<0);
			PTD->PSOR = (1<<1);
			PTD->PSOR = (1<<2);
			break;
		default:
			PRINTF("invalid digit");
	}
	for (int k=1;k<8;k++){
		PTB->PCOR |= (1<<segments[k]);
	}
	for (int i=1;i<8;i++){
		if(digit[i]){
			PTB->PSOR |= (1<<segments[i]);
		}
		else{
			PTB->PCOR |= (1<<segments[i]);
		}
	}
}

void resetDigit(){
	digit[0] = 0;
	digit[1] = 0;
	digit[2] = 0;
	digit[3] = 0;
	digit[4] = 0;
	digit[5] = 0;
	digit[6] = 0;
	digit[7] = 0;
}

void setZero(){
	digit[1] = 1;
	digit[2] = 1;
	digit[3] = 1;
	digit[4] = 1;
	digit[5] = 1;
	digit[6] = 1;
	digit[7] = 0;
}

void setOne(){
	digit[1] = 0;
	digit[2] = 1;
	digit[3] = 1;
	digit[4] = 0;
	digit[5] = 0;
	digit[6] = 0;
	digit[7] = 0;
}

void setTwo(){
	digit[1] = 1;
	digit[2] = 1;
	digit[3] = 0;
	digit[4] = 1;
	digit[5] = 1;
	digit[6] = 0;
	digit[7] = 1;
}

void setThree(){
	digit[1] = 1;
	digit[2] = 1;
	digit[3] = 1;
	digit[4] = 1;
	digit[5] = 0;
	digit[6] = 0;
	digit[7] = 1;
}

void setFour(){
	digit[1] = 0;
	digit[2] = 1;
	digit[3] = 1;
	digit[4] = 0;
	digit[5] = 0;
	digit[6] = 1;
	digit[7] = 1;
}

void setFive(){
	digit[1] = 1;
	digit[2] = 0;
	digit[3] = 1;
	digit[4] = 1;
	digit[5] = 0;
	digit[6] = 1;
	digit[7] = 1;
}

void setSix(){
	digit[1] = 1;
	digit[2] = 0;
	digit[3] = 1;
	digit[4] = 1;
	digit[5] = 1;
	digit[6] = 1;
	digit[7] = 1;
}

void setSeven(){
	digit[1] = 1;
	digit[2] = 1;
	digit[3] = 1;
	digit[4] = 0;
	digit[5] = 0;
	digit[6] = 0;
	digit[7] = 0;
}

void setEight(){
	digit[1] = 1;
	digit[2] = 1;
	digit[3] = 1;
	digit[4] = 1;
	digit[5] = 1;
	digit[6] = 1;
	digit[7] = 1;
}

void setNine(){
	digit[1] = 1;
	digit[2] = 1;
	digit[3] = 1;
	digit[4] = 1;
	digit[5] = 0;
	digit[6] = 1;
	digit[7] = 1;
}

