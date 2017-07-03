import processing.serial.*;
  Serial myPort;  // Create object from Serial class
  String val;     // Data received from the serial port

PShape base, shoulder, upArm, loArm, end;
float rotX, rotY;
float alpha, beta, charly, gamma;

void setup(){
  
    String portName = Serial.list()[0];
    myPort = new Serial(this, portName, 9600);  
  
    size(1350, 750, OPENGL);
    
    base = loadShape("r5.obj");
    shoulder = loadShape("r1.obj");
    upArm = loadShape("r2.obj");
    loArm = loadShape("r3.obj");
    end = loadShape("r4.obj");
    
    shoulder.disableStyle();
    upArm.disableStyle();
    loArm.disableStyle(); 
}

void draw(){ 
  
  int p = 0;
  
  if(myPort.available()>0){
    val = myPort.readStringUntil('\n');
  }
    if(val != null){
      val = trim(val);
      println(val);
      
      if(val.equals("PAUSE")){
        if(p == 0){
          p = 1;
        }
        else if(p == 1){
          p = 0;
        }
      }
      
   if(p == 0){
      if(val.equals("DROITE")){
       gamma = gamma - 0.01; 
      }
      else if(val.equals("GAUCHE")){
       gamma = gamma + 0.01; 
      }
      
      if(val.equals("AVANT")){
       alpha = alpha + 0.01;
      }
      else if(val.equals("ARRIERE")){
       alpha = alpha - 0.01;
      }
      
      if(val.equals("MONTER")){
       beta = beta + 0.01;
      }
      else if(val.equals("DESCENDRE")){
       beta = beta - 0.01; 
      }
      
      if(val.equals("SERRER")){
       charly = charly + 0.01;
      }
      else if(val.equals("DESSERRER")){
       charly = charly - 0.01; 
      }
      
      if(val.equals("AVANT DROITE")){
       alpha = alpha + 0.01;
       gamma = gamma - 0.01;
      }
      else if(val.equals("AVANT GAUCHE")){
       alpha = alpha + 0.01;
       gamma = gamma + 0.01;
      }
      
      if(val.equals("ARRIERE DROITE")){
       alpha = alpha - 0.01;
       gamma = gamma - 0.01;
      }
      else if(val.equals("ARRIERE GAUCHE")){
       alpha = alpha - 0.01;
       gamma = gamma + 0.01;
      }
   }
}
  
   background(32);
   smooth();
   lights(); 
   directionalLight(51, 102, 126, -1, 0, 0);
   
   noStroke();
   
   translate(width/2,height/2);
   rotateX(rotX);
   rotateY(-rotY);
   scale(-3);
    
   fill(#FFE308);  
   translate(0,-40,0);   
     shape(base);
     
   translate(0, 4, 0);
   rotateY(gamma);
     shape(shoulder);
      
   translate(0, 25, 0);
   rotateY(PI);
   rotateX(alpha);
     shape(upArm);
      
   translate(0, 0, 50);
   rotateY(PI);
   rotateX(beta);
     shape(loArm);
      
   translate(0, 0, -50);
   rotateY(PI);
   rotateX(charly);
     shape(end);
}

void mouseDragged(){
    rotY -= (mouseX - pmouseX) * 0.01;
    rotX -= (mouseY - pmouseY) * 0.01;
}