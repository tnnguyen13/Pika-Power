#include <Wire.h> //transmit between two Arduinos, this Arduino is the master
#include <IRremote.h> //enables library for IR Remote input
#include <Servo.h> //enables Servo library

#define RECV_PIN 2 // digital pin for IR Remote input
#define r_button 3 // right button on doll
#define l_button 4 // left button on doll
#define TILT_belly 5 //tilt sensor in belly of doll
#define tail1_RED 6 //multi-color display in tail, red
#define tail1_GREEN 7 //multi-color display in tail, green
#define tail1_BLUE 8 //multi-color display in tail, blue
Servo servo_lt_ear; //sets up servo motor in left ear of doll
Servo servo_rt_ear; //sets up servo motor in right ear of doll
#define tail2_RED 14 //variations of yellow in tail, red
#define tail2_GREEN 15 //variations of yellow in tail, green
#define tail2_BLUE 16 //variations of yellow in tail, blue
IRrecv irrecv(RECV_PIN); // enables the IR Remote input pin #
decode_results results; // decodes results from IR Remote selection

//these variables customize minibehaviors and timing within the doll
int pika_setup = 21;
int cheek_redblink = 22;
int angry_red = 23;
int angry_thunder1 = 24;
int angry_thunder2 = 25;
int dizzy_pika = 26;
int dizzy_shock1 = 27;
int dizzy_shock2 = 28;


void setup(){
  Wire.begin(17); //initiates the Wire library, joins I2C bus as a master or slave
  Serial.begin(9600); //begins Serial monitor
  irrecv.enableIRIn();
  pinMode(r_button,INPUT);
  pinMode(l_button,INPUT);
  pinMode(TILT_belly,INPUT);
  servo_rt_ear.attach(9); // servo motor right ear on doll
  servo_lt_ear.attach(10); // servo motor left ear on doll
  //servo_rt_ear.write(0); //establishes 0 for right ear
  //servo_lt_ear.write(0); //establishes 0 for left ear
  pinMode(tail1_RED,OUTPUT);
  pinMode(tail1_GREEN,OUTPUT);
  pinMode(tail1_BLUE,OUTPUT);
  pinMode(tail2_RED,OUTPUT);
  pinMode(tail2_GREEN,OUTPUT);
  pinMode(tail2_BLUE,OUTPUT);

  pikastretch(); //behavior when pikachu doll turns on
}

void loop() {
    digitalWrite(tail2_RED,255);
    digitalWrite(tail2_GREEN,0);
    digitalWrite(tail2_BLUE,0);
    pikaInput();
    delay(1000);
}

void pikaInput() {
  if(digitalRead(r_button) == HIGH) { //happy Pikachu behavior
    happy_Pika();
  }
  else if(digitalRead(l_button) == HIGH) { //angry Pikachu behavior
    angry_Pika();
  }
  else if(irrecv.decode(&results)) {
    int value = results.value;
    Serial.println(value);
    switch(value) { //redo of Pikachu stretch/set up behavior
      case 12495: //button 1
      pikastretch();
      break;
    }
    switch(value) { //happy Pikachu behavior
      case 6375: //button 2
      happy_Pika();
      break;
    }
    switch(value) { //annoyed Pikachu behavior
      case 31365: //button 3
      annoyed_Pika();
      break;
    }
    switch(value) { //angry Pikachu behavior
      case 25979: //button 4
      angry_Pika();
      break;
    }
    switch(value) {
      //case FF38C7: //button 5
      //LED DESIGN
      break;
    }
    switch(value) {
      //case FF5AA5: //button 6
      //LED DESIGN
      break;
    }
    irrecv.resume();
  }
  else if(digitalRead(TILT_belly)==HIGH) {
    annoyed_Pika();
  }
  else {
    Serial.print("nah fam");
  }
}

void happy_Pika() { //happy pikachu behavior
  for (int pos=0; pos<=45; pos+=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(15);
  }

  Serial.print("hi Daria\n"); //easter egg
  
  Wire.beginTransmission(17);
  Wire.write(cheek_redblink); //tells slave arduino to blink cheek LEDs
  Wire.endTransmission();
  for (int pos = 45; pos>=0; pos-=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(15);
  }

reset();
}

void pikastretch() {
  t_yellow1_on; //first set of tail LEDs light up yellow
  
  for (int pos=0; pos<=30; pos+=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(10);
  }
  
  t_yellow2_on(); //second set of tail LEDs light up yellow
  
  Serial.print("hi saridlin\n"); //easter egg 2

  Wire.beginTransmission(17);
  Wire.write(pika_setup);
  Wire.endTransmission();

  for (int pos = 30 ; pos>=0; pos-=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(10);
  }
  t_yellow1_off(); //turns off LEDS after behavior finishes
  t_yellow2_off();

  reset();
}

void angry_Pika() {
  t_yellow1_on;
  t_yellow2_on();

  Wire.beginTransmission(17);
  Wire.write(angry_red);
  Wire.endTransmission();

  for (int pos = 0; pos<=25; pos+=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(5);
  }

  Serial.print("hi i'm doraerawr"); //easter egg 3
  
  t_yellow1_off();
  t_yellow2_off(); 
  
  for (int pos = 25; pos>=0; pos-=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(5);
  }
  
  t_yellow1_on;
  t_yellow2_on();

  Wire.beginTransmission(17);
  Wire.write(angry_thunder1);
  Wire.endTransmission();

  t_yellow1_off();
  t_yellow2_off();

  for (int pos = 0; pos>=10; pos+=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(1);
  }

  t_yellow1_on; 
  t_yellow2_on();

  Wire.beginTransmission(17);
  Wire.write(angry_thunder2);
  Wire.endTransmission();

  for (int pos=10;pos >=0; pos-=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(20);
  }

  t_yellow1_off();
  t_yellow2_off();

  reset();
}

void annoyed_Pika() {
  for (int pos = 0; pos <=10; pos+=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(20);
  }
  
  t_yellow1_on;
  t_yellow2_off();
  
  delay(50);

  for (int pos = 10; pos<=20; pos +=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(20);
  }
  
  t_yellow1_off();
  t_yellow2_on();
  
  delay(50);

  for (int pos = 20; pos<=30; pos+=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(20);
  }
  
  t_yellow1_on; 
  t_yellow2_off();

  Wire.beginTransmission(17);
  Wire.write(dizzy_pika);
  Wire.endTransmission();

  t_yellow2_on(); 

  for (int pos = 30; pos<=40; pos+=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(20);
  }

  t_yellow2_off();

  Wire.beginTransmission(17);
  Wire.write(dizzy_shock1);
  Wire.endTransmission();

  t_yellow1_on();
  t_yellow2_on();
  

  Wire.beginTransmission(17);
  Wire.write(dizzy_shock2);
  Wire.endTransmission();

  for (int pos = 40; pos>=0; pos-=1) {
    servo_rt_ear.write(pos);
    servo_lt_ear.write(pos);
    delay(5);
  }

  t_yellow1_off();
  t_yellow2_off();
  
  reset();
}

void t_yellow1_on() {
  digitalWrite(tail1_RED,255);
  digitalWrite(tail1_GREEN,200);
  digitalWrite(tail1_BLUE,0);
}

void t_yellow1_off() {
  digitalWrite(tail1_RED,0);
  digitalWrite(tail1_GREEN,0);
  digitalWrite(tail1_BLUE,0);
}

void t_yellow2_on() {
  digitalWrite(tail2_RED,255);
  digitalWrite(tail2_GREEN,200);
  digitalWrite(tail2_BLUE,0);
}

void t_yellow2_off() {
  digitalWrite(tail2_RED,0);
  digitalWrite(tail2_GREEN,0);
  digitalWrite(tail2_BLUE,0);
}

void reset() {
  Wire.beginTransmission(17);
  Wire.write(0);
  Wire.endTransmission();
}
