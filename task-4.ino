/*
 * Jacob Koziej
 * millis-micros (task 4)
 * 2020-10-29
 * 2020-11-02
 */

const uint8_t  LED[]    = {9, 10, 11};
const uint16_t PERIOD[] = {1000, 10, 200};  // 1Hz, 100Hz, 5Hz
const uint16_t STEP[] = {
	// Cast type to calculate step correctly
	((uint32_t) PERIOD[0] * 1000 / 256),
	((uint32_t) PERIOD[1] * 1000 / 256),
	((uint32_t) PERIOD[2] * 1000 / 256)
};

uint32_t t_init[3];
uint32_t t_init_step[3];
uint8_t  fade_lvl[3];

void setup()
{
	uint32_t capture_millis = millis();
	uint32_t capture_micros = micros();

	for (int i = 0; i < 3; i ++) {
		pinMode(LED[i], OUTPUT);
		digitalWrite(LED[i], LOW);
		t_init[i]      = capture_millis;
		t_init_step[i] = capture_micros;
	}
}

void loop()
{
	for (int i = 0; i < 3; i++) {
		uint32_t current_millis = millis();
		uint32_t current_micros = micros();

		if (current_millis - t_init[i] >= PERIOD[i]) {
			fade_lvl[i]    = 0;
			t_init[i]      = current_millis;
			t_init_step[i] = current_micros;
		}

		if (current_micros - t_init_step[i] >= STEP[i]) {
			t_init_step[i] = current_micros;
			analogWrite(LED[i], ++fade_lvl[i]);
		}
	}
}
