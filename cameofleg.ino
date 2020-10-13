/*************************************************************

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
int m1Clock=D8;
int m1AntiClock=D7;
int m2Clock=D6;
int m2AntiClock=D5;
int gasPin=D4;
int pirPin=D3;
int proxiPin=D2;
int gun[]={D1,D0};
//char auth[] = "UHrA_Yvys81NDwK7ywlfnzfRo77r5ES_";
//char auth[] = "H5t8tTGr2yw_cU7CkvHT9VTPwA5A0ZC0";
char auth[]="8KXjpAeW4GQ0yCFwRXqdAYM-UUN7HFxN";
//char auth[] = "H2ajExldKt1umhBDhToljgeQePp_ojem";
// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "supritha";
//char pass[] = "12345678";
//char auth[]="WNw5AR0L_YhDCVK1JkNoqH9SkpVn_EuA";
//char ssid[]="yokay!";
//char pass[]="hello123";
char ssid[]="RDX";
char pass[]="rdx12345";
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(proxiPin,INPUT);
  pinMode(pirPin,INPUT);
  pinMode(gasPin,INPUT);
  pinMode(m1Clock,OUTPUT);
  pinMode(m1AntiClock,OUTPUT);
  pinMode(m2Clock,OUTPUT);
  pinMode(m2AntiClock,OUTPUT);
  pinMode(gun[0],OUTPUT);
  pinMode(gun[1],OUTPUT);
  Blynk.begin(auth, ssid, pass);  
}

void loop()
{
  Blynk.run();
  checkHumain();
  checkMattle();
  checkGas();
}

BLYNK_WRITE(V8){
  int val=param.asInt();
  if(val){
    digitalWrite(m1Clock,HIGH);
    digitalWrite(m2Clock,HIGH);
    Blynk.virtualWrite(V0,"Forward");
  }else{
    digitalWrite(m1Clock,LOW);
    digitalWrite(m2Clock,LOW);
    Blynk.virtualWrite(V0,".......");
  }
}


BLYNK_WRITE(V7){
  int val=param.asInt();
  if(val){
    digitalWrite(m1AntiClock,HIGH);
    digitalWrite(m2AntiClock,HIGH);
    Blynk.virtualWrite(V0,"Backward");
  }else{
    digitalWrite(m1AntiClock,LOW);
    digitalWrite(m2AntiClock,LOW);
    Blynk.virtualWrite(V0,"......");
  }
}


BLYNK_WRITE(V6){
  int val=param.asInt();
  if(val){
    digitalWrite(m1Clock,HIGH);
    //digitalWrite(m2Clock,HIGH);
    Blynk.virtualWrite(V0,"Right");
  }else{
    digitalWrite(m1Clock,LOW);
    Blynk.virtualWrite(V0,".....");
  }
}


BLYNK_WRITE(V5){
  int val=param.asInt();
  if(val){
    digitalWrite(m2Clock,HIGH);
    digitalWrite(m1Clock,LOW);
    Blynk.virtualWrite(V0,"Left");
  }else{
    digitalWrite(m2Clock,LOW);
  }
}

BLYNK_WRITE(V4){
  if(param.asInt()){
    digitalWrite(gun[0],HIGH);
    Blynk.virtualWrite(V20,"Clock");
  }else{
    digitalWrite(gun[0],LOW);
    Blynk.virtualWrite(V20,"......");
  }
}


BLYNK_WRITE(V3){
  if(param.asInt()){
    digitalWrite(gun[1],HIGH);
    Blynk.virtualWrite(V20,"anti_clock");
  }else{
    digitalWrite(gun[1],LOW);
    Blynk.virtualWrite(V20,"......");
  }
}

void checkHumain(){
  if(digitalRead(pirPin)){
    Blynk.virtualWrite(V11,"Detected");
  }else{
    Blynk.virtualWrite(V11,"........");
  }
}

void checkMattle(){
  if(digitalRead(proxiPin)){
    Blynk.virtualWrite(V12,"Detected");
  }else{
    Blynk.virtualWrite(V12,"........");
  }
  
}

void checkGas(){
  if(digitalRead(gasPin)==LOW){
    Blynk.virtualWrite(V13,"Detected");
  }else{
    Blynk.virtualWrite(V13,"........");
  }
}
