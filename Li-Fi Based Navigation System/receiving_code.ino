#include <LiquidCrystal.h>
int ldr = A0;
int dly = 15;
int cutoff = 300;
int arr[4];
int c = 0;
int lcd_delay = 500;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Starting....");
  delay(1000);
  lcd.clear();
  Serial.begin(9600);
  pinMode(ldr, INPUT);
}

void loop() {
  ///
  // put your main code here, to run repeatedly:
  delay(1000);
  for (int i = 0; i < 4; i++) {
    arr[i] = rdldr(analogRead(ldr));
    delay(dly);
    Serial.println(arr[i]);
  }
  int  m = arr[0] + arr[1] + arr[2] + arr[3];
  if (m == 3) {
    Serial.println("3");
    lcd.print("Location:C");
    lcd.setCursor(0, 0);
    //  delay(lcd_delay);
    //  lcd.clear();
  }
  else {
    if (arr[0] != arr[2]) {
      Serial.println("2");
      lcd.print("Location:B");
      lcd.setCursor(0, 0);
      //    delay(lcd_delay);
      //  lcd.clear();
    }
    else if (arr[1] != arr[3]) {
      Serial.println("2");
      lcd.print("Location:C");
      lcd.setCursor(0, 0);
      //        delay(lcd_delay);
      //  lcd.clear();
    }
    else {
      Serial.println("1");
      lcd.print("Location:A");
      lcd.setCursor(0, 0);
      //        delay(lcd_delay);
      //  lcd.clear();
    }
  }
}

int rdldr(int d) {
  if (d < cutoff)
    return 1;
  else
    return 0;
}
