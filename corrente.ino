#include<SoftwareSerial.h>
#include "EmonLib.h"

SoftwareSerial Bluetooth(10,11);

//Variáveis do sensor de corrente 
EnergyMonitor SCT013;
int pinSCT = A0; 
int I_calibracao = 60;     
int tensao = 127;
int kwh;
int CSM;
int TR;
double Irms = 0 ;
float Tempo = 0;

void setup()
{
    Serial.begin(9600);
    Bluetooth.begin(9600);
    SCT013.current(pinSCT, I_calibracao);
}

void loop()
{
   consumoEnergia();
}

void consumoEnergia(){
   Irms = SCT013.calcIrms(1480);
   kwh = Irms*tensao*(Tempo/3600);
   CSM = TR*kwh;
   Tempo++;

    Serial.print("Corrente = ");
    Serial.print(Irms);
    Serial.println(" A");
    Serial.print("R$ ");
    
    Serial.print("Consumo = ");
    Serial.print(kwh);
    Serial.print(CSM);
    Serial.println(" Kwh");

    delay(500);
    Serial.print(".");
    delay(500);
    Serial.print(".");
    delay(500);
    Serial.println(".");
    delay(500);

    Bluetooth.print(Irms);
    Bluetooth.print("|");
    Bluetooth.print(kwh);
    Bluetooth.print("|");
}
