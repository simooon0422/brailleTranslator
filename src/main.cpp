#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h> //Servo driver library
#include <SoftwareSerial.h>          //Serial communiction library

#define SERVOMIN 150  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 550  // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // Create pwm object
SoftwareSerial hc06(2, 3);

String message = "";

int messageLength = 0;

int brailleDots[] = {0, 0, 0, 0, 0, 0};                // Braille representation of captured letter
int servPositions[] = {90, 90, 90, 90, 90, 90};        // Stores servos' desired positions
int servInitPositions[] = {90, 90, 90, 90, 90, 90};    // Stores servos' initial positions
int servMovePositions[] = {105, 105, 105, 75, 75, 75}; // Stores max positions that servos will move to

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
  updateServos();
  // writePosition(0, 90);
}

void loop()
{
  // Write data from HC06 to Serial Monitor
  if (hc06.available())
  {
    // Serial.write(hc06.read());
    message = hc06.readString();
    message = message + ".";
    Serial.println(message);

    // Convert String message to Char array for letterToBraille function
    messageLength = message.length();
    Serial.println(messageLength);
    char messageBuf[messageLength];
    message.toCharArray(messageBuf, messageLength);

    letterToBraille(messageBuf[0]);
    physicalRepresentation(brailleDots);
    // Serial.println(brailleDots[0]);
    // Serial.println(brailleDots[1]);
    // Serial.println(brailleDots[2]);
    // Serial.println(brailleDots[3]);
    // Serial.println(brailleDots[4]);
    // Serial.println(brailleDots[5]);
    // Serial.println(messageBuf[0]);
    // Serial.println(messageBuf[10]);
    // delay(100);
  }

  updateServos();
  delay(1);

  // if (message == "90")
  // {
  //   writePosition(0, 90);
  // }
  // else if(message == "5"){
  //   writePosition(0, 95);
  // }
  // else if(message == "10"){
  //   writePosition(0, 100);
  // }
  // else if(message == "15"){
  //   writePosition(0, 105);
  // }
  // else if(message == "20"){
  //   writePosition(0, 110);
  // }
  // else if(message == "25"){
  //   writePosition(0, 115);
  // }
  // else if(message == "30"){
  //   writePosition(0, 120);
  // }
  // else if(message == "60"){
  //   writePosition(0, 150);
  // }
  // else if(message == "0"){
  //   writePosition(0, 0);
  // }

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
  case 'a':
  case 'A':
    convert(1, 0, 0, 0, 0, 0);
    break;
  case 'b':
  case 'B':
    convert(1, 1, 0, 0, 0, 0);
    break;
  case 'c':
  case 'C':
    convert(1, 0, 0, 1, 0, 0);
    break;
  case 'd':
  case 'D':
    convert(1, 0, 0, 1, 1, 0);
    break;
  case 'e':
  case 'E':
    convert(1, 0, 0, 0, 1, 0);
    break;
  case 'f':
  case 'F':
    convert(1, 1, 0, 1, 0, 0);
    break;
  case 'g':
  case 'G':
    convert(1, 1, 0, 1, 1, 0);
    break;
  case 'h':
  case 'H':
    convert(1, 1, 0, 0, 1, 0);
    break;
  case 'i':
  case 'I':
    convert(0, 1, 0, 1, 0, 0);
    break;
  case 'j':
  case 'J':
    convert(0, 1, 0, 1, 1, 0);
    break;
  case 'k':
  case 'K':
    convert(1, 0, 1, 0, 0, 0);
    break;
  case 'l':
  case 'L':
    convert(1, 1, 1, 0, 0, 0);
    break;
  case 'm':
  case 'M':
    convert(1, 0, 1, 1, 0, 0);
    break;
  case 'n':
  case 'N':
    convert(1, 0, 1, 1, 1, 0);
    break;
  case 'o':
  case 'O':
    convert(1, 0, 1, 0, 1, 0);
    break;
  case 'p':
  case 'P':
    convert(1, 1, 1, 1, 0, 0);
    break;
  case 'q':
  case 'Q':
    convert(1, 1, 1, 1, 1, 0);
    break;
  case 'r':
  case 'R':
    convert(1, 1, 1, 0, 1, 0);
    break;
  case 's':
  case 'S':
    convert(0, 1, 1, 1, 0, 0);
    break;
  case 't':
  case 'T':
    convert(0, 1, 1, 1, 1, 0);
    break;
  case 'u':
  case 'U':
    convert(1, 0, 1, 0, 0, 1);
    break;
  case 'v':
  case 'V':
    convert(1, 1, 1, 0, 0, 1);
    break;
  case 'w':
  case 'W':
    convert(0, 1, 0, 1, 1, 1);
    break;
  case 'x':
  case 'X':
    convert(1, 0, 1, 1, 0, 1);
    break;
  case 'y':
  case 'Y':
    convert(1, 0, 1, 1, 1, 1);
    break;
  case 'z':
  case 'Z':
    convert(1, 0, 1, 0, 1, 1);
    break;

  //Special characters
  case '!': //Ą
    convert(1, 0, 0, 0, 0, 1);
    break;
  case '@': //Ć
    convert(1, 0, 0, 1, 0, 1);
    break;
  case '#': //Ę
    convert(1, 0, 0, 0, 1, 1);
    break;
  case '$': //Ł
    convert(1, 1, 0, 0, 0, 1);
    break;
  case '%': //Ń
    convert(1, 0, 0, 1, 1, 1);
    break;
  case '^': //Ś
    convert(0, 1, 0, 1, 0, 1);
    break;
  case '&': //Ó
    convert(0, 0, 1, 1, 0, 1);
    break;
  case '*': //Ż
    convert(1, 1, 1, 1, 0, 1);
    break;
  case '(': //Ź
    convert(0, 1, 1, 1, 0, 1);
    break;

  default:
    convert(0, 0, 0, 0, 0, 0);
    break;
  }
}

// void physicalRepresentation(int letterData[])
// {
//   for (int i = 0; i < 6; i++)
//   {
//     if (letterData[i] == 1)
//     {
//       servPositions[i] = 60;
//     }
//     else
//       servPositions[i] = 90;
//   }
// }
void physicalRepresentation(int letterData[])
{
  for (int i = 0; i < 6; i++)
  {
    if (letterData[i] == 1)
    {
      servPositions[i] = servMovePositions[i];
    }
    else
      servPositions[i] = servInitPositions[i];
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