#include <SPI.h>
#include "Rfid.h"
#include "Nrf24.h"
#include <stdio.h> 
#include <Servo.h>

Servo servoMotor;

#define SS_RF 10
#define SS_RFID 8

#define RST_RFID 6

Nrf24 radiorf24(SS_RF,9);
Rfid rfid(7,SS_RFID);

int perros[2][4] = { {154,113,138,22} , {58,193,190,21} };


void setup() { 
   
  pinMode (SS_RF, OUTPUT);
  pinMode (SS_RFID, OUTPUT);
  
  digitalWrite(SS_RF, HIGH);
  digitalWrite(SS_RFID, HIGH);

  Serial.begin(9600); 
  SPI.begin();
  radiorf24.begin();
  rfid.begin();
}

void loop() {
  
  int perro_rf_index = validar(radiorf24.read());

  if(perro_rf_index >= 0){
    Serial.print("Se recibio RF el perro: ");
    Serial.println(perro_rf_index);
  }
  enableRFID();
  int perro_index = validar(rfid.read()); 
   
  if(perro_index >= 0){
    Serial.print("Se lee el perro: ");   
    Serial.println(perro_index);     
    int perro[4] = { perros[perro_index][0], perros[perro_index][1], perros[perro_index][2],perros[perro_index][3]};   
    
    enableRF();
    radiorf24.send(perro);     
  
  };
  
  delay(500);
}

int validar( int * lectura){
  int index = -1;
  for (int i = 0; i < 2; i++) {
      if(lectura[0] == perros[i][0] && lectura[1] == perros[i][1] && lectura[2] == perros[i][2] && lectura[3] == perros[i][3] ) index = i;
  };
  return index;
}

void enableRFID(){
}

void enableRF(){
}

void abrir(){
  servoMotor.write(180);
}

void cerrar() {  
  servoMotor.write(180);
}
