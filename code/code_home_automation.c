#include<reg52.h> 
#include<stdio.h>
sbit b=P0^0; #sbit datatype allows you to access a specific pin within a port. Any changes to b or c will be reflected in the respective pins 0 and 1 of Port 0 that will change the state of the relays 1 and 2 respectively.
sbit c=P0^1;
unsigned int a; # used to store the value of the bits in the serial buffer register.
void receive()
{
	TMOD=0X20; // Timer mode to 8 bit auto reload mode
	TH1=0XFD; // Set baud rate in the timer register of timer1 =9600.   
	SCON=0X50; // Set 8bit UART mode
	TR1=1; // Enable timer 1 
	while(RI==0); // Wait for the receive interrupt to become 1
	a=SBUF; //Value from serial buffer (SBUF) stored in variable a 
	RI=0; //Clear receive interrupt flag for the next cycle
}	
void main()
{
	P0=0X00; // Initialize the pins of port 0 to 0, so all the relays are not working now
	while(1) //infinte loop we need it to run continually
	{
		receive(); //call the receive function. So the variable a is storing the value of the bits in the SBUF register. The bluetooth app transmits ASCII values of a, A , b B based on which option you select and you are switching on or switching off a device.
		if(a=='a') 
		{
			b=0; // Relay 1 is off
		}
		if(a=='A')
		{
			b=1; // Relay 1 is on
		}
		if(a=='b')
		{
			c=0; //  Relay 2 is off
		}
		if(a=='B')
		{
			c=1; // Relay 2 is on
		}
	}
}	