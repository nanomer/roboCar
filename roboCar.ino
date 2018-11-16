int stateRed = 968;
int stateBlack = 1023;
void setup() {
  // put your setup code here, to run once:
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

  //Stop when sense RED
  if(5==stateRed || 18==stateRed || 19==stateRed)
  {
    analogWrite(14, 0);
    analogWrite(15, 0);
    analogWrite(16, 0);
    analogWrite(17, 0);
  }

  //Stop when Phase 5 obstacle
  else if(2==HIGH && !3 &&!4)
  {
    analogWrite(14, 0);
    analogWrite(15, 0);
    analogWrite(16, 0);
    analogWrite(17, 0);
  }

  else
  {
    if(5==stateBlack || 18==stateBlack || 19==stateBlack)
    {
      if(18==LOW || 19==LOW)
      {
        analogWrite(14, 0);
        analogWrite(15, 0);
        analogWrite(16, 0);
        analogWrite(17, 0);
        if(18==LOW)
        {
          analogWrite(14, 1023); //adjust number for speed
          analogWrite(15, 0);
          analogWrite(16, 0);
          analogWrite(17, 0);
        }
        else if(19==LOW)
        {
          analogWrite(14, 0); 
          analogWrite(15, 0);
          analogWrite(16, 0);
          analogWrite(17, 1023);
        }
      }
      else
      {
        analogWrite(14, 1023);
        analogWrite(15, 1023);
        analogWrite(16, 1023);
        analogWrite(17, 1023);
      }
    }
    else if(2==HIGH || 3==HIGH || 4==HIGH)
    {
      if(2==HIGH)
      {
        analogWrite(14, 510);
        analogWrite(15, 510);
        analogWrite(16, 510);
        analogWrite(17, 510);
      }
      if(3==HIGH)
      {
        analogWrite(14, 1023); //adjust number for speed
        analogWrite(15, 0);
        analogWrite(16, 0);
        analogWrite(17, 0);
      }
      else if(4==HIGH)
      {
        analogWrite(14, 0); 
        analogWrite(15, 0);
        analogWrite(16, 0);
        analogWrite(17, 1023);
      }
    }
    else
    {
      analogWrite(14, 1023);
      analogWrite(15, 1023);
      analogWrite(16, 1023);
      analogWrite(17, 1023);
    }
  }
}
