// Constants
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver srituhobby = Adafruit_PWMServoDriver();

#define servoMIN 150
#define servoMAX 600
int servoval;
const int servos = 4;
int straighttvalues[4]={470,350,450,150};
int pick[4];
int drop[4]={520,570,500,600};
int values[4]={470,350,450,150};
int turn1[4]={350,570,450,600};


void setup() {
  Serial.begin(9600);
  srituhobby.begin();
  srituhobby.setPWMFreq(60);
}


void pickup(){
    for (int i =3 ;i>-1 ; i--){
      Serial.println(i);
      if (values[i] < straighttvalues[i]){
        for (float j = values[i];j<straighttvalues[i];j=j+0.1 ){
          srituhobby.setPWM(i,0,j);
          }
      }else if(values[i]> straighttvalues[i]){
        for (float j = values[i];j>straighttvalues[i];j=j-0.1 ){
            srituhobby.setPWM(i,0,j);
      }
      }else{
      Serial.print("Equal");
      }

}
  for (int i = 0; i < servos; i++) {
        values[i] = straighttvalues[i];
    }
  
}


void puttingdown(){


}


void move(int destination[]){
   for (int i =0 ;i<servos ; i++){
    if (values[i] < destination[i]){
    for (float j = values[i];j<destination[i];j=j+0.1 ){
    srituhobby.setPWM(i,0,j);
   }
    }else if(values[i]> destination[i]){
      for (float j = values[i];j>destination[i];j=j-0.1 ){
    srituhobby.setPWM(i,0,j);
   }
    }else{
      Serial.print("Equal");
    }

}
  for (int i = 0; i < servos; i++) {
        values[i] = destination[i];
    }
}

void loop() {
  if (Serial.available() > 0) {
  
    String input = Serial.readStringUntil('\n');


    servoval = input.toInt();
  };
  switch (servoval) {
  case 1:
    move(straighttvalues);
    Serial.println("Straight");
    
    delay(300);
    break;

  case 2:
    move(turn1);
    Serial.println("Turn1");
    delay(300);
    break;

  case 3:
    for (int i=0;i<servos;i++){
      pick[i]=values[i];
      if (i==2){
        pick[i] = pick[i]-50;
      }
    }
    move(pick);
    Serial.println("Mving Down");
    delay(300);
    break;
  case 4:
    pickup();
    Serial.println("Picking up");
    delay(300);
    break;
  case 5:
    move(drop);
    Serial.println("Dropping");
    delay(300);
    break;

  };
  servoval = 0;


};
