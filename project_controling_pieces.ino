#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <Wire.h>
int counter1 = 0, counter2 = 0, counter3, counter4, counter5, counter6, counter7, counter8;
volatile int adress1 = 0x30, adress2 = 0x31, adress3 = 0x32, adress4 = 0x33, adress5 = 0x34, adress6 = 0x35, adress7 = 0x36, adress8 = 0x37;
char casea[4], caseb[4], casec[4], cased[4], casee[4], casef[4], caseg[4], caseh[4];
int MUX_S = 12;
String str;
int mux_tab[3] = { 9, 10, 11 };
byte Rowpin[4] = { 2, 3, 4, 5 };
byte colpin[3] = { 6, 7, 8 };
char keypadpress[4][3] = {
  { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' }, { '*', '0', '#' }
};
Keypad clavier = Keypad(makeKeymap(keypadpress), Rowpin, colpin, 4, 3);
LiquidCrystal_I2C lcd(0x27, 16, 2);
char key = clavier.getKey();

void lcd_initiation() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("hello");
  delay(500);
  lcd.clear();
}
void mux_fillout(int ii, int kk, int jj) {
  digitalWrite(mux_tab[0], ii);
  digitalWrite(mux_tab[1], kk);
  digitalWrite(mux_tab[2], jj);
}
void Saturation(int t) {
 
      digitalWrite(13, t);
      delay(200);
digitalWrite(13,0);    
  }

void conversion_tostr(int k, char case1[4]) {
  str = String(k);
  str.toCharArray(case1, 4);
}
void reset(volatile int adress, int *i) {
  i = EEPROM.read(adress);
  i = sizeof(int);
  *i = 0;
  EEPROM.put(adress, *i);
}

void setup() {
  Serial.begin(9600);
  lcd_initiation();
  pinMode(13, OUTPUT);
  pinMode(MUX_S, INPUT_PULLUP);
  for (int g = 0; g < 4; g++) {
    pinMode(Rowpin[g], OUTPUT);
  }
  for (int h = 0; h < 3; h++) {
    pinMode(colpin[h], INPUT_PULLUP);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(mux_tab[i], OUTPUT);
  }
}

void loop() {

  int etat1, etat2, etat3, etat4, etat5, etat6, etat7, etat8;
  digitalWrite(13, LOW);
  char key = clavier.getKey();
  while (1) {
    delay(30);
    lcd.setCursor(1, 0);
    lcd.print("chain l:");
    mux_fillout(0, 0, 0);
    int y = digitalRead(MUX_S);

    if ((y == 1) && (etat1 != y)) {
      counter1++;
      conversion_tostr(counter1, casea);
      EEPROM.write(adress1, casea);
      lcd.println(casea);
      delay(100);
    }
    etat1 = y;

    if (counter1 >= 10) {
      Saturation(1);
    }

    if ((key == '0') && (counter1 >= 10)) {
      counter1 = 0;
      conversion_tostr(counter1, casea);
      reset(adress1, counter1);
      lcd.println(casea);
      Saturation(0);
      delay(30);
    }
    delay(50);
    mux_fillout(1, 0, 0);
    y = digitalRead(MUX_S);
    lcd.setCursor(1, 1);
    lcd.print("chain 2:");
    if ((y == 1) && (etat2 != y)) {
      counter2++;
      conversion_tostr(counter2, caseb);
      EEPROM.write(adress2, caseb);
      lcd.print(caseb);
      delay(50);
    }
    etat2 = y;

    if (counter2 >= 10) {
      Saturation(1);
    }
    key = clavier.getKey();
    if ((key == '1') && (counter2 >= 10)) {
      counter2 = 0;
      reset(adress2, counter2);
      conversion_tostr(counter2, caseb);
      lcd.println(caseb);
      Saturation(0);
      delay(30);
    }
    delay(30);
    mux_fillout(0, 1, 0);
    delay(30);
    mux_fillout(1, 1, 0);
    delay(30);
    mux_fillout(0, 0, 1);
    delay(30);
    mux_fillout(1, 0, 1);
    delay(30);
    mux_fillout(0, 1, 1);
    delay(30);
    mux_fillout(1, 1, 1);
  }
}