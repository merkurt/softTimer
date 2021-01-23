#include <Arduino.h>
#include <soft_tim.h>

#define LED 13

volatile uint16_t val1 = 0; 
volatile uint16_t val2 = 0; 
volatile uint16_t val3 = 0; 

volatile uint16_t val1_ex = 150; // 20
volatile uint16_t val2_ex = 750; // 4 
volatile uint16_t val3_ex = 1500; //2


struct softTimer tim1;
struct softTimer tim2;
struct softTimer tim3;
struct softTimer tim4;

void tim1_callback(void){
	val1 += val1_ex;
}

void tim2_callback(void){
	val2 += val2_ex;
}

void tim3_callback(void){
	val3 += val3_ex;
}

void tim4_callback(void){
	Serial.print(val1);
  	Serial.print("/");
  	Serial.print(val2);
  	Serial.print("/");
  	Serial.println(val3);
}

void initTim1(void){
	softTimer_init(&tim1);
	softTimer_setTickMs(&tim1, 1);
	softTimer_setInterval(&tim1, 50);
	softTimer_setCallback(&tim1, &tim1_callback);
}

void initTim2(void){
	softTimer_init(&tim2);
	softTimer_setTickMs(&tim2, 1);
	softTimer_setInterval(&tim2, 250);
	softTimer_setCallback(&tim2, &tim2_callback);
}

void initTim3(void){
	softTimer_init(&tim3);
	softTimer_setTickMs(&tim3, 1);
	softTimer_setInterval(&tim3, 500);
	softTimer_setCallback(&tim3, &tim3_callback);
}

void initTim4(void){
	softTimer_init(&tim4);
	softTimer_setTickMs(&tim4, 1);
	softTimer_setInterval(&tim4, 10);
	softTimer_setCallback(&tim4, &tim4_callback);
}

void initInterrupt(void){	// 1kHz 
	cli(); 
	TCCR1A = 0; 
	TCCR1B = 0; 
	TCNT1  = 0; 
	OCR1A = 15999;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
	sei();
}

ISR(TIMER1_COMPA_vect){
   softTimer_tickHandler(&tim1);
   softTimer_tickHandler(&tim2);
   softTimer_tickHandler(&tim3);
   softTimer_tickHandler(&tim4);
}

void setup() {
	pinMode(LED, OUTPUT);

	Serial.begin(115200);

	initTim1();
	initTim2();
	initTim3();
	initTim4();
	
	initInterrupt();
}

void loop() {
	;
}


