//Still need to be changed

int redMin = 400;
int redMax = 700;
int blackMin = 701;
int blackMax = 1023;

void setup() {
  
  //Digital
  
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
  pinMode(17, INPUT); //Left
  pinMode(18, INPUT); //Middle
  pinMode(19, INPUT); //Right

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
  // put your main code here, to run repeatedly:

int leftIR = digitalRead(2);
int frontIR = digitalRead(3);
int rightIR = digitalRead(4);
int leftPR = analogRead(17);
int midPR = analogRead(18);
int rightPR = analogRead(19);


  stopCar();
  delay(250);

  //Stop when sense RED, average for RED?
  if((leftPR<=redMax && leftPR>=redMin) || (rightPR<=redMax && rightPR>=redMin)|| (midPR<=redMax && midPR>=redMin))
  {
    stopCar();
  }

  //Stop when Phase 4 obstacle
  else if(frontIR==HIGH && leftIR==LOW && rightIR==LOW)
  {
    stopCar();
  }

  //Check first for black line to follow, else worries about walls, else goes straight
  else
  {
    if((midPR<=blackMax && midPR>=blackMin) || (leftPR<=blackMax && leftPR>=blackMin) || (rightPR<=blackMax && rightPR>=blackMin))
    {
      //Checking if left/right PR detects white
      if(leftPR==LOW || rightPR==LOW)
      {
        //Turn off all motors
        //stopCar();
        if(leftPR==LOW)
        {
          turnRight();
        }
        else if(rightPR==LOW)
        {
          //Turn left
          turnLeft();
        }
      }
      else
      {
        //Go forward
        goCar();
      }
    }
    //Phase 5: Slow when sees wall approaching
    else if(frontIR==HIGH || leftIR==HIGH || rightIR==HIGH)
    {
      if(frontIR==HIGH)
      {
       stopCar();
      }
      if(leftIR==HIGH)
      {
        //Slight right for 1000 then forward
        turnRight();
        delay(1000);          //change turning duration
        goCar();
      }
      else if(rightIR==HIGH)
      {
        //Slight left for 1000 then forward
        turnLeft();
        delay(1000);          //change turning duration
        goCar();
      }
    }
    else
    {
      //Go forward if no special case
      goCar();
    }
  }
}
