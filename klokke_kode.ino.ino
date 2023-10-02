#include <Wire.h> //Wire-bibliotek som lar arduinonene kommunisere med hverandre med I2C
#define SENSOR 9 //Definerer slave I2C adressen

int slideSwitch = 3; // Slide-switch pin
int redLED = 4;// LED pin
int greenLED = 5;// LED pin
int Buzz = 6; // Buzzer pinnen
int vibrator = 7; //Pinnen til vibrasjonsmotoren


void setup() {

//Blir med i I2C bussen
  Wire.begin();
//Setter pinmode for pinnene
  pinMode(slideSwitch, INPUT);
  pinMode(Buzz, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(vibrator, OUTPUT);
//Starter seriell kommunikasjon med PC for enklere debugging
  Serial.begin(9600);
}


void loop() {
  
//Skrur paa komponentene i klokken om slideSwitchens read er HIGH, altsaa om man skrur den paa
  
  int slideVal = digitalRead(slideSwitch);
  
  if (slideVal == HIGH) {
//Naar klokken er paa, lyser det groenne LED-lyset
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);

    Serial.println("Write data to sensor");
//Her starter vi overfoeringen mellom sensor og armbaandsuret
    Wire.beginTransmission(SENSOR);
    Wire.write(0);
    Wire.endTransmission();

    Serial.println("Recieve data");

//Her ber vi om én byte fra sensoren
    Wire.requestFrom(SENSOR, 1);

 //Leser av dataen som har blitt sendt fra sensoren, som vil vaere 1 om den har blitt utloest, og 0 hvis ikke
    int val;
    while (Wire.available()) {
      val = Wire.read();
    }

 //Om sensoren er utloest og val er 1, skrus det roede lyset på, buzzeren piper og vibratoren vibrerer
    if (val == 1) {
        digitalWrite(redLED, HIGH); // Turn red LED ON
        digitalWrite(greenLED, LOW);
        digitalWrite(Buzz, HIGH); // Turn Buzzer ON
        digitalWrite(vibrator, HIGH);
        tone(Buzz, 2000); // Send 1KHz sound signal...
        delay(1000);
        
        Serial.println("Movement Detected"); 
    }
 //Hvis ikke, gjoer den ingenting, lyser kun groent
    else if (val == 0) {
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      digitalWrite(vibrator, LOW);
      noTone(Buzz);
      digitalWrite(Buzz, LOW);
      Serial.println("Movement not Detected");
    }
     
  }

//Skrur av komponentene om slideswitchen er paa av
  else {
     digitalWrite(redLED, LOW);
     digitalWrite(greenLED, LOW);
     digitalWrite(vibrator, LOW);
     noTone(Buzz);
     digitalWrite(Buzz, LOW);
  }

}
