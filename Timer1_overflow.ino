volatile bool timer = false;
void setup() {
  Serial.begin(115200);
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TCNT1 = 0;
  TCCR1B |= (1 << CS11);   //Prescaler = 8 and period is 0.5us(microseconds)
  TIMSK1 |= (1 << TOIE1);  //0.5us * 65 535 = 0.032s = 32ms
  TIFR1 |= (1 << TOV1);
}

void loop() {
  if (timer) {
    Serial.println(micros() / 1000);
    timer = false;
  }
}
ISR(TIMER1_OVF_vect) {
  timer = true;
  //Fires every 32ms
}
