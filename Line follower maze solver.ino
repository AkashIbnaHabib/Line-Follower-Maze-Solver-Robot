#define leftFarSensor      2
#define leftNearSensor     3
#define centerSensor       4
#define rightNearSensor    5
#define rightFarSensor     6

//#define notchSensor        7

int leftFarReading;
int leftNearReading;
int centerReading;
int rightNearReading;
int rightFarReading;

//int notchReading;

#define leftMotor1  11
#define leftMotor2  10

#define rightMotor1 9
#define rightMotor2 8

#define littleForward 300
#define led 13

#define black  0
#define white  1
#define goRun  220

char path[100] = {};
int pathLength = 0;
int readLength = 0;
bool replaystage = true;

void setup()
{
  pinMode(leftFarSensor, INPUT);
  pinMode(leftNearSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
  //pinMode(notchSensor, INPUT);

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);

  pinMode(led, OUTPUT);

  //Serial.begin(9600);
  digitalWrite(led, HIGH);
  delay(1000);
}

void loop()
{
  readSensors();

  if ((leftFarReading == white && rightFarReading == white && centerReading == black) ||
      (leftFarReading == black && leftNearReading == black && centerReading == black && rightNearReading == white && rightFarReading == white) ||
      (leftFarReading == white && leftNearReading == white && centerReading == black && rightNearReading == black && rightFarReading == black))
  {
    //Serial.println("straight()");
    straight();
  }
  else
  {
    //Serial.println("leftHandWall()");
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(50);
    leftHandWall();
  }
}

void readSensors()
{
  leftFarReading     = digitalRead(leftFarSensor);
  leftNearReading    = digitalRead(leftNearSensor);
  centerReading      = digitalRead(centerSensor);
  rightNearReading   = digitalRead(rightNearSensor);
  rightFarReading    = digitalRead(rightFarSensor);
  //notchReading       = digitalRead(notchSensor);

  //delay(5);

  // serial printing be0 for debugging purposes

  /*
    Serial.print("leftFarReading: ");
    Serial.println(leftFarReading);
    Serial.print("leftNearReading: ");
    Serial.println(leftNearReading);
    Serial.print("centerReading: ");
    Serial.println(centerReading);
    Serial.print("rightNearReading: ");
    Serial.println(rightNearReading);
    Serial.print("rightFarReading: ");
    Serial.println(rightFarReading);
    //Serial.print("notchReading: ");
    //Serial.println(notchReading);
    Serial.println();
    delay(1000);*/
}

void straight()
{
  if ( digitalRead(leftFarSensor) == white && digitalRead(leftNearSensor) == black && digitalRead(centerSensor) == black && digitalRead(rightNearSensor) == black && digitalRead(rightFarSensor) == white)
  {
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(4);
    //Serial.println("straight()--only");
    return;
  }
  else if ( digitalRead(leftFarSensor) == white && digitalRead(leftNearSensor) == white && digitalRead(centerSensor) == black && digitalRead(rightNearSensor) == black && digitalRead(rightFarSensor) == white)
  {
    /*analogWrite(leftMotor1, goRun);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor1, goRun);
      analogWrite(rightMotor2, 0);
      delay(1);*/
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(5);
    //Serial.println("straight()--right--1st");
    return;
  }
  else if ( digitalRead(leftFarSensor) == white && digitalRead(leftNearSensor) == white && digitalRead(centerSensor) == black && digitalRead(rightNearSensor) == black && digitalRead(rightFarSensor) == black)
  {
    /*analogWrite(leftMotor1, goRun);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor1, goRun);
      analogWrite(rightMotor2, 0);
      delay(1);*/
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(5);
    //Serial.println("straight()--right--2nd");
    return;
  }
  else if ( digitalRead(leftFarSensor) == white && digitalRead(leftNearSensor) == black && digitalRead(centerSensor) == black && digitalRead(rightNearSensor) == white && digitalRead(rightFarSensor) == white)
  {
    /*analogWrite(leftMotor1, goRun);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor1, goRun);
      analogWrite(rightMotor2, 0);
      delay(1);*/
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(5);
    //Serial.println("straight()--left--1st");
    return;
  }
  else if ( digitalRead(leftFarSensor) == black && digitalRead(leftNearSensor) == black && digitalRead(centerSensor) == black && digitalRead(rightNearSensor) == white && digitalRead(rightFarSensor) == white)
  {
    /*analogWrite(leftMotor1, goRun);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor1, goRun);
      analogWrite(rightMotor2, 0);
      delay(1);*/
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(5);
    //Serial.println("straight()--left--2nd");
    return;
  }
  else
  {
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(4);
    return;
    //Serial.println("straight()--outside");
  }
}

void leftHandWall()
{
  //T Shape OR Cross Shape OR End Point (3 posibility)
  if ( leftFarReading == black && rightFarReading == black && leftNearReading == black && rightNearReading == black)
  {
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(littleForward);
    readSensors();

    if (leftFarReading == black && rightFarReading == black) {
      doneTravel();
    }
    else 
	{
      turnLeft();
    }
  }
  //END of T Shape OR Cross Shape OR End Point (3 posibility)

  //Left OR Left-Straight
  if (leftFarReading == black && leftNearReading == black && rightNearReading == black && rightFarReading == white)
  {
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(littleForward);
    readSensors();

    if (leftFarReading == white || rightFarReading == white)
    {
      turnLeft();
    }
    else
    {
      doneTravel();
    }
  }
  //End of Left OR Left-Straight

  //Right OR Right-Straight
  if (leftFarReading == white && leftNearReading == black && rightNearReading == black && rightFarReading == black)
  {
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(30);
    readSensors();

    if (leftFarReading == black)
    {
      delay(littleForward - 30);
      readSensors();

      if (rightFarReading == black && leftFarReading == black)
      {
        doneTravel();
      }
      else
      {
        turnLeft();
        return;
      }
    }

    delay(littleForward - 30);
    readSensors();
    if (leftFarReading == white && leftNearReading == white && centerReading == white && rightNearReading == white && rightFarReading == white)
    {
      turnRight();
      return;
    }
    else
    {
      //Shortest path.......
      path[pathLength] = 'S';
      pathLength++;
      if (path[pathLength - 2] == 'B')
      {
        shortPath();
      }
      //End Shortest path.......
      straight();
    }
  }
  //End of Right OR Right-Straight

  //Dead End
  readSensors();
  if (leftFarReading == white && leftNearReading == white && centerReading == white && rightNearReading == white && rightFarReading == white)
  {
    turnAround();//
  }
  //End of Dead End
}

void doneTravel()
{
  analogWrite(leftMotor1, 0);
  analogWrite(leftMotor2, 0);
  analogWrite(rightMotor1, 0);
  analogWrite(rightMotor2, 0);

  //Shortest path.......
  replaystage = false;
  path[pathLength] = 'D';
  pathLength++;
  //End of Shortest path.......

  while (digitalRead(leftFarSensor) == black || digitalRead(rightFarSensor) == black)
  {
    analogWrite(led, 0);
    delay(500);
    analogWrite(led, goRun);
    delay(500);
  }
  delay(500);

  //2nd Time Run.....
  delay(1000);
  replay();
  //Serial.println("done---Travel");
}

void turnLeft()
{
  //for Cross Shape and Left-Straignt Case
  while (digitalRead(centerSensor) == black || digitalRead(rightNearSensor) == black)
  {
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, goRun);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }

  //for T and Left Shape Case and
  while (digitalRead(centerSensor) == white || digitalRead(rightNearSensor) == white)
  {
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, goRun);
    analogWrite(rightMotor1, goRun);
    analogWrite(rightMotor2, 0);
    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }

  /*analogWrite(leftMotor1, 0);
  analogWrite(leftMotor2, goRun);
  analogWrite(rightMotor1, goRun);
  analogWrite(rightMotor2, 0);
  delay(50);*/

  //Shortest path.......
  if (replaystage)
  {
    path[pathLength] = 'L';
    pathLength++;
    if (path[pathLength - 2] == 'B')
    {
      shortPath();
    }
  }
  //End of Shortest path.......
}

void turnRight()
{
  while (digitalRead(leftNearSensor) == black  || digitalRead(centerSensor) == black)
  {
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, goRun);
    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }

  while (digitalRead(leftNearSensor) == white || digitalRead(centerSensor) == white)
  {
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, goRun);
    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }

  /*analogWrite(leftMotor1, goRun);
  analogWrite(leftMotor2, 0);
  analogWrite(rightMotor1, 0);
  analogWrite(rightMotor2, goRun);
  delay(50);*/

  //Shortest path.......
  if (replaystage)
  {
    path[pathLength] = 'R';
    pathLength++;
    if (path[pathLength - 2] == 'B')
    {
      shortPath();
    }
  }
  //End of Shortest path.......
}

void turnAround()
{
  analogWrite(leftMotor1, goRun);
  analogWrite(leftMotor2, 0);
  analogWrite(rightMotor1, goRun);
  analogWrite(rightMotor2, 0);
  delay(150);
  while (digitalRead(centerSensor) == white || digitalRead(leftNearSensor) == white)
  {
    analogWrite(leftMotor1, goRun);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, goRun);
    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }

  //Shortest path.......
  path[pathLength] = 'B';
  pathLength++;
  //End of Shortest path.......
  straight();
}

void shortPath() {
  if ((path[pathLength - 3] == 'L' && path[pathLength - 1] == 'R') || (path[pathLength - 3] == 'R' && path[pathLength - 1] == 'L')) {
    pathLength -= 3;
    path[pathLength] = 'B';
  }

  else if ((path[pathLength - 3] == 'L' && path[pathLength - 1] == 'S') || (path[pathLength - 3] == 'S' && path[pathLength - 1] == 'L')) {
    pathLength -= 3;
    path[pathLength] = 'R';
  }

  else if (path[pathLength - 3] == 'S' && path[pathLength - 1] == 'S') {
    pathLength -= 3;
    path[pathLength] = 'B';
  }

  else if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'L') {
    pathLength -= 3;
    path[pathLength] = 'S';
  }

  path[pathLength + 1] = 'D';
  path[pathLength + 2] = 'D';
  pathLength++;
}


void replay()
{
  readSensors();
  if ((leftFarReading == white && rightFarReading == white && centerReading == black) ||
      (leftFarReading == black && leftNearReading == black && centerReading == black && rightNearReading == white && rightFarReading == white) ||
      (leftFarReading == white && leftNearReading == white && centerReading == black && rightNearReading == black && rightFarReading == black))
  {
    straight();
  }

  else
  {
    if (path[readLength] == 'D')
    {
      analogWrite(leftMotor1, goRun);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor1, goRun);
      analogWrite(rightMotor2, 0);
      delay(500);
      analogWrite(leftMotor1, 0);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor1, 0);
      analogWrite(rightMotor2, 0);
      endMotion();
    }
    else if (path[readLength] == 'L')
    {
      analogWrite(leftMotor1, goRun);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor1, goRun);
      analogWrite(rightMotor2, 0);
      delay(littleForward+50);
      turnLeft();
    }
    else if (path[readLength] == 'R')
    {
      analogWrite(leftMotor1, goRun);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor1, goRun);
      analogWrite(rightMotor2, 0);
      delay(littleForward+50);
      turnRight();
    }
    else if (path[readLength] == 'S')
    {
      analogWrite(leftMotor1, goRun);
      analogWrite(leftMotor2, 0);
      analogWrite(rightMotor1, goRun);
      analogWrite(rightMotor2, 0);
      delay(littleForward+50);
      straight();
    }
    readLength++;
  }

  replay();
}

void endMotion() 
{
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(500);
  endMotion();
}
