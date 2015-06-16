#include <SoftwareSerial.h>

SoftwareSerial bluetooth(13, 12); // RX, TX

int mdf = 2; //motor direito pra frente
int mdt = 3; //motor direito pra trás
int mef = 4; //motor esquerdo pra frente
int met = 5; //motor esquerdo pra trás
int ag = 6; //abrir garra
int fg = 7; //fechar garra

void setup(){
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  //Saidas
  pinMode(mdf,OUTPUT);
  pinMode(mdt,OUTPUT);
  pinMode(mef,OUTPUT);
  pinMode(met,OUTPUT);
  pinMode(ag,OUTPUT);
  pinMode(fg,OUTPUT);
  

  // set the data rate for the SoftwareSerial port
  bluetooth.begin(9600);
  Serial.println("Iniciando o Robô REX...");
}

// run over and over
void loop(){
  if (bluetooth.available()){
        char leitura = bluetooth.read();
        Serial.println(leitura);
        
          //CARRO PRA FRENTE
          if(leitura == 'F'){
            digitalWrite(mdf,HIGH);
            digitalWrite(mef,HIGH);
            delay(30);
            digitalWrite(mdf,LOW);
            digitalWrite(mef,LOW);            
          }else{
            digitalWrite(mdf,LOW);
            digitalWrite(mef,LOW); 
          }  
          
          //CARRO PRA TRAS
          if(leitura == 'B'){
            digitalWrite(mdt,HIGH);
            digitalWrite(met,HIGH);
            delay(30);
            digitalWrite(mdt,LOW);
            digitalWrite(met,LOW);
          }
            else{
            digitalWrite(mdt,LOW);
            digitalWrite(met,LOW);
            }
          
          //CARRO ESQUERDA - FRENTE
          if(leitura == 'G'){
            digitalWrite(mdf,HIGH);
            delay(30);
            digitalWrite(mdf,LOW);
          }
            else{
              digitalWrite(mdf,LOW);
            }
            
          //CARRO DIREITA - FRENTE
          if(leitura == 'I'){
            digitalWrite(mef,HIGH);
            delay(30);
            digitalWrite(mef,LOW);
          }
            else{
              digitalWrite(mef,LOW);
          }
          
           //CARRO ESQUERDA - TRAS
          if(leitura == 'J'){
            digitalWrite(mdt,HIGH);
            delay(30);
            digitalWrite(mdt,LOW);
          }
            else{
              digitalWrite(mdt,LOW);
          }
          
          //CARRO DIREITA - TRAS
          if(leitura == 'H'){
            digitalWrite(met,HIGH);
            delay(30);
            digitalWrite(met,LOW);
          }
            else{
              digitalWrite(met,LOW);
          }


          //GARRA ABRE
          if(leitura == 'w'){
            digitalWrite(ag,HIGH);
            delay(30);
          }else{
          }

          if(leitura == 'W'){
            digitalWrite(ag,LOW);
            delay(30);
          }else{
          }
          
          //GARRA FECHA          
          if(leitura == 'u'){
            digitalWrite(fg,HIGH);
            delay(30);
               }else{
          }
          if(leitura == 'U'){
            digitalWrite(fg,LOW);
            delay(30);
            }else{
          }
      
        leitura = 'x';
  }
if (Serial.available())
    bluetooth.write(Serial.read());
    
}
                                                                                            