#ifndef arduino_digital_comm_h
#define arduino_digital_comm_h

#if defined(__AVR_ATmega2560__) // Arduino Mega 2560
#define OUTPUT_PIN 22
#elif defined(__AVR_ATmega328P__) // Arduino UNO R3
#define OUTPUT_PIN 2
#endif

void setBitDelay();
unsigned long getMinBitTime();

#endif
