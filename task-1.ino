/*
 * Jacob Koziej
 * millis-micros (task 1)
 * 2020-10-29
 */

#define LED 11
#define PERIOD 1000UL
#define STEP   (PERIOD * 1000UL / 256UL)

uint32_t t_init, t_init_step;
uint8_t  fade_lvl;

void setup()
{
	pinMode(LED, OUTPUT);
}

void loop()
{
	t_init      = millis();
	t_init_step = micros();

	do {
		if (micros() - t_init_step >= STEP) {
			++fade_lvl;
			t_init_step = micros();
		}

		analogWrite(LED, fade_lvl);
	} while (millis() - t_init <= PERIOD);

	fade_lvl = 0;
}
