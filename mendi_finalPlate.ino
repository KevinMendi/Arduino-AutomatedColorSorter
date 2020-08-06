#include "Servo.h"
#include "Wire.h"
#include "Adafruit_TCS34725.h"

const int redPos = 160;
const int orangePos = 130;
const int yellowPos = 100;
const int greenPos = 70;
const int bluePos = 30;
const int nonePos = 0;

Servo myservo;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

void setup()
{
Serial.begin(9600);
Serial.println("Makerblog.at - MuMs Color Sensor");

if(tcs.begin())
{
Serial.println("Sensor gefunded");
}
else
{
Serial.println("TCS34725 nicht gefunden .. Ablauf gestoppt !");
while(1);
}

myservo.attach(3);
myservo.write(0);
delay(1000);

}

void loop()
{
uint16_t clearcol, red, green, blue;
float average, r, g, b;
delay(100);
tcs.getRawData(&red, &green, &blue, &clearcol);

average = (red+green+blue)/3;
r = red/average;
g = green/average;
b = blue/average;


Serial.print("\tClear:"); Serial.print(clearcol);
Serial.print("\tRed:"); Serial.print(r);
Serial.print("\tGreen"); Serial.print(g);
Serial.print("\tBlue"); Serial.print(b);

if((r > 1.4) && (g > 1.3) && (b < 1.2))
{
Serial.print("\tROT");
myservo.write(redPos);
}
else if((r < 0.95) && (g > 1.3) && (b < 1.2))
{
Serial.print("\tGRUEN");
myservo.write(greenPos);

}
else if((r < 0.8) && (g < 1.2) && (b > 1.2))

{
Serial.print("\tBLAU");
myservo.write(bluePos);

}
else if ((r > 1.15) && (g > 1.15) && (b < 0.7))
{
Serial.print("\tGELB");
myservo.write(yellowPos);

}
else if ((r > 1.4) && (g < 1.0) && (b < 0.7))
{
Serial.print("t\ORANGE");
myservo.write(orangePos);

}
else 
{
Serial.print("\tNICHT ERKANNI");
//myservo.write(nonePose);
}


Serial.print("");
delay(100);




}

