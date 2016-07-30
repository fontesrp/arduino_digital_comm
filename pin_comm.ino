#define DATA_BIT_SIZE 10u // unsigned char

unsigned long bitRate = 2000; // bits per second

void send10b(unsigned char pinNumber, unsigned int data) {

	unsigned char i;
	unsigned int converter = 1u;
	char pinState;

	noInterrupts();

	for (i = 0u; i < DATA_BIT_SIZE; i++) {
		pinState  = ((data & converter) == 0u ? LOW : HIGH);
		digitalWrite(pinNumber, pinState);
		converter = converter << 1;
	}

	interrupts();
}

unsigned int receive10b(unsigned char pinNumber) {

	unsigned char i;
	unsigned int data = 0u;
	char pinState;

	noInterrupts();

	for (i = 0u; i < DATA_BIT_SIZE; i++) {
		pinState = digitalRead(pinNumber);
		data = (data << 1) | (pinState == LOW ? 0u : 1u);
	}

	interrupts();

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

unsigned long getMaxBitRate() {

	const unsigned char pinNumber = 2u;
	unsigned long time;
	unsigned int data;

	data = generateAlternatingBitData(DATA_BIT_SIZE);

	time = micros();
	send10b(pinNumber, data);
	time = micros() - time;

	// 'DATA_BIT_SIZE' bits were sent in 'time' microseconds.
	// Bit rate = 'DATA_BIT_SIZE' / ('time' * 10^(-6)) = 'DATA_BIT_SIZE' * 10^6 / 'time' [bps]

	return DATA_BIT_SIZE * 1000000u / time;
}
