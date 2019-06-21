// File:    	MovingAvgFilter.c
//
// Processor:   	PIC32MX79F512L
// Board:   	Max32
// Compiler:    	XC32
// IDE:     	MPLAB-X
// Date:    	January 22, 2017
// Status:      	in development: correct in initial tests
//      	
// Description:
// Moving Average Filter
// Timer 2 generates interrupts at 15625 i.e. every 64 us
// The ISR reads a sample from the ADC, performs a moving average, and
//          	writes the result to the 12-bit SPI DAC
//    	Port B bit 2 is set as digital output to time execution of filter
// Illustrates how to
// 1. set oscillator
// 2. use SPI port and MCP 4822 12-bit DAC
// 3. use timer
// 4. use interrupts
//  	5. use on-chip 10-bit ADC
//  	6. perform a moving average filter algorithm
//  	7. time execution of filter algorithm using output bit and oscilloscope
//
//
// Reference: Chapter 15 of Smith textbook
//
//----------------------------------------------------------------------
// INCLUDES
//----------------------------------------------------------------------
#include <xc.h>
#include <stdio.h>
#include <plib.h>
#include <inttypes.h>
#include <math.h>
#include "ADC.h"
#include "BASICSHIELD.h"
#include "SPI.h"
#include "SYS.h"
#include <dsplib_dsp.h>
#include <fftc.h>
#define FILTER_SIZE 11
#define min_change 200
#define fftc fft16c16 // Number of points in the moving average filter
#define T   (0.000064)  // Sample interval in seconds
#define Fs  (1/T)   	// Sample frequency
// For blinking LED
#define HALF_SECOND (0.5/T)  // 0.5 seconds / T = counts to reach 1/2 second
#define log2N          	4
#define N           	( 1 << log2N )
int16c Time[N], Freq[N], scratch[N], Filter[N], Tout[N];

float FilterCoeffFloat = 1.0/FILTER_SIZE;
/*float ynFloat;
int Xoldest = 0;
int Xnewest = FILTER_SIZE - 1;
*/
 unsigned int count = 0;  // Used to blink the LED on Port A bit 3 of the MAX32
 
// -----------------------------------------------------------
// build_filter_kernel
// -----------------------------------------------------------
void build_filter_kernel(void)
{
	//int i = 32767;
	int j = 0;
	int filter_size = 3;
	//for ( ; j < 16 ; ++j , i -= (32767 >> 4))
	//{
  	//  Filter[j].re = i;
    	//Filter[j].im = 0;
	//}
	for( ; j < filter_size; ++j )
	{
    	Filter[j].re = 0;
	}
	for ( ; j < (N - filter_size + 1); ++j )
	{
    	Filter[j].re = 1;
	}
	for ( ; j < N; ++j )
	{
    	Filter[j].re = 0;
	}
}
// -----------------------------------------------------------
// multiply_ffts
// -----------------------------------------------------------
void multiply_ffts(void)
{
	int i = 0;
	for( ; i < N; ++i )
	{
    	Freq[i].re *= Filter[i].re;
    	Freq[i].im *= Filter[i].re;
	}
}
// -----------------------------------------------------------
// inverse_fft
// -----------------------------------------------------------
void inverse_fft(void)
{
	int i = 0;
	for ( ; i < N; ++i )
	{
    	Freq[i].im *= -1;
	}
	mips_fft16( Tout, Freq, fftc, scratch, log2N );
	for( i = 0; i < N; ++i )
	{
    	if( Tout[i].im < 0 )
    	{
        	Tout[i].im *= -1;
    	}
	}
	for ( i = 0; i < N; ++i )
	{
    	Tout[i].re = Tout[i].re << ( log2N >> 4 );
    	Tout[i].im = Tout[i].im << ( log2N >> 4 );
	}
	Nop();
}
// -----------------------------------------------------------
// Timer2initialize
// -----------------------------------------------------------
// Set for interrupt rate of 15625 Hz
void Timer2initialize(void) {	
	
T2CON = 0x8070; // 80 MHz = 12.5 ns per clock.  Prescale = divide by 256  
// 256 clocks per count * 12.5 ns per clock = 3.2 us per count	
PR2 = 19; // interrupt after 20 counts = 64 us
}
// -----------------------------------------------------------
// PortsInitialize
// -----------------------------------------------------------
/*void PortsInitialize(void) {	
	//_TRISB2 = 0;      	// set GPIO bit 2 of port B as output:  used to time filter execution	
	TRISBCLR = 0x04;    	// Two ways to do the same thing	
	//_TRISA3 = 0;      	// LED connected to Port A bit 3 (pin 13 of MAX32)	
	TRISACLR = 0x08;    	// Two ways to do the same thing
}*/
// -----------------------------------------------------------
// InterruptInitialize
// -----------------------------------------------------------
// Initializes Timer2 interrupt
void InterruptInitialize(void) {	
	mT2SetIntPriority(1);	
	INTEnableSystemMultiVectoredInt();	
	mT2IntEnable(1);
}
// -----------------------------------------------------------
// SystemInitialize
// -----------------------------------------------------------
void SystemInitialize(void) {	
	SysInitialize();	
	PortsInitialize();	
	SPI2initialize();	
	Timer2initialize();	
	InterruptInitialize();	
	//initU1(); // UART	
	initADC(0xfffc); // Argument determines which Port B bits are analog input (0) and which are digital (1)
	// MAX32 pin A0 (Port B bit 0), pin A1 (B1) are analog rest (B2-15) are digital
}
// -----------------------------------------------------------
// Global Variables
// -----------------------------------------------------------
//float xFloat[FILTER_SIZE + 1];

// -----------------------------------------------------------
// Update Sample Array
// Operates on global variable array and indices Xnewest and Xoldest
// -----------------------------------------------------------
/*void UpdateSampleArray() {	
	Xnewest++;	
	if (Xnewest > FILTER_SIZE) Xnewest = 0;	
	Xoldest++;	
	if (Xoldest > FILTER_SIZE) Xoldest = 0;
}
int i = 0;
*/
// -----------------------------------------------------------
//  Perform Moving Average Filter
//  Performed at a rate of Fs i.e. every T seconds (64 us in this case)
//  Reads analog sample from ADC, computes moving average, outputs to DAC
// -----------------------------------------------------------
/*void AnalogSampleFloatNew(void) {
   // i = readADC(1);
	static int j = 0;
	UpdateSampleArray(); // Update samples
	
   // for( int j = 0; j < N; ++j )
	//{
    	xTime.re[j] = readADC(1) << 5;
    	xTime.im[j] = 0;
	//}
	mips_fft16( xFreq, xTime, fftc, scratch, log2N );
	//xFloat[Xnewest] = ((float) i) / 1024.0; // Normalized
	
	// Perform filtering	
	//SumFloat = SumFloat + xFloat[Xnewest] - xFloat[Xoldest];	
	//ynFloat = SumFloat*FilterCoeffFloat;	
	//i = (int) (ynFloat * 4096.0);  	// 12 bits to send to DAC    	
	++j;
	if ( j == N )
	{
    	j = 0;
	}
	// DAC	
   //////////////////////////// writeDAC_SPI2(i, 0, 0, 1);      	//writeDAC_SPI2(val, channel, gain, shutdown)  
}*/
// -----------------------------------------------------------
// AnalogOutput
// -----------------------------------------------------------
/*void AnalogOutput(void)
{
	writeDAC_SPI2(xTime.re[i], 0, 0, 1);
}*/
// -----------------------------------------------------------
// T2InterruptHandler
// -----------------------------------------------------------
void __ISR(_TIMER_2_VECTOR, ipl1) T2InterruptHandler(void) {	
	// T2 handler code here               	// used by background cod in main to blink an LED	
	_RB2 = 1;           	// Set Port B bit 2 high to start timing output	
	//PORTBSET = 0x04;  	// alternate method	
	// Read ADC, to filter, output to DAC	
	Time[N/2].re = readADC(1) << 5;
	
	mips_fft16( Freq, Time, fftc, scratch, log2N );
	multiply_ffts();
	inverse_fft();
  
	writeDAC_SPI2( Tout[N/2].re, 0, 0, 1 );
	for( count = 0; count < N/2; ++count )
	{
    	Time[count] = Time[count + 1];
	}
	
	//AnalogSampleFloatNew();	// 
	//AnalogOutput();
	_RB2 = 0;           	// Clear Port B bit 2 to stop timing output 	
	//PORTBCLR = 0x004; 	// Alternate method	
	// clear the flag and exit	
	mT2ClearIntFlag();
} // T2 Interrupt Handler
// -----------------------------------------------------------
// main
// -----------------------------------------------------------
main() {	
  
 
	SystemInitialize();
	build_filter_kernel();
	//for(; i < N; ++i )
	//{
  	//  Time[i].re = 0;
    	//Time[i].im = 0;
	//}
	while (1) // This loop run except when the timer interrupt occurs	
	{ // As long as the LEDS change you know the interrupts are occurring    	
    	if (count > HALF_SECOND) {
       	count = 0;        	
       	PORTAINV = 0x08;  // Invert Port A bit 3 to blink LED    	
    	}
    	
    	// Uncomment and don't initialize interrupts to test ADC and DAC    	
    	//i = readADC(1);    	
    	//writeDAC_SPI2(i, 0, 0, 1);    	
    	//printf("%d ", i);  
	}
} // main

