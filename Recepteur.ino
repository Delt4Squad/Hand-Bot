#include <VirtualWire.h>

const char* MSGA = "A"; //Avant
const char* MSGB = "B"; //Arriere
const char* MSGC = "C"; //Gauche
const char* MSGD = "D"; //Droite

const char* MSGE = "E"; //Avant + Droite
const char* MSGF = "F"; //Avant + Gauche
const char* MSGG = "G"; //Arriere + Droite
const char* MSGH = "H"; //Arriere + Gauche

const char* MSGP = "P"; //Retourner -> Pause
const char* MSGZ = "Z"; //Rien

const char* MSGI = "I"; //Monter
const char* MSGJ = "J"; //Descendre

const char* MSGK = "K"; //Serrer
const char* MSGL = "L"; //Desserer

void setup() {
  Serial.begin(9600);
  
  vw_setup(2000);
  vw_rx_start();
}

void loop() {
  byte message[VW_MAX_MESSAGE_LEN];
  byte taille_message = VW_MAX_MESSAGE_LEN;

  vw_wait_rx();

  if (vw_get_message(message, &taille_message)) {
    if (strcmp((char*) message, MSGA) == 0){
      Serial.println("AVANT");
    } 
    else if (strcmp((char*) message, MSGB) == 0) {
      Serial.println("ARRIERE");
    } 
    else if (strcmp((char*) message, MSGC) == 0) {
      Serial.println("GAUCHE");
    }
    else if (strcmp((char*) message, MSGD) == 0) {
      Serial.println("DROITE");
    }
    else if (strcmp((char*) message, MSGE) == 0) {
      Serial.println("AVANT DROITE");
    }
    else if (strcmp((char*) message, MSGF) == 0) {
      Serial.println("AVANT GAUCHE");
    } 
    else if (strcmp((char*) message, MSGG) == 0) {
      Serial.println("ARRIERE DROITE");
    }
    else if (strcmp((char*) message, MSGH) == 0) {
      Serial.println("ARRIERE GAUCHE");
    }   
    else if (strcmp((char*) message, MSGI) == 0) {
      Serial.println("MONTER");
    }
    else if (strcmp((char*) message, MSGJ) == 0) {
      Serial.println("DESCENDRE");
    }
    else if (strcmp((char*) message, MSGK) == 0) {
      Serial.println("SERRER");
    }
    else if (strcmp((char*) message, MSGL) == 0) {
      Serial.println("DESSERRER");
    }
    else if (strcmp((char*) message, MSGP) == 0) {
      Serial.println("PAUSE");
    }
    else if (strcmp((char*) message, MSGZ) == 0) {
      Serial.println("---");
    }
    else{
      Serial.println("Message corrompu");
    }
  }

}
