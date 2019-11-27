#include <SPI.h>
#include "Rfid.h"
#include "Nrf24.h"
#include <stdio.h> 
#include <Servo.h>

Servo servoMotor;

#define CE_RF 9
#define CSN_RF 8
#define CSN_RFID 10
#define IRQ_PIN 2

//#define RST_RFID 6 -> Este cable ahora va a tierra.
Nrf24 radiorf24(CE_RF,CSN_RF); //9
Rfid rfid(CE_RF,CSN_RFID); //7

int perros[2][4] =  { {154,113,138,22} , {58,193,190,21} };

bool ignorarPerro1 = false;
bool ignorarPerro2 = false;

unsigned long tiempoPerro1;
unsigned long tiempoPerro2;

void setup() { 

  //Configuracion de entradas y salidas
  pinMode (CSN_RF, OUTPUT); //Declaro las variables como salidas
  pinMode (CSN_RFID, OUTPUT); //Declaro las variables como salidas

  //Deshabilito ambos para que ninguno hable.
  digitalWrite(CSN_RF, LOW); //Con esto deshabilito el RF - Logica invertida
  digitalWrite(CSN_RFID, HIGH); // Con esto deshabilito el RFid - Logica normal

  // Inicializacion de los protocolos de comunicacion
  Serial.begin(115200); //Inicializo la comunicacion serie a 115200 baudios
  SPI.begin(); // Inicializo la comunicacion SPI

  // Inicializo los modulos de comunicaciones
  Serial.println("Inicializando RF24");enableRF();radiorf24.begin(); 
  Serial.println("Inicializando RFid");enableRFID();rfid.begin();


  servoMotor.attach(2);
  
  //Mensaje de salida exitosa del setup
  Serial.println("He finalizado con exito las configuraciones");
  cerrar();
  delay(500);
  abrir();
}

void loop() {
  enableRF();
  delay(5);
  int perro_rf_index = validar(radiorf24.read());

  if(perro_rf_index >= 0){
    if(perro_rf_index == 0) ignorarPerro1 = true;
    if(perro_rf_index == 1) ignorarPerro2 = true;
  }

  Serial.print("primer perro: ");Serial.println(ignorarPerro1);
  Serial.print("segundo perro: ");Serial.println(ignorarPerro2);
  enableRFID();
  delay(5);
  int perro_index = validar(rfid.read()); 
   
  if(perro_index >= 0){
    Serial.print("Se lee el perro: ");   
    Serial.println(perro_index + 1);     
    int perro[4] = { perros[perro_index][0], perros[perro_index][1], perros[perro_index][2],perros[perro_index][3]};   
    
    if(perro_index == 0 & !ignorarPerro1)
    {
      Serial.println("Sirviendo comida perro1");
      abrirServo();
      ignorarPerro1 = true;
      tiempoPerro1 = millis();
    }
    if(perro_index == 1 & !ignorarPerro2)
    {
      Serial.println("Sirviendo comida perro2");
      abrirServo();
      ignorarPerro2 =  true;
      tiempoPerro2 = millis();
    }
    enableRF();
    radiorf24.send(perro);     
  
  };

  if(millis() - tiempoPerro1 > 300000) 
  {
    ignorarPerro1 = false;
  }
  
  if(millis() - tiempoPerro2 > 300000) 
  {
    ignorarPerro2 = false;
  }
  
  delay(500);
  
}

void abrirServo()
{
  Serial.println("Abriendo puerta");
  abrir();
  delay(5000);
  cerrar();
}
int validar( int * lectura){
  int index = -1;
  for (int i = 0; i < 2; i++) {
      if(lectura[0] == perros[i][0] && lectura[1] == perros[i][1] && lectura[2] == perros[i][2] && lectura[3] == perros[i][3] ) index = i;
  };
  //if(index == 0 & !ignorarPerro1) {pinMode(3, INPUT); if(digitalRead(3)) ignorarPerro1 = true;}
  //if(index == 1 & !ignorarPerro2) {pinMode(4, INPUT); if(digitalRead(4)) ignorarPerro2 = true;}
  return index;
}

void enableRFID(){
  digitalWrite(CSN_RF, HIGH); //Con esto deshabilito el RF - Logica invertida
  digitalWrite(CSN_RFID, HIGH); // Con esto habilito el RFid - Logica normal
}

void enableRF(){
  digitalWrite(CSN_RF, LOW); //Con esto habilito el RF - Logica invertida
  digitalWrite(CSN_RFID, HIGH); // Con esto deshabilito el RFid - Logica normal
}

void abrir(){
  servoMotor.write(90);
}

void cerrar() {  
  servoMotor.write(0);
}
