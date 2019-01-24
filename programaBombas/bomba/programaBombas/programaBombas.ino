const int butMA = 7;
const int enB1 = 6, apaB1 = 5;
const int enB2 = 4, apaB2 = 3;
const int flotante = 2;

const int ledMan = 13, ledAuto = 12;
const int ledB1 = 11, ledB2 =10;
const int fallaB1 = 9, fallaB2 = 8;

bool cMA = true;
bool encendidoUno = false, encendidoDos = false;
bool cBomb = false, isChanged = false;

const float sensibilidad = 0.066;
const float seteo = 9.0;



void setup() {
  pinMode(butMA,INPUT);
  pinMode(enB1,INPUT);
  pinMode(apaB1,INPUT);
  pinMode(enB2,INPUT);
  pinMode(apaB2,INPUT);
  pinMode(flotante,INPUT);

  pinMode(ledMan,OUTPUT);
  pinMode(ledAuto,OUTPUT);
  pinMode(ledB1,OUTPUT);
  pinMode(ledB2,OUTPUT);
  pinMode(fallaB1,OUTPUT);
  pinMode(fallaB2,OUTPUT);

  
}

void loop() {
  
  medir();
  
  if(!digitalRead(fallaB2) && !digitalRead(fallaB2)){
    if(digitalRead(butMA)){
      if(cMA)
        cMA = false;
      else
        cMA = true;
      delay(500);
    }
  
    if(cMA)
      manual();
    else
      digitalWrite(ledMan,LOW);
  
    if(!cMA)
      automatico();
    else
      digitalWrite(ledAuto,LOW);
   }
    
}


void manual(){
  digitalWrite(ledMan,HIGH);
  
  if(digitalRead(enB1) && !encendidoDos)
    encendidoUno = true;
  
  if(digitalRead(apaB1) && encendidoUno)
    encendidoUno = false;

  if(digitalRead(enB2) && !encendidoUno)
    encendidoDos = true;
  
  if(digitalRead(apaB2) && encendidoDos)
    encendidoDos = false;
  

  if(encendidoUno)
    digitalWrite(ledB1,HIGH);
  else
    digitalWrite(ledB1,LOW);


  if(encendidoDos)
    digitalWrite(ledB2,HIGH);
  else
    digitalWrite(ledB2,LOW); 
    
}

void automatico(){
  digitalWrite(ledAuto,HIGH);


  if(digitalRead(flotante) && !isChanged){
    if(cBomb)
      cBomb = false;
    else
      cBomb = true;
    delay(200);
    isChanged = true;
  }


  if(cBomb && !digitalRead(flotante)){
    digitalWrite(ledB1,HIGH);
    isChanged = false;
  }else
    digitalWrite(ledB1,LOW);

  if(!cBomb && !digitalRead(flotante)){
    digitalWrite(ledB2,HIGH);
    isChanged = false;
  }else
    digitalWrite(ledB2,LOW);
  
    
}

void medir() {
  float vSensor1 = analogRead(A0) * (5.0 / 1023);
  float iSensor1 = (vSensor1 - 2.5) / sensibilidad;

  if (iSensor1 >= seteo) {
    digitalWrite(ledB1, LOW);
    digitalWrite(fallaB1, HIGH);
  }



  float vSensor2 = analogRead(A1) * (5.0 / 1023);
  float iSensor2 = (vSensor2 - 2.5) / sensibilidad;

  if (iSensor2 >= seteo) {
    digitalWrite(ledB2, LOW);
    digitalWrite(fallaB2, HIGH);

  }

}
