#ifndef pin_comm_h
#define pin_comm_h

#ifndef OUTPUT_PIN

#if defined(__AVR_ATmega2560__) // Arduino Mega 2560
#define OUTPUT_PIN 22
#elif defined(__AVR_ATmega328P__) // Arduino UNO R3
#define OUTPUT_PIN 2
#endif

#endif

#define DATA_BIT_SIZE 10u // Used as an 'unsigned char'

// Factor used to adjust the delay time to the imprecision of the Arduino functions delayMicroseconds() and delay()
#define DELAY_CORRECTION_FACTOR 5u
// The best factors for different bit rates are:
// 12u -> 1 kbps (T = 1000 us)
//  5u -> 2 kbps (T =  500 us)
//  2u -> 4 kbps (T =  250 us)
//  1u -> 8 kbps (T =  125 us)

// All bit times are in microseconds
unsigned long minimumBitTime = 0u;
unsigned long desiredBitTime = 500u; // Rate = 2 kbps

unsigned int microBitDelay = 0u;
unsigned int milliBitDelay = 0u;

#endif
