#define BLYNK_TEMPLATE_ID "TMPLQicelPb8"
#define BLYNK_DEVICE_NAME "security device"
#define BLYNK_AUTH_TOKEN "1sYTqd4mtCdbQPDo7z4EV--ZZ504Mks7"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define echoPin D5
#define trigPin D6


int ir= D0;
int buzzer = D7;
long duration;
int distance;

char ssid[] = "hariv";
char pass[] = "hariv1234";

int i= 0;
int u = 0;
char auth[] = BLYNK_AUTH_TOKEN;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void write2()//ultrasonic
{
  // Set incoming value from pin V0 to a variable
  int value = ultrasonic();

  if (value<=15)
  {
    lcd.setCursor(0, 1);
    lcd.print("Intruder- R1");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    u=1;
  }
  else
  {
    lcd.setCursor(10, 1);
    lcd.print("  ");
    u=0;
  }
  // Update state
  Blynk.virtualWrite(V2, value);
}

void write1()//ir
{
  // Set incoming value from pin V0 to a variable
  int value = !digitalRead(ir);
  lcd.setCursor(7, 0);
  lcd.print("IR- "+ String(value));
  Serial.print("IR - ");
  Serial.println(value);
    // Update state
  if (value==1)
  {
    lcd.setCursor(0, 1);
    lcd.print("Intruder-");
    lcd.setCursor(13, 1);
    lcd.print("R2");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    i=1;
  }
  else
  {
    lcd.setCursor(13, 1);
    lcd.print("  ");
    i=0;
  }
  Blynk.virtualWrite(V1, value);
}
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(ir,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
}

void loop()
{
  Blynk.run();

  write2();
  write1();

  if(i==0 && u==0)
  {
   lcd.setCursor(0, 1);
   lcd.print("                ");
   lcd.setCursor(0, 1);
   lcd.print("Safe");
  }
  delay(1000);
}

int ultrasonic()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  
  duration=pulseIn(echoPin,HIGH);
  distance=(duration*0.034/2);
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm ");
  lcd.setCursor(0, 0);
  lcd.print("       ");
  lcd.setCursor(0, 0);
  lcd.print(String(distance)+" cm");
  return distance;
}
