#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
float pressure = 1;
float psi = 0;
float reading = 0;
int x = 0;

void setup()
{
  pinMode(pressure, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect))
  {
    Serial.println("Card failed");
    return;
  }
  Serial.println("Card initialized.");
}

void loop()
{
  reading = analogRead(pressure);
  // reading: 921.6 @ 4.5V -> 500 psi
  // reading: 102.4 @ 0.5V ->   0 psi
  psi = (1/1.6384)*(reading-102.4);
  File dataFile = SD.open("pressure.txt", FILE_WRITE);
  while (!dataFile)
  {
    ;
  }
  if (dataFile)
  {
    dataFile.println(psi);
    dataFile.close();

    Serial.write("pressure: ");
    Serial.print(psi);
    Serial.print('\t');
    Serial.write("psi");
    Serial.print('\t');
    Serial.write("reading: ");
    Serial.print(reading);
    Serial.print('\n');
  }
  else
  {
     Serial.println("Error opening text file");
  }
  delay(50);
}
