// SFF DOM reader
// by eoinpk.ek@gmail.com
// Created 5/10/2014

// This code prints the temperature and the optical power received value of an
// SFF compliant device with DOM support to a LCD display

#include <Wire.h>
#include <math.h>
#include <LiquidCrystal.h>

// LCD interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte EEPROM_ID = 0x51;
int A51[128];

void setup()
{
  Wire.begin();        
  Serial.begin(9600);  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
}

byte I2CEEPROM_Read (unsigned int address)
{
  byte data;
  Wire.beginTransmission(EEPROM_ID);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ID,(byte)1);
  while(Wire.available() == 0); data = Wire.read();
    return data;
}

void loop()
{
   for (int i = 96; i <106; i++)
  {
    A51[i] = I2CEEPROM_Read(i);
   }
  float temp = A51[96] + (float) A51[97]/256;
  float optical_rx = 10 * log10((float)(A51[104]<<8 | A51[105]) * 0.0001);
  lcd.setCursor(0, 0);
  lcd.print ("Temp = ");
  lcd.print (temp);
  lcd.print ((char)223); //degree symbol
  lcd.print ("C");
  lcd.setCursor (0, 1);
  lcd.print ("RX = ");
  lcd.print (optical_rx);
  lcd.print (" dBm");
    
delay(1000);
}
