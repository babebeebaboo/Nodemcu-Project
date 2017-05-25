#include <IRremoteESP8266.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int RECV_PIN = D4; //an IR detector connected to D4
IRrecv irrecv(RECV_PIN);
decode_results results;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  lcd.begin();
  lcd.backlight();
}
void loop() {
  if (irrecv.decode(&results)) {
    lcd.setCursor(0, 0);
    if(results.value != 4294967295){
      lcd.clear();
      Serial.println(results.value);
    lcd.println(results.value);
    }
    
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
