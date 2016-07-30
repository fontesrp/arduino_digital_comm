#include "pin_comm.h"

void send10b(unsigned int data) {

	unsigned char i;
	unsigned int converter = 1u;
	char pinState;

	// noInterrupts();

	for (i = 0u; i < DATA_BIT_SIZE; i++) {
		pinState  = ((data & converter) == 0u ? LOW : HIGH);
		converter = converter << 1;
		digitalWrite(OUTPUT_PIN, pinState);
		delayMicroseconds(microBitDelay);
		delay(milliBitDelay);
	}

	// interrupts();
}

unsigned int receive10b(unsigned char pinNumber) {

	unsigned char i;
	unsigned int data = 0u;
	char pinState;

	// noInterrupts();

	for (i = 0u; i < DATA_BIT_SIZE; i++) {
		pinState = digitalRead(pinNumber);
		data = (data << 1) | (pinState == LOW ? 0u : 1u);
		delayMicroseconds(microBitDelay);
		delay(milliBitDelay);
	}

	// interrupts();

	return data;
}

unsigned int generateAlternatingBitData(unsigned char bitQtt) {

	// For bitQtt = 10, should return the 10-bit integer 682 = 0x2AA = 0010 1010 1010

	unsigned int data = 0u;

	for (; bitQtt; bitQtt--) {
		data = (data << 1) | ((bitQtt + 1u) % 2u); // Set all odd bits to 1
	}

	return data;
}

unsigned long getMinBitTime() {

	// On both Arduino UNO R3 and Arduino Mega 2560, the maximum bit rate is about 277,777 bps (time ~= 36 us, for 10 bits)

	unsigned long time;
	unsigned int data;

	data = generateAlternatingBitData(DATA_BIT_SIZE);

	time = micros();
	send10b(data);
	time = micros() - time;

	return time / DATA_BIT_SIZE;
}

void setBitDelay() {

	microBitDelay = 0u;
	milliBitDelay = 0u;

	if (!minimumBitTime) {
		minimumBitTime = getMinBitTime();
	}

	microBitDelay = desiredBitTime - minimumBitTime - DELAY_CORRECTION_FACTOR; // Everything in microseconds

	// Arduino's documentation warns that, for values greater than 16,383, the function delayMicroseconds() won't produce an accurate delay
	// For safety, a cap is put at 10,000. For delays greater than that, the delay() function is used
	if (microBitDelay >= 10000u) {
		microBitDelay = 0u;
		milliBitDelay = (desiredBitTime - minimumBitTime) / 1000u; // Converts to milliseconds
	}
}
