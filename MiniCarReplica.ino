const int BUZZER=2;
const int ECHO_FRONT=13;
const int TRIG_FRONT=12;
const int ECHO_SIDE=9;
const int TRIG_SIDE=8;
const int LIGHT_PARKING_WARNING_FRONT=4;
const int LIGHT_BLIND_SPOT_SIDE=7;


void setup() {
  pinMode(BUZZER,OUTPUT);
  pinMode(TRIG_FRONT,OUTPUT);
  pinMode(ECHO_FRONT,INPUT);
  pinMode(LIGHT_PARKING_WARNING_FRONT,OUTPUT);
  pinMode(TRIG_SIDE,OUTPUT);
  pinMode(ECHO_SIDE,INPUT);
  pinMode(LIGHT_BLIND_SPOT_SIDE,OUTPUT);
   Serial.begin(9600);
}

long timeToObject(int trigPin, int echoPin) {
 //Make sure that there is no wave
 //that has been sent
  digitalWrite(trigPin,LOW);
  delay(2);
  
  //Send wave to get timeToFront then 
  //convert to distance
  digitalWrite(trigPin,HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);
  return pulseIn(echoPin,HIGH);
}

 //Begins to buzz rapidly for the person parking the car
 //Will buzz one constant note when the user should stop moving the car
void buzzAndLight() {
  int distFront=timeToObject(TRIG_FRONT,ECHO_FRONT)*0.034/2;
  if(distFront < 50 && distFront >= 7) {
  digitalWrite(LIGHT_PARKING_WARNING_FRONT,HIGH);
  tone(BUZZER,2000);
  delay(distFront*8);
  digitalWrite(LIGHT_PARKING_WARNING_FRONT,LOW);
  noTone(BUZZER);
  delay(distFront*8);
  
  }else if(distFront < 7){
    digitalWrite(LIGHT_PARKING_WARNING_FRONT,HIGH);
    tone(BUZZER,2000);
  }
  else{
    noTone(BUZZER);
    digitalWrite(LIGHT_PARKING_WARNING_FRONT,LOW);
  }
}

void checkBlindSpot() {
int distSide=(timeToObject(TRIG_SIDE,ECHO_SIDE)*0.034/2);
Serial.println(distSide);
if(distSide > 5 && distSide < 25) {
  digitalWrite(LIGHT_BLIND_SPOT_SIDE,HIGH);
 }
else{
  digitalWrite(LIGHT_BLIND_SPOT_SIDE,LOW);
 }
}

void loop() {
   //Convert time to centimetres for the front 
   //to get distance for front ultrasonic sensor
   buzzAndLight();
   checkBlindSpot();
}
