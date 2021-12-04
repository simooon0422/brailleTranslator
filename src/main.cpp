#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Adafruit_PWMServoDriver.h>


#define SERVOMIN 150                // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 550                // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50               // Analog servos run at ~50 Hz updates

const byte ROWS = 3; //number of rows
const byte COLS = 3; //number of columns

byte rowPins[ROWS] = {10, 9, 8};   //rows pins
byte colPins[COLS] = {13, 12, 11}; //columns pins

char keys[ROWS][COLS] = { //map keypad
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize keypad
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);                                    //Create LCD screen object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

char capturedLetter = '0';

int captureLetter();
void updateScreen();
int degreesToPulse(int degrees);               //convert degrees to pulse
void writePosition(int channel, int position); //control servo position

void setup()
{
  Serial.begin(9600);

  pwm.begin();
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
  writePosition(0, 30); //Simple test of the circuit

  if (captureLetter() == 1)
  {
    updateScreen();
  }
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