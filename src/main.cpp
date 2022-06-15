#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h> //Servo driver library
#include <SoftwareSerial.h>          //Serial communiction library

#define SERVOMIN 150  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 550  // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // Create pwm object
SoftwareSerial hc06(2, 3);

String message = "";

int brailleDots[] = {0, 0, 0, 0, 0, 0};   // Braille representation of captured letter
int servPositions[] = {0, 0, 0, 0, 0, 0}; // Stores servos' desired positions

// int captureLetter();                                    //Stores letter for conversion to Braille
void updateScreen();                                    // Updates LCD screen to show current letter
int degreesToPulse(int degrees);                        // convert degrees to pulse
void writePosition(int channel, int position);          // control servo position
void letterToBraille(char letter);                      // Converting chosen letter to its Braille version
void convert(int a, int b, int c, int d, int e, int f); //
void physicalRepresentation(int letterData[]);          // Fills array with servos' desired positions
void updateServos();                                    // Updates servos' positions

void setup()
{
  Serial.begin(9600);

  Serial.println("ENTER AT Commands:");
  // Initialize Bluetooth Serial Port
  hc06.begin(9600);

  pwm.begin();                // Initialize pwm
  pwm.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
  delay(10);
  writePosition(0, 90);
}

void loop()
{
  // Write data from HC06 to Serial Monitor
  if (hc06.available())
  {
    // Serial.write(hc06.read());
    message = hc06.readString();
    Serial.println(message);
  }

  if (message == "90")
  {
    writePosition(0, 90);
  }
  else if(message == "5"){
    writePosition(0, 95);
  }
  else if(message == "10"){
    writePosition(0, 100);
  }
  else if(message == "15"){
    writePosition(0, 105);
  }
  else if(message == "20"){
    writePosition(0, 110);
  }
  else if(message == "25"){
    writePosition(0, 115);
  }
  else if(message == "30"){
    writePosition(0, 120);
  }
  else if(message == "60"){
    writePosition(0, 150);
  }
  else if(message == "0"){
    writePosition(0, 0);
  }

  // Write from Serial Monitor to HC06
  //  if (Serial.available()) {
  //    hc06.write(Serial.read());
  //  }

  // if (captureLetter() == 1)
  // {
  //   updateScreen();
  //   letterToBraille(capturedLetter);
  //   physicalRepresentation(brailleLetter);
  // }
  // updateServos();
  // delay(1);
}

// int captureLetter()
// {
//   char key = keypad.getKey();

//   if (key)
//   {
//     switch (key)
//     {
//     case '1':
//       capturedLetter = 'A';
//       break;
//     case '2':
//       capturedLetter = 'B';
//       break;
//     case '3':
//       capturedLetter = 'C';
//       break;
//     case '4':
//       capturedLetter = 'D';
//       break;
//     case '5':
//       capturedLetter = 'E';
//       break;
//     case '6':
//       capturedLetter = 'F';
//       break;
//     case '7':
//       capturedLetter = 'G';
//       break;
//     case '8':
//       capturedLetter = 'H';
//       break;
//     case '9':
//       capturedLetter = 'I';
//       break;
//     default:
//       break;
//     }
//     return 1;
//   }
//   else
//     return 0;
// }

int degreesToPulse(int degrees)
{
  if (degrees >= 0 && degrees <= 180)
  {
    int pulseLenght = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
    return pulseLenght;
  }
  else
    return 0;
}

void writePosition(int channel, int newPosition)
{
  pwm.setPWM(channel, 0, degreesToPulse(newPosition));
}

void letterToBraille(char letter)
{
  switch (letter)
  {
  case 'A':
    convert(1, 0, 0, 0, 0, 0);
    break;
  case 'B':
    convert(1, 1, 0, 0, 0, 0);
    break;
  case 'C':
    convert(1, 0, 0, 1, 0, 0);
    break;
  case 'D':
    convert(1, 0, 0, 1, 1, 0);
    break;
  case 'E':
    convert(1, 0, 0, 0, 1, 0);
    break;
  case 'F':
    convert(1, 1, 0, 1, 0, 0);
    break;
  case 'G':
    convert(1, 1, 0, 1, 1, 0);
    break;
  case 'H':
    convert(1, 1, 0, 0, 1, 0);
    break;
  case 'I':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'J':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'K':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'L':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'M':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'N':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'O':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'P':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'Q':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'R':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'S':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'T':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'U':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'V':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'W':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'X':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'Y':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'Z':
    convert(0, 1, 0, 1, 0, 0);
    break;
  default:
    convert(0, 0, 0, 0, 0, 0);
    break;
  }
}

void physicalRepresentation(int letterData[])
{
  for (int i = 0; i < 6; i++)
  {
    if (letterData[i] == 1)
    {
      servPositions[i] = 90;
    }
    else
      servPositions[i] = 0;
  }
}

void updateServos()
{
  for (int i = 0; i < 6; i++)
  {
    writePosition(i, servPositions[i]);
  }
}

void convert(int a, int b, int c, int d, int e, int f)
{
  brailleDots[0] = a;
  brailleDots[1] = b;
  brailleDots[2] = c;
  brailleDots[3] = d;
  brailleDots[4] = e;
  brailleDots[5] = f;
}