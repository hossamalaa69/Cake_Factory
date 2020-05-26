int eggsValve = 9;
int vanillaValve = 10;
int sugarValve = 11;
int flourValve = 12;
int armMotor = A1;
unsigned long t;
int cycle[4][4]={{1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1}};
int mixerMotor[4]={0,1,2,3};
int productionMotor[4]={4,5,6,7};
int decorMotor[2] = {A4,A5};
int cycle2[4][2]={{1,1},{0,1},{0,0},{1,0}};

int red = A2;
int yellow = A3;
int color = red;
void setup() {
pinMode(A0,INPUT);   //switches
pinMode(8,OUTPUT);    //heater
pinMode(red,OUTPUT);
pinMode(yellow,OUTPUT);

pinMode(eggsValve, OUTPUT);
pinMode(vanillaValve, OUTPUT);
pinMode(sugarValve, OUTPUT);
pinMode(flourValve, OUTPUT);
pinMode(armMotor, OUTPUT);

for(int i=0;i<4;i++)
    pinMode(mixerMotor[i],OUTPUT);
for(int i=0;i<4;i++)
    pinMode(productionMotor[i],OUTPUT);
for(int i=0;i<2;i++)
    pinMode(decorMotor[i],OUTPUT);

Serial.begin(9600);
servoPulse(eggsValve,0);
servoPulse(vanillaValve,0);
servoPulse(sugarValve,0);
servoPulse(flourValve,0);
servoPulse(armMotor,0);

digitalWrite(8,LOW);
}

void loop(){
cakeMaking();
cakeBaking();
cakeDecoration();
}

void cakeDecoration(){
int key = analogRead(A0);  
while(!key)
  key = analogRead(A0);
  
if(key == 1021)
  Decor1();
else if(key == 1002)
  Decor2();
else if(key == 929)
  Decor3();
else if(key == 852)
  Decor4();

servoPulse(armMotor,0);
  
}

void Decor4(){
  Serial.println("Key 4");  

  //outer decoration
  servoPulse(armMotor,0);
  for(int k=0;k<18;k++){
    digitalWrite(color,HIGH);
    for(int i=0;i<12;i+=4)
      stepMotor2(decorMotor,60);

    digitalWrite(color,LOW);
    delay(150);
    stepMotor2(decorMotor,60);
    stepMotor2(decorMotor,60);
    
    if(color == red) color = yellow;
    else  color = red;  
   }

  //middle decoration
  servoPulse(armMotor,80);
  delay(300);
  color = red;
  digitalWrite(color,HIGH);
  for(int i=0 ;i<360;i+=4)
     stepMotor2(decorMotor,60);
     
  //inner decoration
  servoPulse(armMotor,110);   
  delay(500);
  digitalWrite(color,LOW);
  delay(200);
}
void Decor3(){
  Serial.println("Key 3");
  //outer decoration
  servoPulse(armMotor,0);
  for(int k=0;k<18;k++){
    digitalWrite(red,HIGH);
    delay(100);
    for(int i=0;i<12;i+=4)
      stepMotor2(decorMotor,60);

    digitalWrite(red,LOW);
    delay(100);
    stepMotor2(decorMotor,60);
    stepMotor2(decorMotor,60);
    
   }
  //Inner decoration
  servoPulse(armMotor,110);
  delay(300);
  digitalWrite(yellow,HIGH);
  delay(500);
  digitalWrite(yellow,LOW);
  delay(200);
}

void Decor2(){
  Serial.println("Key 2");

  //outer decoration
  servoPulse(armMotor,0);
  for(int k=0;k<4;k++){
    digitalWrite(red,HIGH);
    delay(50);
    for(int i=0;i<44;i+=4)
      stepMotor2(decorMotor,60);
    
    digitalWrite(red,LOW);
    delay(50);
    for(int i=0;i<44;i+=4)
      stepMotor2(decorMotor,60);      
  }
  stepMotor2(decorMotor,60);
  stepMotor2(decorMotor,60);
  
  //inner decoration
  servoPulse(armMotor,70);
  for(int k=0;k<4;k++){
    digitalWrite(yellow,LOW);
    delay(50);
    for(int i=0;i<44;i+=4)
      stepMotor2(decorMotor,60);
    
    digitalWrite(yellow,HIGH);
    delay(50);
    for(int i=0;i<44;i+=4)
      stepMotor2(decorMotor,60);      
  }
  stepMotor2(decorMotor,60);
  stepMotor2(decorMotor,60);
  digitalWrite(yellow,LOW);
  delay(200);
}


void Decor1(){
  Serial.println("Key 1");
  
  servoPulse(armMotor,0);
  digitalWrite(red,HIGH);
  for(int i=0;i<360;i+=4)
    stepMotor2(decorMotor,60);
  digitalWrite(red,LOW);
  
  servoPulse(armMotor,70);
  delay(200);  
  digitalWrite(yellow,HIGH);
  for(int i=0;i<360;i+=4)
    stepMotor2(decorMotor,60);
  digitalWrite(yellow,LOW);  
  delay(200);
}

void cakeMaking(){

  //eggs valve part
  servoPulse(eggsValve,180);
  delay(500);
  servoPulse(eggsValve,0);  

  
  t = millis(); 
  for(int i=0;i<1800;i+=4)
      stepMotor(mixerMotor,1050);
  Serial.println(millis()-t);
  Serial.println("expected to be 500ms");

   
  //vanilla valve part
  servoPulse(vanillaValve,180);
  t = millis(); 
  for(int i=0;i<1440;i+=4)
      stepMotor(mixerMotor,1050);
  Serial.println(millis()-t);
  Serial.println("expected to be 400ms");    
  servoPulse(vanillaValve,0);


  //sugar valve part
  servoPulse(sugarValve,180);
  delay(200);
  servoPulse(sugarValve,0);
  t = millis(); 
  for(int i=0;i<3600;i+=4)
      stepMotor(mixerMotor,1050);
  Serial.println(millis()-t);
  Serial.println("expected to be 1000ms");     

  for(int j=0;j<3;j++){
    servoPulse(flourValve,180);
    delay(100);
    servoPulse(flourValve,0);     
    t = millis();
    for(int i=0;i<1440;i+=4)
      stepMotor(mixerMotor,2100);   //Now, rpm of stepper is doubled
    Serial.println(millis()-t);
    Serial.println("expected to be 800ms");    
   }
}

void cakeBaking(){
  for(int i=0;i<360;i+=4)
    stepMotor(productionMotor,10000);  

  digitalWrite(8,HIGH);
  delay(1000);
  digitalWrite(8,LOW);

  for(int i=0;i<360;i+=4)
    stepMotor(productionMotor,10000);  

  delay(1000);
}

void servoPulse (int servoPin, int angle)
{
  int pwm = angle * 9 + 500;
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(servoPin, LOW);
}


void stepMotor2(int Motor[], unsigned long rpm_delay){       
      for(int i=0;i<4;i++)
          for(int j=0;j<2;j++)
             digitalWrite(Motor[j],cycle[i][j]);
      delay(rpm_delay);      
}

void stepMotor(int Motor[], unsigned long rpm_delay){       
      for(int i=0;i<4;i++)
          for(int j=0;j<4;j++)
             digitalWrite(Motor[j],cycle[i][j]);
      delayMicroseconds(rpm_delay);      
}
