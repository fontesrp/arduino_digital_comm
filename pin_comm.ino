#define BITS_PER_BYTE 8

void digitalSend(unsigned char pinNumber, unsigned int data) {

	int i;
	char pinState;
	unsigned int converter = 1;
	unsigned char sendBit = 0;

	noInterrupts();

	for (i = 0; i < sizeof(unsigned int) * BITS_PER_BYTE; i++) {
		converter = converter << i;
		sendBit   = (data & converter) >> i;
		pinState  = (sendBit == 0 ? LOW : HIGH);
		digitalWrite(pinNumber, pinState);
	}

	interrupts();
}

unsigned int digitalReceive(unsigned char pinNumber) {

	int i;
	char pinState;
	unsigned int data = 0;
	unsigned char receivedBit;

	noInterrupts();

	for (i = 0; i < sizeof(unsigned int) * BITS_PER_BYTE; i++) {
		pinState = digitalRead(pinNumber);
		receivedBit = (pinState == LOW ? 0 : 1);
		data = (data << i) | receivedBit;
	}

	interrupts();

	return data;
}
