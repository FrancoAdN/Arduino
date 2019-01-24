const int ledBomba1 = 2;
const int ledBomba2 = 3;
const int ledFalla1 = 4;
const int ledFalla2 = 5;
const int botonB1 = 6;
const int botonB2 = 7;
const int releB1 = 9;
const int releB2 = 8;
const int ledAuto = 10;
const int botonFlotante = 11;
const int llaveSelectora = 12;
const int ledMan = 13;
const float sensibilidad = 0.066;
const float seteo = 9.0;


int stateLlave;
int stateBotonB1;
int stateBotonB2;
int stateFlotante;
int contador=0;
int lastButtonState=0;






void setup() {
  pinMode(botonB1, INPUT);
  pinMode(botonB2, INPUT);
  pinMode(botonFlotante, INPUT);
  pinMode(llaveSelectora, INPUT);

  pinMode(ledBomba1, OUTPUT);
  pinMode(ledBomba2, OUTPUT);
  pinMode(ledFalla1, OUTPUT);
  pinMode(ledFalla2, OUTPUT);
  pinMode(releB1, OUTPUT);
  pinMode(releB2, OUTPUT);
  pinMode(ledAuto, OUTPUT);
  pinMode(ledMan, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);


  Serial.begin(9600);
}



void automatico() {
  digitalWrite(ledAuto, HIGH);
  stateFlotante = digitalRead(botonFlotante);
  medir();


  if(stateFlotante != lastButtonState){
    if(stateFlotante == HIGH){
      if(contador == 0){
        contador = 1;
      }else{
        contador = 0;
      }
    }
  }

  lastButtonState= stateFlotante;
  if( contador == 1 && stateFlotante==HIGH && digitalRead(ledFalla1)==LOW && digitalRead(ledBomba2)==LOW){
    digitalWrite(ledBomba1,HIGH);
    digitalWrite(releB1,HIGH);
    delay(200);
  }else{
    digitalWrite(ledBomba1,LOW);
    digitalWrite(releB1,LOW);
    delay(200);
  }



 if( contador == 0 && stateFlotante == HIGH && digitalRead(ledFalla2)==LOW && digitalRead(ledBomba1)==LOW){
  digitalWrite(ledBomba2,HIGH);
  digitalWrite(releB2,HIGH);
  delay(200);
 }else{
  digitalWrite(ledBomba2,LOW);
  digitalWrite(releB2,LOW);
  delay(200);
 }






}






void manual() {       //función para modo manual

  digitalWrite(ledMan, HIGH);
  stateBotonB1 = digitalRead(botonB1);
  stateBotonB2 = digitalRead(botonB2);

  if (stateBotonB1 == HIGH && stateBotonB2 == LOW) {

    medir();
    digitalWrite(releB1, HIGH);
    digitalWrite(ledBomba1, HIGH);
  } else {
    digitalWrite(releB1,LOW);
    digitalWrite(ledBomba1,LOW);
  }

  if (stateBotonB2 == HIGH && stateBotonB1 == LOW) {

    medir();
    digitalWrite(releB2, HIGH);
    digitalWrite(ledBomba2, HIGH);
  } else {
    digitalWrite(releB2, LOW);
    digitalWrite(ledBomba2, LOW);
  }


}







void medir() {
  float vSensor1 = analogRead(A0) * (5.0 / 1023);
  float iSensor1 = (vSensor1 - 2.5) / sensibilidad;

  if (iSensor1 >= seteo) {
    digitalWrite(releB1, LOW);
    digitalWrite(ledBomba1, LOW);
    digitalWrite(ledFalla1, HIGH);
  }



  float vSensor2 = analogRead(A1) * (5.0 / 1023);
  float iSensor2 = (vSensor2 - 2.5) / sensibilidad;

  if (iSensor2 >= seteo) {
    digitalWrite(releB2, LOW);
    digitalWrite(ledBomba1, LOW);
    digitalWrite(ledFalla2, HIGH);

  }

}









void loop() {


  stateLlave = digitalRead(llaveSelectora);

  if (stateLlave == HIGH) {
    automatico();
  } else {
    digitalWrite(ledAuto, LOW);
  }



  if (stateLlave == LOW) {
    manual();
  } else {
    digitalWrite(ledMan, LOW);
  }










}
