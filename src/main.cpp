#include <Arduino.h>

#define ledPin 13
#define OC1Apin 11
#define OC3Apin 5
#define OC4Apin 6


void set_timer1(int pwm_value) {  
  // Set up timer 1
  noInterrupts();               // Turn off interrupts during setting
  TIMSK1 = 0;                   // Turn off timer 1 interrupts
  // Set timer 1 to Fast Pwm mode with OC1A (dig pin 9) toggling
  TCNT1 = 0;                    // Zero the counter
  TCCR1A = 1<<WGM11 | 1<<WGM10  // for Fast Pwm with TOP from OCR1A
    | 1<<COM1A0;                // To toggle OC1A PB1 D9 on Compare Match
  TCCR1B = 1<<WGM13 | 1<<WGM12// for Fast Pwm with TOP from OCR1A
    | 1;                      // Start timer 1 with prescale 1
  // Set OCR1A *after* setting up TCCR1A & TCCR1B
  OCR1A = pwm_value;                // Gen. about 38095.24 Hz
  pinMode(OC1Apin, OUTPUT);
  interrupts();
}

void set_timer3(int pwm_value) {  
  // Set up timer 1
  noInterrupts();               // Turn off interrupts during setting
  TIMSK3 = 0;                   // Turn off timer 1 interrupts
  // Set timer 1 to Fast Pwm mode with OC1A (dig pin 9) toggling
  TCNT3 = 0;                    // Zero the counter
  TCCR3A = 1<<WGM31 | 1<<WGM30  // for Fast Pwm with TOP from OCR1A
    | 1<<COM3A0;                // To toggle OC1A PB1 D9 on Compare Match
  TCCR3B = 1<<WGM33 | 1<<WGM32// for Fast Pwm with TOP from OCR1A
    | 1;                      // Start timer 1 with prescale 1
  // Set OCR1A *after* setting up TCCR1A & TCCR1B
  OCR3A = pwm_value;                // Gen. about 38095.24 Hz
  pinMode(OC3Apin, OUTPUT);
  interrupts();
}

void set_timer4(int pwm_value) {  
  // Set up timer 1
  noInterrupts();               // Turn off interrupts during setting
  TIMSK4 = 0;                   // Turn off timer 1 interrupts
  // Set timer 1 to Fast Pwm mode with OC1A (dig pin 9) toggling
  TCNT4 = 0;                    // Zero the counter
  TCCR4A = 1<<WGM41 | 1<<WGM40  // for Fast Pwm with TOP from OCR1A
    | 1<<COM4A0;                // To toggle OC1A PB1 D9 on Compare Match
  TCCR4B = 1<<WGM43 | 1<<WGM42// for Fast Pwm with TOP from OCR1A
    | 1;                      // Start timer 1 with prescale 1
  // Set OCR1A *after* setting up TCCR1A & TCCR1B
  OCR4A = pwm_value;                // Gen. about 38095.24 Hz
  pinMode(OC4Apin, OUTPUT);
  interrupts();
}

void set_timer1_interrupt(){
  noInterrupts(); 
  TCCR1B = 0;
  TCCR1B|=(1<<CS10); //Timer 1 No Prescaler
  TCCR1B|=(1<<WGM12); //Timer 1 in CTC Mode
  TIMSK1 |= (1 << OCIE1A); //Timer 1 enables compare interrupt
  OCR1A=40000; // Frequency of 16 kHz
  interrupts();
}

ISR(TIMER1_COMPA_vect){
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
}

void setup(){
  // pwm_value = 16000000/2/freq_value - 1
  // freq_value = 16000000/2/(pwm_value+1)

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  set_timer1(1000); //8 KHz
  set_timer3(79); //100 KHz
  set_timer4(7); //1 MHz

  //set_timer1_interrupt(); // Check Interrup timing

}

void loop()
{
  // your program here…
  Serial.println("Starting Loop");
  
  /*
  while(1){
    increase_counter = increase_counter + 100;
    set_timer1(increase_counter); //8 KHz
    _delay_ms(1000);

  }*/

  digitalWrite(ledPin,HIGH);
  _delay_ms(1000);
  digitalWrite(ledPin,LOW);
  _delay_ms(1000);

}