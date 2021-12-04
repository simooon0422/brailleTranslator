#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Keypad.h>


const byte ROWS = 3; // ile wierszy
const byte COLS = 3; //ile kolumn
 
byte rowPins[ROWS] = {10, 9, 8}; //piny wierszy
byte colPins[COLS] = {13, 12, 11}; //piny kolum
 
char keys[ROWS][COLS] = { //mapowanie klawiatury
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};
 
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //inicjalizacja klawiatury
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Hello"); //Wyświetlenie tekstu
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print("World!"); //Wyświetlenie tekstu
}

void loop() {
  char klawisz = klawiatura.getKey();
  
  if (klawisz){
    Serial.println(klawisz);
  }
}