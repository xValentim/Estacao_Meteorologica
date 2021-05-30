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

#include <DHT.h>; //INCLUSÃO DE BIBLIOTECA
#define DHTPIN 2 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)

int lm35 = 0; // porta A0
int ldr = 1; // porta A1
float vcc_3p3v = 3.3;
float R = 200000.0; // ohms
float a_dht22_T = 1;
float b_dht22_T = 0;
float a_dht22_H = 1;
float b_dht22_H = 0;
float a_lm35;
float b_lm35;



DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
 
void setup()
{
  Serial.begin(9600); //INICIALIZA A SERIAL
  dht.begin(); //INICIALIZA A FUNÇÃO
  
  pinMode(A0, INPUT);
  analogReference(INTERNAL); //Analog Reference = 1.1 V
  lcd.init();                      // initialize the lcd 
  //lcd.init();
  lcd.createChar(0, simbolo);
  // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
  delay(2000); //INTERVALO DE 2 SEGUNDO ANTES DE INICIAR
}
void loop()
{
  //float temperatura_sem_calibragem = get_temperatura_lm35(tensao_na_porta(lm35));
  float sensorValue = analogRead(1);
  float v_out_ldr = (sensorValue / 1023) * 1.1;
  float R_ldr = (v_out_ldr * R) / (vcc_3p3v - v_out_ldr);

  
  float humidade = calibragem_dht22(dht.readHumidity(), a_dht22_H, b_dht22_H);
  float temperatura_dht22 = calibragem_dht22(dht.readTemperature(), a_dht22_T, b_dht22_T);
  //float temperatura = calibragem_lm35(temperatura_sem_calibragem, a_lm35, b_lm35);
  float luminosidade = converte_luminosidade(R_ldr);
  
  Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(humidade); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
  Serial.print(" %"); //IMPRIME O TEXTO NA SERIAL 
  Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(temperatura_dht22); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  Serial.print("*C"); //IMPRIME O TEXTO NA SERIAL
  Serial.print(" / Luminosidade: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(luminosidade); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("Lux"); //IMPRIME O TEXTO NA SERIAL
  
  lcd.setCursor(0,1);
  lcd.print("Temp.:");
  lcd.setCursor (7, 1);
  lcd.print(temperatura_dht22);
  lcd.setCursor (13, 1);
  lcd.write(byte(0));
  lcd.setCursor (14, 1);
  lcd.print ("C");

  delay(1000);
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Humi.:");
  lcd.setCursor (7, 1);
  lcd.print(humidade);
  lcd.setCursor (12, 1);
  lcd.print(" %");

  delay(1000);
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Lumi.:");
  lcd.setCursor (7, 1);
  lcd.print(luminosidade);
  lcd.setCursor (12, 1);
  lcd.print(" Lux");
  
  delay(1000); //INTERVALO DE 2 SEGUNDOS * NÃO DIMINUIR ESSE VALOR
  lcd.clear();
}
