void setup() {
  pinMode(9, OUTPUT); // OC1A (Pin 9)

  cli();  // Disable interrupts

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Fast PWM, Mode 14 (WGM13:0 = 1110), TOP = ICR1
  TCCR1A |= (1 << COM1A1) | (1 << WGM11);                   // Non-inverting PWM on OC1A
  TCCR1B |= (1 << WGM13) | (1 << WGM12);     // Part of WGM14
  TCCR1B |= (1 << CS11);                     // Prescaler = 8 (0.5 µs per tick)

  ICR1 = 99;        // TOP = 199 → 100 µs period
  OCR1A = 29;        // 30% duty cycle

  sei(); // Enable interrupts if needed
}

void loop() {
  // Nothing needed; PWM runs in hardware
}
