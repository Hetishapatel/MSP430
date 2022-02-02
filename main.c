/************************************************************************************************************
 * date of creation: 9/24/2021
 * Authors: Hetisha Patel and Parshva Gandhi
 * The code take potentiometer reading on one msp430 board give digital value and turn on led, it also passes the same dutycycle
 * value to second msp430 board using uart communication and turn on led connected to that board.
 * The code is robust for sender and receiver board
 */

#include "msp430g2553.h"
#include "common.h"
#include "pin_common.h"
#include "UART.h"
#include "DIN.h"
#include "DOUT.h"
void transmit(void);
void delay(unsigned int  t);
void adc_setup();
void uart_setup();


int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

        P2DIR &= 0xDF;         // P2.5 as input


        while(1)
            {
                 if(P2IN&0x20){        //p2.5 connected to vcc transmitter board
                     transmit();
                 }
                 receive();           // else p2.5 connected to GND receiver board
            }

	    return 0;
}

//DELAY FUNCTION
void delay(unsigned int time)          // Custom delay function
{
    unsigned int i;
    for(i = time; i > 0; i--)
        __delay_cycles(1);          // __delay_cycles accepts only constants !
}

// SETUP UART

void uart_setup(){
    uartPinInit();
    uartConfigureCR();          // setup uart
}

//SETUP ADC
void adc_setup(){                      // setup ADC
    P1SEL &=0XF7;
    ADC10AE = 0x08;
    ADC10CTL1 = INCH_3;
    ADC10CTL0 =ADC10SHT_3 + MSC + ADC10ON;
}

// TRANSMITTER BOARD
void transmit(void){                        // code for transmitter board
    adc_setup();                            // ADC setp

    uart_setup();
    P1DIR |= 0x20;                          // p1.5 as output
    while(1)
        {
            ADC10CTL0 |= ENC + ADC10SC;     // enable and start conversion
            int adc_value;
            adc_value = ADC10MEM;           // read converted value
            adc_value/=10;                  // calculate dutycycle
            uartTransmitChar(adc_value);    // transmit via uart


            unsigned int dutycycle;

               dutycycle= adc_value;

                P1OUT |= BIT5;                // LED ON
                delay(dutycycle);             // Delay for ON Time
                P1OUT &= ~BIT5;               // LED OFF
                delay(1023-dutycycle);        // OFF Time = Period - ON Time
          }
}

// RECEIVER BOARD
void receive(){                               // code for receiver board
    P1DIR |= 0x20;                            // p1.5 as output
    uart_setup();
    while(1){
    uint8_t data= uartReceiveChar();          // read received byte to data
    P1OUT |= BIT5;                            // LED ON
    delay(data);                              // Delay for ON Time
    P1OUT &= ~BIT5;                           // LED OFF
    delay(1023-data);
    }

}
