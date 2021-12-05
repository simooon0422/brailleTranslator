#include <Arduino.h>
#include <LiquidCrystal.h>           //LCD library
#include <Keypad.h>                  //Keypad library
#include <Adafruit_PWMServoDriver.h> //Servo driver library

#define SERVOMIN 150  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 550  // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

const byte ROWS = 3; //number of rows
const byte COLS = 3; //number of columns

byte rowPins[ROWS] = {10, 9, 8};   //rows' pins
byte colPins[COLS] = {13, 12, 11}; //columns' pins

char keys[ROWS][COLS] = { //map keypad
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize keypad
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);                                    //Create LCD screen object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();                //Create pwm object

char capturedLetter = '0'; //Variable for converting signal from keypad to letter

int brailleLetter[] = {0, 0, 0, 0, 0, 0}; //Braille representation of captured letter
int servPositions[] = {0, 0, 0, 0, 0, 0}; //Stores servos' desired positions

int captureLetter();                                    //Stores letter for conversion to Braille
void updateScreen();                                    //Updates LCD screen to show current letter
int degreesToPulse(int degrees);                        //convert degrees to pulse
void writePosition(int channel, int position);          //control servo position
void letterToBraille(char letter);                      //Converting chosen letter to its Braille version
void convert(int a, int b, int c, int d, int e, int f); //
void physicalRepresentation(int letterData[]);          //Fills array with servos' desired positions
void updateServos();                                    //Updates servos' positions

void setup()
{
  Serial.begin(9600);

  pwm.begin();                //Initialize pwm
  pwm.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
  delay(10);

  lcd.begin(16, 2);    //Declare type of LCD
  lcd.setCursor(0, 0); //Set cursor
  lcd.print("Hello");  //Show text
  lcd.setCursor(0, 1); //Set cursor
  lcd.print("World!"); //Show text
}

void loop()
{
  if (captureLetter() == 1)
  {
    updateScreen();
    letterToBraille(capturedLetter);
    physicalRepresentation(brailleLetter);
  }
  updateServos();
  delay(1);
}

int captureLetter()
{
  char key = keypad.getKey();

  if (key)
  {
    switch (key)
    {
    case '1':
      capturedLetter = 'A';
      break;
    case '2':
      capturedLetter = 'B';
      break;
    case '3':
      capturedLetter = 'C';
      break;
    case '4':
      capturedLetter = 'D';
      break;
    case '5':
      capturedLetter = 'E';
      break;
    case '6':
      capturedLetter = 'F';
      break;
    case '7':
      capturedLetter = 'G';
      break;
    case '8':
      capturedLetter = 'H';
      break;
    case '9':
      capturedLetter = 'I';
      break;
    default:
      break;
    }
    return 1;
  }
  else
    return 0;
}

void updateScreen()
{
  lcd.clear();                  //Clear screen
  lcd.setCursor(0, 0);          //Set cursor
  lcd.print("Wybrana litera:"); //Show text
  lcd.setCursor(0, 1);          //Set cursor
  lcd.print(capturedLetter);    //Show text
}

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
  brailleLetter[0] = a;
  brailleLetter[1] = b;
  brailleLetter[2] = c;
  brailleLetter[3] = d;
  brailleLetter[4] = e;
  brailleLetter[5] = f;
}