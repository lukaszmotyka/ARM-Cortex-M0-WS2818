#include "ws2818.h"
#define mask 0x80
#define LedOut 0

void LedInit(void){
	SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[3]=PORT_PCR_MUX(1UL);    //data out is PTD3
	FPTD->PDDR|=Mask[LedOut];
}
void SendReset(void){
	uint16_t nr_of_cycles;		
	FPTD->PCOR|=(1UL<<3);
	for(nr_of_cycles=200; nr_of_cycles>0; nr_of_cycles--){__nop();}
	FPTD->PSOR|=(1UL<<3);
}
void SendOne(void){
		FPTD->PSOR|=0x8;  
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		FPTD->PCOR|=0x8;		
}
void SendZero(void){
		FPTD->PSOR|=0x8;
		FPTD->PCOR|=0x8;
			__nop();
			__nop();
			__nop();
			__nop();
			__nop();
			__nop();
}	

void Display(uint8_t digit,uint8_t color[39][2]){   //function which display colors on 40 leds, color[x][0] - RED
	uint8_t nr_vec;                                   //                                          color[x][1] - GREEN
	uint8_t nr_byte;                                  //                                          color[x][2] - BLUE
	uint8_t nr_digits;
	for(nr_digits=0;nr_digits<=digit;nr_digits++){
		for(nr_vec=0;nr_vec<3;nr_vec++){
				for(nr_byte = 8; nr_byte>0; nr_byte--){
				if(mask & color[nr_digits][nr_vec]) SendOne();
				else SendZero();
			color[nr_digits][nr_vec]<<=1;
			}
		}
	}
		
}
