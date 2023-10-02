#include <Wire.h> //Wire-bibliotek som lar arduinonene kommunisere med hverandre med
#define SENSOR 9 //Definerer slave I2C adressen


//Setter verdien som skal sendes til armbaandsuret til 0
int val = 0;

//Pinnen til PIR-sensoren
int PIR = 3; 


void setup() {

  pinMode(PIR, INPUT);
  
  //Blir med i I2C bussen og definerer hva som skal skje paa forespoersel fra master-enhet
  Wire.begin(SENSOR);
  Wire.onRequest(requestEvent);
  
  //Starter seriell kommunikasjon med PC for aa lettere kunne debugge
  Serial.begin(9600);

}

//Her definerer vi handlingen som vil skjer dersom det kommer en forespoersel fra master-enheten
//Sier at val er PIR-sensorens read, om denne er HIGH så blir response 1
//og om den er LOW blir den 0. Sender deretter response til armbaandsuret.

void requestEvent() {
  byte response;
    
  val = digitalRead(PIR);
  if (val == HIGH) {
    response = 1;
  } else {
    response = 0;
  }

  Wire.write(response);

  Serial.println("Request event");
}

void loop() {
  

}
