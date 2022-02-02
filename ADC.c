/*
 * ADC.c
 *
 *  Created on: Sep 22, 2021
 *      Author: hpate108
 */
#include "common.h"
#include "msp430g2553.h"

     //P1SEL &= 0XFE;                               //setup P1.0 for analog input
void ADC_setup(void){
    pinClearSEL(1,3);
    ADC10CTL0 = ADC10SHT_3 + MSC + ADC10ON;      // set multiple sampling and turn on ADC
    ADC10CTL1 = INCH_0;
}



