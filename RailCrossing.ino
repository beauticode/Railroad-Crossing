#include <Servo.h>
//
short button,led1,led2,buzzer,motor;
Servo smotor;
bool buttonhold; ///Has the button been presed before? Is it still being held?
bool crossenabled;
bool leftled; //Left LED or Right LED?
bool buzzon;
unsigned int led; 
unsigned int buzz;
//
void LEDs();
void ring();
void initardu();
bool pressed();
//
void setup() {
  initardu();
  smotor.attach(motor);
  smotor.write(1);
}

void loop() {
  if(pressed()) {
    if(crossenabled) {
      crossenabled = false;
      smotor.write(1);
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
    } else {
      crossenabled = true;
      smotor.write(90);
    }
  }
  if(crossenabled) {
    LEDs();
    ring();
  }
}

void initardu() {
  buzz = 0;
  button = 8;
  buzzer = 10;
  motor = 11;
  led = 0;
  led1 = 12;
  led2 = 13;
  buttonhold = false;
  crossenabled = false;
  buzzon = false;
  pinMode(button,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
}

bool pressed() {
  bool ispressed = false;
  if(digitalRead(button)==HIGH) {
    if(!buttonhold) { //Button is actually being pressed
      ispressed = true;
      buttonhold = true;
    } else { //Button is not being pressed
      //Void
    }
  } else { //Check if person has taken their finger off of the button yet, if so then they are no longer holding the button down.
    if(buttonhold) {
      buttonhold = false;
    }
  }
  return ispressed;
}

void LEDs() {
  if(leftled) {
    digitalWrite(led1,HIGH);
  } else {
    digitalWrite(led2,HIGH);
  }
  if((millis() - led)>=500) {
    if(leftled) {
      leftled = false;
      digitalWrite(led1,LOW);
    } else {
      leftled = true;
      digitalWrite(led2,LOW);
    }
    led = millis();
  }
}

void ring() {
  if((millis() - buzz)>=110) {
    if(buzzon) {
      digitalWrite(buzzer,LOW);
      buzzon = false;
    } else {
      digitalWrite(buzzer,HIGH);
      buzzon = true;
    }
    buzz = millis();
  }
}

