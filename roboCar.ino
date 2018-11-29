int redMin = 400;
int redMax = 700;
int blackMin = 701;
int blackMax = 1023;

void setup() {
  
  //Digital
  
  //IR
  pinMode(2, INPUT); //Front
  pinMode(3, INPUT); //Left
  pinMode(4, INPUT); //Right
  //PR
  pinMode(5, INPUT); //Middle

  //Analog
  
  //Motors
  pinMode(14, OUTPUT); //Left Motor
  pinMode(15, OUTPUT); //Left Motor
  pinMode(16, OUTPUT); //Right Motor
  pinMode(17, OUTPUT); //Right Motor
  //PR
  pinMode(18, INPUT); //Left
  pinMode(19, INPUT); //Right

}

void loop() {
  // put your main code here, to run repeatedly:

int frontIR = digitalRead(2);
int leftIR = digitalRead(3);
int rightIR = digitalRead(4);
int midPR = digitalRead(5);
int leftPR = analogRead(18);
int rightPR = analogRead(19);

  //Stop when sense RED
  if((leftPR<=redMax && leftPR>=redMin) || (rightPR<=redMax && rightPR>=redMin))
  {
    analogWrite(14, 0);
    analogWrite(15, 0);
    analogWrite(16, 0);
    analogWrite(17, 0);
  }

  //Stop when Phase 4 obstacle
  else if(frontIR==HIGH && leftIR==LOW && rightIR==LOW)
  {
    analogWrite(14, 0);
    analogWrite(15, 0);
    analogWrite(16, 0);
    analogWrite(17, 0);
  }

  //Check first for black line to follow, else worries about walls, else goes straight
  else
  {
    if(midPR==HIGH || (leftPR<=blackMax && leftPR>=blackMin) || (rightPR<=blackMax && rightPR>=blackMin))
    {
      //Checking if left/right PR detects white
      if(leftPR==LOW || rightPR==LOW)
      {
        //Turn off all motors
        analogWrite(14, 0);
        analogWrite(15, 0);
        analogWrite(16, 0);
        analogWrite(17, 0);
        if(leftPR==LOW)
        {
          //Turn right
          analogWrite(14, 1023); //adjust number for speed
          analogWrite(15, 0);
          analogWrite(16, 0);
          analogWrite(17, 0);
        }
        else if(rightPR==LOW)
        {
          //Turn left
          analogWrite(14, 0); 
          analogWrite(15, 0);
          analogWrite(16, 0);
          analogWrite(17, 1023); //adjust for speed
        }
      }
      else
      {
        //Go forward
        analogWrite(14, 1023);
        analogWrite(15, 1023);
        analogWrite(16, 1023);
        analogWrite(17, 1023);
      }
    }
    //Phase 5: Slow when sees wall approaching
    else if(frontIR==HIGH || leftIR==HIGH || rightIR==HIGH)
    {
      if(frontIR==HIGH)
      {
        //Slow down
        analogWrite(14, 510);
        analogWrite(15, 510);
        analogWrite(16, 510);
        analogWrite(17, 510);
      }
      if(leftIR==HIGH)
      {
        //Slight right for 3000 then forward
        analogWrite(14, 1023); //adjust number for speed
        analogWrite(15, 0);
        analogWrite(16, 0);
        analogWrite(17, 0);
        delay(3000);          //change turning duration
        analogWrite(14, 1023);
        analogWrite(15, 1023);
        analogWrite(16, 1023);
        analogWrite(17, 1023);
      }
      else if(rightIR==HIGH)
      {
        //Slight left for 3000 then forward
        analogWrite(14, 0); 
        analogWrite(15, 0);
        analogWrite(16, 0);
        analogWrite(17, 1023);
        delay(3000);          //change turning duration
        analogWrite(14, 1023);
        analogWrite(15, 1023);
        analogWrite(16, 1023);
        analogWrite(17, 1023);
      }
    }
    else
    {
      //Go forward if no special case
      analogWrite(14, 1023);
      analogWrite(15, 1023);
      analogWrite(16, 1023);
      analogWrite(17, 1023);
    }
  }
}
