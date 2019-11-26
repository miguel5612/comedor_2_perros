#include <SPI.h>
#include "Rfid.h"
#include "Nrf24.h"
#include <stdio.h> 
#include <Servo.h>

Servo servoMotor;

#define SS_RF 9
#define SS_RFID 10

//#define RST_RFID 6 -> Este cable ahora va a tierra.
Nrf24 radiorf24(SS_RF,109); //9
Rfid rfid(107,SS_RFID); //7

int perros[2][4] = { {154,113,138,22} , {58,193,190,21} };

void setup() { 

  //Configuracion de entradas y salidas
  pinMode (SS_RF, OUTPUT); //Declaro las variables como salidas
  pinMode (SS_RFID, OUTPUT); //Declaro las variables como salidas

  //Deshabilito ambos para que ninguno hable.
  digitalWrite(SS_RF, HIGH); //Con esto deshabilito el RF - Logica invertida
  digitalWrite(SS_RFID, LOW); // Con esto deshabilito el RFid - Logica normal

  // Inicializacion de los protocolos de comunicacion
  Serial.begin(115200); //Inicializo la comunicacion serie a 115200 baudios
  SPI.begin(); // Inicializo la comunicacion SPI

  // Inicializo los modulos de comunicaciones
  Serial.println("Inicializando RF24");enableRF();radiorf24.begin(); 
  Serial.println("Inicializando RFid");enableRFID();rfid.begin();

  //Mensaje de salida exitosa del setup
  Serial.println("He finalizado con exito las configuraciones");
}

void loop() {
  
  int perro_rf_index = validar(radiorf24.read());

  if(perro_rf_index >= 0){
    Serial.print("Se recibio RF el perro: ");
    Serial.println(perro_rf_index + 1);
  }
  enableRFID();
  int perro_index = validar(rfid.read()); 
   
  if(perro_index >= 0){
    Serial.print("Se lee el perro: ");   
    Serial.println(perro_index + 1);     
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
  digitalWrite(SS_RF, HIGH); //Con esto deshabilito el RF - Logica invertida
  digitalWrite(SS_RFID, HIGH); // Con esto habilito el RFid - Logica normal
}

void enableRF(){
  digitalWrite(SS_RF, LOW); //Con esto habilito el RF - Logica invertida
  digitalWrite(SS_RFID, HIGH); // Con esto deshabilito el RFid - Logica normal
}

void abrir(){
  servoMotor.write(180);
}

void cerrar() {  
  servoMotor.write(180);
}
