#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

float celsius = 0.0;
int sensorValue;
float volts;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

byte simbolo[]={
  B01110,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup()
{
  
  pinMode(A0, INPUT);
  Serial.begin(9600);
  analogReference(INTERNAL); //Analog Reference = 1.1 V

  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.createChar(0, simbolo);
  // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
 
 }

float sensor_volts() {   
  sensorValue = analogRead (A0);
  volts = (sensorValue * 1.1)/ 1023.0;
return volts;}


void loop()
{
  celsius = 100.0*sensor_volts();
  
  Serial.print(celsius);
  Serial.print(" c, ");
  Serial.print(sensor_volts());
  Serial.println(" V");
  
  lcd.setCursor(1,0);
  lcd.print("Temperatura");
  lcd.setCursor (13, 0);
  lcd.write(byte(0));
  lcd.setCursor (14, 0);
  lcd.print ("C:");
  lcd.setCursor(2,1);
  lcd.print(celsius);
  
  delay(1000); 
}

//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
