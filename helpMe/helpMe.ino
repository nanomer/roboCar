int blackMin = 670;
int blackMid = 450;
int blackLeft = 570;
void setup() {
   //Digital
  Serial.begin(9600);
  //IR
  pinMode(2, INPUT); //Left
  pinMode(3, INPUT); //Front
  pinMode(4, INPUT); //Right

  
  //Motors
  pinMode(9, OUTPUT); //Right Motor (Forward) 
  pinMode(10, OUTPUT); //Right Motor (Backward) 
  pinMode(11, OUTPUT); //Left Motor (Backward)
  pinMode(12, OUTPUT); //Left Motor (Forward)
 
  //Analog
  //PR
  pinMode(17, INPUT); //Middle A3
  pinMode(18, INPUT); //Left A4
  pinMode(19, INPUT); //Right A5
}
void goCar() {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
}
void stopCar(){
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
}

void turnLeft(){
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
}

void turnRight(){
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
}

void loop() {
  int leftIR = digitalRead(2);
  int frontIR = digitalRead(3);
  int rightIR = digitalRead(4);
  int leftPR = analogRead(18);
  int midPR = analogRead(17);
  int rightPR = analogRead(19);

  Serial.println(leftPR);
  Serial.println(midPR);
  Serial.println(rightPR);
  Serial.println();
turnLeft();
//turnRight();
  //if(leftPR<=blackLeft && rightPR <=blackMin)
 // {
   // goCar();
  //}
  if(leftPR>=blackLeft)
  {
    turnLeft();
  }
  /*if(midPR<=blackMid && leftPR>=blackLeft)
  {
    turnLeft();
  }*/
  if(rightPR>=blackMin)
  {
    turnRight();
  }
  if(frontIR==1)
  {
    stopCar();
  }
  if(leftIR==1)
  {
    turnRight();
  }
  if(rightIR==1)
  {
    turnLeft();
  }
  delay(30);
  stopCar();
  delay(100);
}
