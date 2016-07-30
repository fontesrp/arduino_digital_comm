#include "arduino_digital_comm.h"

void setup() {
	Serial.begin(9600);
	pinMode(OUTPUT_PIN, OUTPUT);
	setBitDelay();
}

void loop() {

	unsigned long bitTime;

	Serial.println("main loop: fired");

	bitTime = getMinBitTime();

	Serial.print("main loop: minimum bit time = ");
	Serial.print(bitTime);
	Serial.print(" us");
	Serial.println("");

	delay(3000);
}
