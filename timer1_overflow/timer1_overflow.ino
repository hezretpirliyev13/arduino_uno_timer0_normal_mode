// Timer 1 is 16-bit (0-65 535)
//1/16MHz = 62.5ns which means for one tick is period 62.5ns(nanoseconds)
// fclk=N * (0-65 535) / fcpu(16MHz) = 0.0327675s 

volatile bool timer = false;
void setup() {
    Serial.begin(115200);
    TCCR1A = 0;              //Reset the Timer/Counter 1A Control Register 
    TCCR1B = 0;              //Reset the Timer/Counter 1B Control Register
    TCCR1C = 0;              //Reset the Timer/Counter 1C Control Register
    TCNT1 = 0;               // Reset the Timer/Counter1 register
    TCCR1B |= (1 << CS11);   //Prescaler = 8 and period is 0.5us(microseconds)
    // TCCR1B |= 0b00000010;  //Prescaler = 8 other type to set the bit1
    TIMSK1 |= (1 << TOIE1);  //0.5us * 65 535 = 0.032s = 32ms
    // TIMSK1 |= 0b00000001; //0.5us * 65 535 tick = 0.032s = 32ms
    TIFR1 |= (1 << TOV1);    //Enable the Timer/Counter 1 Overflow Flag
    // TIFR1 |= 0b00000001;  //Enable the Timer/Counter 1 Overflow Flag
}

void loop() {
    if (timer) {
        Serial.println(micros() / 1000);
        timer = false;
    }   
}
ISR(TIMER1_OVF_vect) {
    timer = true;
    // Fires every 32ms
}
