/*
 * Jacob Koziej
 * millis-micros (task 3)
 * 2020-10-29
 */

#define LED 11

void setup()
{
	pinMode(LED, OUTPUT);
}

void loop()
{
	digitalWrite(LED, HIGH);
	scuffedDelay(millis(), 1000);
	digitalWrite(LED, LOW);
	scuffedDelay(millis(), 1000);
}

void scuffedDelay(uint32_t t_start, uint32_t t_duration)
{
	while (millis() - t_start <= t_duration) _NOP();
}
