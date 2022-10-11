// this constant won't change:
int counter = 1; //initial counter state
int modebutton = 2;  // The Mode Select Button
//int HEARTRATE = 3;  // Heartrate measurement Power Control
//int OXYGEN = 4;  // Oxygen measurement Power Control
//int TEMPERATURE = 5;
int delayTime;  //declaration of the time it takes to delay the change
int mode;
int LO_PINN = 11;
int LO_PINP = 10;
void ecg();
void oximeter();
void temperature();


Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <Adafruit_MLX90614.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
 #define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    Serial.println("Beat!");
}
 

void setup() {
    pinMode(modebutton, INPUT);  //button for mode
    //pinMode(HEARTRATE, OUTPUT);  //pin for heartrate
   // pinMode(OXYGEN, OUTPUT);  //pin for oxygen
   // pinMode(TEMPERATURE, OUTPUT);  //pin for temperature
    Serial.begin(9600);
    pinMode(10, INPUT); // Setup for leads off detection LO +
pinMode(11, INPUT); // Setup for leads off detection LO -

    
    Serial.print("Initializing pulse oximeter..");
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);

    
  while (!Serial);

  Serial.println("Adafruit MLX90614 test");

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

  Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
  Serial.println("================================================");
}

void loop() {
  mode=digitalRead(modebutton); //reads the output of the modebutton 
  if (mode == 1)
  { 
    delay(200);
    counter+=1; //adds the counter +1 if the mode button is high
    if (counter == 4)
    {
      counter = 1;//if the counter goes above 3, it resets it to mode 11
    }
  }

//different mode changes depending on the counter number
  if (counter ==1){
   // digitalWrite(HEARTRATE, HIGH);
    //digitalWrite(OXYGEN, LOW);
   // digitalWrite(TEMPERATURE, LOW);
   oximeter();
}
  else if(counter == 2){
    //digitalWrite(HEARTRATE, LOW);
   // digitalWrite(OXYGEN, HIGH);
   // digitalWrite(TEMPERATURE, LOW);
   ecg();
   delay(10);

}
//Wait for a bit to keep serial data from saturating

  
  else if( counter == 3){
   // digitalWrite(HEARTRATE, LOW);
    //digitalWrite(OXYGEN, LOW);
    //digitalWrite(TEMPERATURE, HIGH);
    temperature();


  }
  Serial.println(mode);
  delay(2000);
}
