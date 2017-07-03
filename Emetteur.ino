#include <VirtualWire.h>
#include<Wire.h>

int btH;
int btP;

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp;
int AccelX,AccelY,AccelZ;

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

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

void setup() {
  vw_setup(2000);
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  pinMode(2,INPUT);
  pinMode(3,INPUT);
}

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
 
void loop() {

  btH = digitalRead(2);
  btP = digitalRead(3);
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true); 
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();
  AccelX=map(AcX,-16384,16383,-10,10);
  AccelY=map(AcY,-16384,16383,-10,10);
  AccelZ=map(AcZ,-16384,16383,-10,10);
  
  byte message[VW_MAX_MESSAGE_LEN]; 
/*************************************************************************/
if(btH == HIGH){
  if(AccelX>=4){
    vw_send((byte*) MSGJ, strlen(MSGJ) + 1);  //Descendre
    vw_wait_tx();
  }
  else if(AccelX<=-5){
    vw_send((byte*) MSGI, strlen(MSGI) + 1);  //Monter
    vw_wait_tx();
  }
  else{
    vw_send((byte*) MSGZ, strlen(MSGZ) + 1);  //Rien
    vw_wait_tx();
  }
}
/*************************************************************************/
else if(btP == HIGH){
  if(AccelX>=4){
    vw_send((byte*) MSGK, strlen(MSGK) + 1);  //Serrer
    vw_wait_tx();
  }
  else if(AccelX<=-5){
    vw_send((byte*) MSGL, strlen(MSGL) + 1);  //Deserrer
    vw_wait_tx();
  }
  else{
    vw_send((byte*) MSGZ, strlen(MSGZ) + 1);  //Rien
    vw_wait_tx();
  }
}
/*************************************************************************/
else{
  if(AccelZ<=-7){
    vw_send((byte*) MSGP, strlen(MSGP) + 1);  //A l envers
    vw_wait_tx();
  }
  else if(AccelX>=4 & AccelY<=-5){
    vw_send((byte*) MSGE, strlen(MSGE) + 1);  //Avant droite
    vw_wait_tx();
  }
  else if(AccelX>=4 & AccelY>=3){
    vw_send((byte*) MSGF, strlen(MSGF) + 1);  //Avant gauche
    vw_wait_tx();
  }
  else if(AccelX<=-5 & AccelY<=-5){
    vw_send((byte*) MSGG, strlen(MSGG) + 1);  //Arriere droite
    vw_wait_tx();
  }
  else if(AccelX<=-5 & AccelY>=3){
    vw_send((byte*) MSGH, strlen(MSGH) + 1);  //Arriere gauche
    vw_wait_tx();
  }
  else if(AccelX>=4){
    vw_send((byte*) MSGA, strlen(MSGA) + 1);  //Avant
    vw_wait_tx();
  }
  else if(AccelX<=-5){
    vw_send((byte*) MSGB, strlen(MSGB) + 1);  //Arriere
    vw_wait_tx();
  }
  else if(AccelY>=3){
    vw_send((byte*) MSGC, strlen(MSGC) + 1);  //Gauche
    vw_wait_tx();
  }
  else if(AccelY<=-5){
    vw_send((byte*) MSGD, strlen(MSGD) + 1);  //Droite
    vw_wait_tx();
  }
  else{
    vw_send((byte*) MSGZ, strlen(MSGZ) + 1);  //Rien
    vw_wait_tx();
  }
  delay(50);
}
}
