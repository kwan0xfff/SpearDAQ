#include <SPI.h>
#include <SD.h>

unsigned long time;
const int chipSelect = 4;
int pressure = 1;
int flowH = 2;
int flowK = 3;
int temp = 4;
float psi = 0.0;
float reading = 0;
int x = 0;
float H = 0;
float K = 0;
float kero = 0;
float hyd = 0;
float T = 0;
float temperature = 0;
File dataFile;

float psicoeff;         // 1/1.6384

void setup()
{
  psicoeff = 1.0/1.6384;

  pinMode(pressure, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(flowH, OUTPUT);
  pinMode(flowK, OUTPUT);
  pinMode(temp,OUTPUT);
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
  dataFile = SD.open("pressure.txt", O_CREAT | O_WRITE | O_APPEND);
  while (!dataFile)
  {
    ;
  }
}

void loop()
{
  time = millis();
  reading = analogRead(pressure);
  H = analogRead(flowH);
  K = analogRead(flowK);
  T = analogRead(temp);

  // reading: 921.6 @ 4.5V -> 500 psi
  // reading: 102.4 @ 0.5V ->   0 psi
  psi = psicoeff*(reading-102.4);
  kero = .0355073*K-.2924;
  hyd = .046377*H-.006668;
  temperature = 1.2207*T;
  if (dataFile)
  {
    dataFile.println();
    dataFile.print(time/1000.000);
    dataFile.write('\t\t');
    dataFile.print(psi);
    dataFile.write('\t\t');
    dataFile.print(kero);
    dataFile.write('\t\t');
    dataFile.print(hyd);
    dataFile.write('\t\t');
    dataFile.print(temperature);
    dataFile.flush();
  }
  else
  {
     Serial.println("Error opening text file");
  }
}
