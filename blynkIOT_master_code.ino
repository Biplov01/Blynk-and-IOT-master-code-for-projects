#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

char auth[] = "R8SYsf1UqRby1dH0KR6Ev9ctB0oEeLui";

/* WiFi credentials */
char ssid[] = "AndroidAP3DEC";
char pass[] = "electroniclinic";
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int msensor = A0; // moisture sensor is connected with the analog pin A0 of ESP8266
int msvalue = 0; // moisture sensor value 
int setmoisture;
int mspercent; // moisture value in percentage
int Relay = D0; // you can connect a dc or ac water pump
int buzzer = D4;

void setup()
{
  Serial.begin(115200);
      Blynk.begin(auth, ssid, pass);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  // initialize the sensor

  pinMode(msensor, INPUT);
  pinMode(Relay, OUTPUT);
  pinMode(buzzer, OUTPUT); 
}

void loop()
{
   Blynk.run();

 
msvalue = analogRead(msensor);
  mspercent = map(msvalue,0,1023,100,0); // To display the soil moisture value in percentage
  
 display.clearDisplay();
  display.setCursor(10,0);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
 display.print("SM:"+String(mspercent)+"%");
    display.setCursor(10,30);
  display.setTextSize(2);
 display.print("SV:"+String(setmoisture));

  display.display();
 
 Blynk.virtualWrite(V1,mspercent);

 if (mspercent<setmoisture )
  {
    Blynk.notify("Soil moisture decreased!!!"); 
    digitalWrite(buzzer,HIGH);
  }
  else
  {
        digitalWrite(buzzer,LOW);

    }
delay(1000);
}
BLYNK_WRITE(V2) // To set soil moisture
{
   setmoisture = param.asInt(); // assigning incoming value from pin V2 to a variable
    
}