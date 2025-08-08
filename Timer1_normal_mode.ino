volatile bool timer = false;
void setup() {
  Serial.begin(115200);
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TCNT1 = 0;
  TCCR1B |= (1 << CS11);  //Prescaler = 8 and period is 0.5us(microseconds) and Normal mode

  TIMSK1 |= (1 << OCIE1A);  //0.5us * 65 535 = 0.032s = 32ms
  OCR1A = 9;            //5us period
  // TIFR1 |= (1 << OCF1A);  //Enable the Output Compare Flag register
}

void loop() {
  if (timer) {
    Serial.println(micros() / 1000);
    timer = false;
  }
}
ISR(TIMER1_COMPA_vect) {
  TCNT1=0;
  timer = true;
}
