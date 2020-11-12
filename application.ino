/*
 * Jacob Koziej
 * millis-micros (application)
 * 2020-11-04
 * 2020-11-11
 */

const uint16_t PERIOD[] = {2000, 500, 3000, 2500};

const uint8_t PIN[][4] = {
	{3, 5, 6, 9},
	{2, 4, 7, 8}
};

const uint8_t SPEED[][4] = {
	{ 128,  255,  128,  64},
	{-256, -128, -128, -64}  // Done to overflow to correct inverse val
};

uint32_t time_start[4];
uint8_t  state = 0;  // Bits 3-0 represent forward or reverse motor direction

void setup()
{
	uint32_t time_capture = millis();

	for (int i = 0; i < 4; i++) {
		pinMode(PIN[0][i], OUTPUT);
		pinMode(PIN[1][i], OUTPUT);

		// Set initial time
		time_start[i] = time_capture;

		// Set initial states
		analogWrite(PIN[0][i], SPEED[0][i]);
		digitalWrite(PIN[1][i], 0);
	}
}

void loop()
{
	for (int i = 0; i < 4; i++) {
		uint32_t time_capture = millis();

		if (time_capture - time_start[i] >= PERIOD[i]) {
			time_start[i] = time_capture;
			state ^= _BV(i);

			/*
			 * Since array SPEED in the second dimension only has a
			 * range of 0 to 1, state & _BV(i) ? 1 : 0 is necessary
			 * to stay within this bound.
			 */
			analogWrite(PIN[0][i], SPEED[state & _BV(i) ? 1 : 0][i]);
			digitalWrite(PIN[1][i], state & _BV(i));
		}
	}
}
