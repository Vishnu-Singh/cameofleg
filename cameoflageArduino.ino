const int s0 = 13;  
const int s1 = 12;  
const int s2 = 11;  
const int s3 = 10;  
const int out = 9;   

const int gunClock=8;
const int gunAntiClock=7;
const int leftNoise=6;
const int rightNoise=5;

// LED pins connected to Arduino
int redLed = 8;  
int greenLed = 7;  
int blueLed = 6;
// Variables  
int red;  
int green;  
int blue;  

int ir=A0;
int buzzer=A1;
void setup()   
{  
  Serial.begin(9600); 
  pinMode(gunClock,OUTPUT);
  pinMode(gunAntiClock,OUTPUT);
  pinMode(leftNoise,OUTPUT);
  pinMode(rightNoise,OUTPUT);
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  pinMode(redLed, OUTPUT);  
  pinMode(greenLed, OUTPUT);  
  pinMode(blueLed, OUTPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH); 
  pinMode(buzzer,OUTPUT);
  pinMode(ir,INPUT);
}

void loop() 
{  
  color(); 
  check_object();
  Serial.print("R Intensity:");  
  Serial.print(red, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(blue, DEC);  
  //Serial.println();  

  if (red < blue && red < green)
  {  
   Serial.println(" - (Red Color)");  
   digitalWrite(redLed, HIGH); // Turn RED LED ON 
   digitalWrite(greenLed, LOW);  
   digitalWrite(blueLed, LOW);  
  }  

  else if (blue < red && blue < green)   
  {  
   Serial.println(" - (Blue Color)");  
   digitalWrite(redLed, LOW);  
   digitalWrite(greenLed, LOW);  
   digitalWrite(blueLed, HIGH); // Turn BLUE LED ON  
  }  

  else if (green < red && green < blue)  
  {  
   Serial.println(" - (Green Color)");  
   digitalWrite(redLed, LOW);  
   digitalWrite(greenLed, HIGH); // Turn GREEN LED ON 
   digitalWrite(blueLed, LOW);  
  }  
  else{
  Serial.println();  
  }
  delay(300);    
  digitalWrite(redLed, LOW);  
  digitalWrite(greenLed, LOW);  
  digitalWrite(blueLed, LOW);  
} 

    


   
    
void color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}

void checkLeftNoise(){
  if(digitalRead(leftNoise)==LOW){
    digitalWrite(gunClock,HIGH);
    delay(500);
  }else{
    digitalWrite(gunClock,LOW);
  }
}

void checkRightNoise(){
  
  if(digitalRead(rightNoise)==LOW){
    digitalWrite(gunAntiClock,HIGH);
    delay(500);
  }else{
    digitalWrite(gunAntiClock,LOW);
  }
}

void check_object(){
  if(digitalRead(ir)==HIGH){
    digitalWrite(buzzer,HIGH);
  }else{
    digitalWrite(buzzer,LOW);
  }
}
