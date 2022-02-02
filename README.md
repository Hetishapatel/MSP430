# MSP430 - UART 

The code is for UART communication between 2 MSP430 boards and is written in Embedded C
If the pin P2.5 is connected to Vcc then the board transmit and if it ground then the board works as receiver.

# Transmitter

Transmitter reads the potentiometer value and conver analog value to digital value using on board 10 bit ADC. 
It uses the digital value to blink the LED  connected to it and transmits same value using UART protocol.
As the digital value varies the brightness of the LED also varies.

# Receiver

Receiver reads the received byte and uses it to blink the LED connected to it. 

# Application 
The LEDs connected to different boards has same duty cycle.
Similar system can be set up on relative large scale to control the output connected to a system with the input connected to other system using simple ADc conversion and UART protocol 
