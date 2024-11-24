#include <ArduinoJson.h>  
#include <Servo.h>         

Servo baseMotor;    
Servo arm1Motor;
Servo arm2Motor;
Servo clawMotor;        

void setup() {
  Serial.begin(9600);     
  baseMotor.attach(8);    
  arm1Motor.attach(9);      
  arm2Motor.attach(10);      
  clawMotor.attach(11);      
  
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  
    
    StaticJsonDocument<200> doc;
    
    DeserializationError error = deserializeJson(doc, input);
    
    if (error) {
      Serial.println("Failed to parse JSON");
      return;
    }
    
    int basemotor = doc["basemotor"]; 
    int arm1motor = doc["arm1"];
    int arm2motor = doc["arm2"];
    int claw = doc["claw"];



    Serial.print("Received motor speed: ");
    Serial.println(basemotor);


    baseMotor.write(basemotor);
    arm1Motor.write(arm1motor);
    arm2Motor.write(arm2motor);
    clawMotor.write(claw);

    Serial.println("Data received and processed.");
  }
}