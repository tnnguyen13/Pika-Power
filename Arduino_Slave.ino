#include <Wire.h> //transmit between two Arduinos, this Arduino is the slave
#include <Servo.h> //enables Servo library
#include "SD.h" //library to read SD card
#include "TMRpcm.h" //library to play audio
#include "SPI.h" //SPI library for SD card
#define tail3_RED 2 //tail RGB #3 red
#define tail3_GREEN 3 //tail RGB #3 green
#define tail3_BLUE 4 //tail RGB #4 blue
Servo servo_tail; //sets up servo motor in tail3
#define tail4_RED 5 //tail RGB #4 red
#define tail4_GREEN 6 //tail RGB #4 green
#define tail4_BLUE 7 //tail RGB #4 blue
#define SD_ChipSelectPin 8 //Chip select is pin number 4
#define cheeks_RED 14 //cheek RGB red
#define cheeks_GREEN 15 //cheek RGB green
#define cheeks_BLUE 16 //check RGB blue
int x = 0;
TMRpcm music; //Library object is named "music"

void setup() {
  Wire.begin(17);
  pinMode(tail3_RED,OUTPUT);
  pinMode(tail3_GREEN,OUTPUT);
  pinMode(tail3_BLUE,OUTPUT);
  servo_tail.attach(A3);
  pinMode(tail4_RED,OUTPUT);
  pinMode(tail4_GREEN,OUTPUT);
  pinMode(tail4_BLUE,OUTPUT);
  pinMode(cheeks_RED,OUTPUT);
  pinMode(cheeks_GREEN,OUTPUT);
  pinMode(cheeks_BLUE,OUTPUT);
  Serial.begin(9600);
  music.speakerPin = 9; //arduino out on pin 9
  if (!SD.begin(SD_ChipSelectPin)) { //failsafe for SD card check
    Serial.println("SD fail");
    return;
  }
  music.setVolume(5); //0 to 5. Sets volume level
  music.quality(1);

}

void receiveEvent(int bytes) {
  x = Wire.read();
  //Serial.print(x); //test print
}

void loop() {
  Wire.onReceive(receiveEvent);
  delay(100);
  if (x==29) { //pika set up behavior
    pika_start();
    //pika_start2();
  }
  else if (x==22) { //happy pikachu behavior
    cheek_redblink1();
    cheek_redblink2();
    cheek_longred();
    cheek_yellowshock();
    //tail_thundershock();
  }
  else if (x==23) { //angry_red
    angry_red();
  }
  else if (x==24) { //angry_thunder1
    angry_thunder1();
  }
  else if (x==25) { //angry_thunder2
    angry_thunder2();
  }
  else if (x==26) { //dizzy_pika
    dizzy_pika();
  }
  else if (x==27) { //dizzy_shock1
    dizzy_shock1();
  }
  else if (x==28) { //dizzy_shock2
    //code
  }
}

void cheek_redblink1() {
  digitalWrite(cheeks_RED,255); //cheek first blink
  digitalWrite(cheeks_GREEN,0);
  digitalWrite(cheeks_BLUE,0);
  music.play("PIWAV4.wav",0);
  delay(1020);
  digitalWrite(cheeks_RED,0);
  delay(100);
  int pos = 0;
  for (int i=0; i<45; i+=1) {
    pos+=1;
    servo_tail.write(pos);
    delay(10);
  }
  pos = 0;
}

void cheek_redblink2() {
  digitalWrite(cheeks_RED,255); //cheek second blink
  digitalWrite(cheeks_GREEN,0);
  digitalWrite(cheeks_BLUE,0);
  music.play("PIWAV4.wav",1.03);
  delay(680);
  digitalWrite(cheeks_RED,0);
  delay(70);
}

void cheek_longred() {
  digitalWrite(cheeks_RED,255); //cheek third length blink
  digitalWrite(cheeks_GREEN,0);
  digitalWrite(cheeks_BLUE,0);
  music.play("PIWAV4.wav",1.71);
  delay(450);
}

void cheek_yellowshock() { //cheeks yellow for thundershock
  digitalWrite(tail3_RED,255); //tail arc for thundershock
  digitalWrite(tail3_GREEN,150);
  digitalWrite(tail3_BLUE,0);
  delay(30);
  /*digitalWrite(tail4_RED,255);
  digitalWrite(tail4_GREEN,255);
  digitalWrite(tail4_BLUE,0);
  delay(1000); //change for behavior reset
  digitalWrite(tail3_RED,0);
  digitalWrite(tail4_RED,0);
  digitalWrite(tail3_GREEN,0);
  digitalWrite(tail4_GREEN,0);
  */
  digitalWrite(cheeks_RED,255);
  digitalWrite(cheeks_GREEN,255);
  digitalWrite(cheeks_BLUE,0);
  music.play("PIWAV4.wav",2.17);
  digitalWrite(tail4_RED,255);
  digitalWrite(tail4_GREEN,200);
  digitalWrite(tail4_BLUE,0);
  delay(789);
  digitalWrite(tail3_RED,0);
  digitalWrite(tail4_RED,0);
  digitalWrite(tail3_GREEN,0);
  digitalWrite(tail4_GREEN,0);
  
  digitalWrite(cheeks_RED,0);
  digitalWrite(cheeks_GREEN,0);
}

/*void tail_thundershock() {
  digitalWrite(tail3_RED,255); //tail arc for thundershock
  digitalWrite(tail3_GREEN,255);
  digitalWrite(tail3_BLUE,0);
  delay(30);
  digitalWrite(tail4_RED,255);
  digitalWrite(tail4_GREEN,255);
  digitalWrite(tail4_BLUE,0);
  delay(1000); //change for behavior reset
  digitalWrite(tail3_RED,0);
  digitalWrite(tail4_RED,0);
  digitalWrite(tail3_GREEN,0);
  digitalWrite(tail4_GREEN,0);
}*/

void pika_start() { //behavior when pikachu doll begins movement
  int pos = 90;
  
  for (int i=0; i<45; i+=1) {
    pos+=1;
    servo_tail.write(pos);
    delay(10);
  }

  for (int i=0; i<45; i+=1) {
    pos-=1;
    servo_tail.write(pos);
    delay(10);
  }
  pos = 0;

  digitalWrite(cheeks_RED,255);
  digitalWrite(cheeks_GREEN,0);
  digitalWrite(cheeks_BLUE,0);
  digitalWrite(tail3_RED,255);
  digitalWrite(tail3_GREEN,255);
  digitalWrite(tail3_BLUE,0);
  
  music.play("PSTART1.wav", 0); //2850 ms start
  delay(404);
  //music.pause();

  digitalWrite(tail4_RED,255);
  digitalWrite(tail4_GREEN,255);
  digitalWrite(tail4_BLUE,0);
  
  //music.pause(); //3430 ms start
  delay(462); //ends at 3530 ms
  //music.pause();
  //total length of cut is 680 ms

  /*for (int i=0; i<=45; i+=1) {
    int pos = 90;
    pos-=1;
    servo_tail.write(pos);
    delay(1);
  }*/

  delay(500); //delay, then turns LEDs off to reset doll
  digitalWrite(cheeks_RED,0);
  digitalWrite(tail3_RED,0);
  digitalWrite(tail3_GREEN,0);
  digitalWrite(tail4_RED,0);
  digitalWrite(tail4_GREEN,0);
}

void angry_red() {
  digitalWrite(cheeks_RED,255);
  digitalWrite(cheeks_GREEN,0);
  digitalWrite(cheeks_BLUE,0);

  //music.play("ANGRY SOUND",time); //ADJUST TIMING
  delay(100); //ADJUST TIMING

  for (int pos=0; pos<=100; pos+=1) {
    servo_tail.write(pos);
    delay(40);
  }
}



void angry_thunder1() {
  digitalWrite(tail3_RED,255);
  digitalWrite(tail3_GREEN,255);
  digitalWrite(tail3_BLUE,0);

  //music.play("ANGRY SOUND 2",time); //ADJUST TIMING
  delay(100); //ADJUST TIMING
}

void angry_thunder2() {
  digitalWrite(tail4_RED,255);
  digitalWrite(tail4_GREEN,255);
  digitalWrite(tail4_GREEN,0);

  //music.play("ANGRY SOUND 3",time); //ADJUST TIMING
  delay(100); //ADJUST TIMING

  for(int pos = 100; pos>=0; pos-=1) {
    servo_tail.write(pos);
    delay(1);
  }

  digitalWrite(cheeks_RED,0); //turns off LEDS to reset doll
  digitalWrite(tail3_RED,0);
  digitalWrite(tail3_GREEN,0);
  digitalWrite(tail4_RED,0);
  digitalWrite(tail4_GREEN,0);
}

void dizzy_pika() {
  digitalWrite(cheeks_RED,255);
  digitalWrite(cheeks_GREEN,0);
  digitalWrite(cheeks_BLUE,0);
  digitalWrite(tail3_RED,255);
  digitalWrite(tail3_GREEN,255);
  digitalWrite(tail3_BLUE,0);
  digitalWrite(tail4_RED,0);
  digitalWrite(tail4_GREEN,0);
  digitalWrite(tail4_BLUE,0);
  delay(100);
  digitalWrite(tail3_RED,0);
  digitalWrite(tail3_GREEN,0);
  digitalWrite(tail4_RED,255);
  digitalWrite(tail4_GREEN,255);
  delay(100);
  digitalWrite(tail3_RED,255);
  digitalWrite(tail3_GREEN,255);
  digitalWrite(tail4_RED,255);
  digitalWrite(tail4_GREEN,255);

  //music.play("ANNOYED1",time) //ADJUST TIMING
  delay(100);

  for (int pos = 0; pos<=45; pos+=1) {
    servo_tail.write(pos);
    delay(35);
  }

  digitalWrite(tail3_RED,0);
  digitalWrite(tail3_GREEN,0);
  digitalWrite(tail4_RED,0);
  digitalWrite(tail4_GREEN,0);

  for (int pos = 45; pos>=0; pos-=1) {
    servo_tail.write(pos);
    delay(35);
  }
}

void dizzy_shock1() {
  digitalWrite(tail3_RED,255);
  digitalWrite(tail3_GREEN,255);
  digitalWrite(tail4_RED,255);
  digitalWrite(tail4_GREEN,255);

  //music.play("ANNOYED2", timing) //ADJUST TIMING
  delay(100); //ADJUST TIMING
  
  for(int pos=0; pos<=45; pos+=1) {
    servo_tail.write(pos);
    delay(35);

  digitalWrite(tail3_RED,0);
  digitalWrite(tail3_GREEN,0);
  digitalWrite(tail4_RED,0);
  digitalWrite(tail4_GREEN,0);
  digitalWrite(cheeks_RED,0); 
  }
}

void dizzy_shock2() {
  digitalWrite(cheeks_RED,255);
  digitalWrite(tail3_RED,255);
  digitalWrite(tail3_GREEN,255);
  digitalWrite(tail4_RED,255);
  digitalWrite(tail4_GREEN,255);
  
  //music.play("ANNOYED FINISH",timing) //ADJUST TIMING
  delay(100); //ADJUST TIMING

  delay(300);
  for(int pos = 45; pos>=0; pos-=1) {
    servo_tail.write(pos);
    delay(50);
  }

  digitalWrite(cheeks_RED,0);
  digitalWrite(tail3_RED,0);
  digitalWrite(tail3_GREEN,0);
  digitalWrite(tail4_RED,0);
  digitalWrite(tail4_GREEN,0);
}
