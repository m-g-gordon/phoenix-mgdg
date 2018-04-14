#include "Hex_Globals.h"
#include "Hex_Cfg.h"

int counter = 0;
int triggerDistance = 15;

float getFrontDistance();
float getBackDistance();
float getRightDistance();
float getLeftDistance();

void InitializeUltrasonic() {
  pinMode(echoFront,INPUT);
  pinMode(trigFront,OUTPUT);
  pinMode(echoLeft,INPUT);
  pinMode(trigLeft,OUTPUT);
  pinMode(echoRight,INPUT);
  pinMode(trigRight,OUTPUT);
  pinMode(echoBack,INPUT);
  pinMode(trigBack,OUTPUT);
  pinMode(SOUND_PIN, OUTPUT);
}

void calcSensorDistances() {

    float distanceFront = 0.0, distanceLeft = 0.0, distanceBack = 0.0, distanceRight = 0.0;

    if((distanceFront = getFrontDistance()) < triggerDistance && (distanceRight = getRightDistance()) < triggerDistance && (distanceBack = getBackDistance()) < triggerDistance && (distanceLeft = getLeftDistance()) < triggerDistance) {tone(SOUND_PIN, 3500);}
    else if((distanceFront = getFrontDistance()) < triggerDistance && (distanceRight = getRightDistance()) < triggerDistance && (distanceBack = getBackDistance()) < triggerDistance) {tone(SOUND_PIN, 1500);}
    else if((distanceFront = getFrontDistance()) < triggerDistance && (distanceRight = getRightDistance()) < triggerDistance && (distanceLeft = getLeftDistance()) < triggerDistance) {tone(SOUND_PIN, 1500);}
    else if((distanceFront = getFrontDistance()) < triggerDistance && (distanceLeft = getLeftDistance()) < triggerDistance && (distanceBack = getBackDistance()) < triggerDistance) {tone(SOUND_PIN, 1500);}
    else if((distanceLeft = getLeftDistance()) < triggerDistance && (distanceRight = getRightDistance()) < triggerDistance && (distanceBack = getBackDistance()) < triggerDistance) {tone(SOUND_PIN, 1500);}
    else if((distanceFront = getFrontDistance()) < triggerDistance && (distanceRight = getRightDistance()) < triggerDistance) {tone(SOUND_PIN, 1000);}
    else if((distanceFront = getFrontDistance()) < triggerDistance && (distanceBack = getBackDistance()) < triggerDistance) {tone(SOUND_PIN, 1000);}
    else if((distanceRight = getRightDistance()) < triggerDistance && (distanceBack = getBackDistance()) < triggerDistance) {tone(SOUND_PIN, 1000);}
    else if((distanceLeft = getLeftDistance()) < triggerDistance && (distanceRight = getRightDistance()) < triggerDistance) {tone(SOUND_PIN, 1000);}
    else if((distanceFront = getFrontDistance()) < triggerDistance && (distanceLeft = getLeftDistance()) < triggerDistance) {tone(SOUND_PIN, 1000);}
    else if((distanceLeft = getLeftDistance()) < triggerDistance && (distanceBack = getBackDistance()) < triggerDistance) {tone(SOUND_PIN, 1000);}
    else if((distanceFront = getFrontDistance()) < triggerDistance){tone(SOUND_PIN, 750);}
    else if((distanceRight = getRightDistance()) < triggerDistance){tone(SOUND_PIN, 500);}
    else if((distanceBack = getBackDistance()) < triggerDistance){tone(SOUND_PIN, 750);}
    else if((distanceLeft = getLeftDistance()) < triggerDistance){tone(SOUND_PIN, 500);}
    else {noTone(SOUND_PIN);}
    
    counter++;
    if(counter % 50 == 0){
//      DBGSerial.print("Front Distance: ");
//      Serial.println(getFrontDistance());
//      Serial.print("Left Distance: ");
//      Serial.println(getLeftDistance());
//      Serial.print("Right Distance: ");
//      Serial.println(getRightDistance());
//      Serial.print("Back Distance: ");
//      Serial.println(getBackDistance());
//      Serial.println();
    }
}

float getFrontDistance(){
    digitalWrite(trigFront, LOW);
    delayMicroseconds(2);
    digitalWrite(trigFront, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigFront, LOW);

    float durFront = pulseIn(echoFront, HIGH);
    float dFront = durFront * 0.034 /2;

    return dFront;
}

float getLeftDistance(){
    digitalWrite(trigLeft, LOW);
    delayMicroseconds(2);
    digitalWrite(trigLeft, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigLeft, LOW);

    float durLeft = pulseIn(echoLeft, HIGH);
    float dLeft = durLeft * 0.034 /2;

    return dLeft;
}

float getRightDistance(){
    digitalWrite(trigRight, LOW);
    delayMicroseconds(2);
    digitalWrite(trigRight, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigRight, LOW);

    float durRight = pulseIn(echoRight, HIGH);
    float dRight = durRight * 0.034 /2;

    return dRight;
}

float getBackDistance(){
    digitalWrite(trigBack, LOW);
    delayMicroseconds(2);
    digitalWrite(trigBack, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigBack, LOW);

    float durBack = pulseIn(echoBack, HIGH);
    float dBack = durBack * 0.034 /2;

    return dBack;
}

