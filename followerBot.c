#include <Ultrasonic.h>

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

int LED = 13;

Ultrasonic sensor1(10, 9);
Ultrasonic sensor3(3,2);
Ultrasonic sensor2(12, 11);

void moveFront();
void moveBack();
void moveRight();
void moveLeft();
void _stop();

float sensorDireito();
float sensorEsquerdo();
float sensorMeio();


int distanciaDireita;
int distanciaEsquerda;
int distanciaMeio;

static int MAX_NEAR = 40;
static int MAX_FAR = 60;
static int MAX_SIGN = 100;
  
void setup()
{
  Serial.begin(9600);
  //Define os pinos como saida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED, OUTPUT);

}
  
void loop() {

  sensorDireita();
  sensorEsquerda();
  sensorMeio();

  
  if(distanciaMeio < MAX_NEAR){
    moveBack(); 
    digitalWrite(LED, HIGH);
    Serial.println("BACK");
  }else if(distanciaMeio == 0 || (distanciaMeio < MAX_FAR && distanciaMeio > MAX_NEAR) || distanciaMeio > MAX_SIGN){
    _stop();
    digitalWrite(LED, LOW);
    Serial.println("STOP");
  }
  else if (distanciaDireita > distanciaMeio ) {
    moveRight();
    digitalWrite(LED, HIGH);
    Serial.println("RIGHT");
  }
  else if (distanciaEsquerda> distanciaMeio) {
    moveLeft();
    digitalWrite(LED, HIGH);
    Serial.println("LEFT");
  } 
  else if(distanciaMeio > MAX_FAR){
    moveFront();
    digitalWrite(LED, HIGH);
    Serial.println("FRONT");
  } 
  
  delay(25);
}

float sensorDireita() {
  long microsec = sensor1.timing();
  distanciaDireita = sensor1.convert(microsec, Ultrasonic::CM);
  Serial.print("Direita - Distancia em cm: ");
  Serial.println(distanciaDireita);
}

float sensorEsquerda() {
  long microsec = sensor2.timing();
  distanciaEsquerda = sensor2.convert(microsec, Ultrasonic::CM);
  Serial.print("Esquerda - Distancia em cm: ");
  Serial.println(distanciaEsquerda);
}

float sensorMeio() {
  long microsec = sensor3.timing();
  distanciaMeio = sensor3.convert(microsec, Ultrasonic::CM);
  Serial.print("Meio - Distancia em cm: ");
  Serial.println(distanciaMeio);
}

void _stop(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
void moveFront(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void moveBack(){
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void moveRight(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void moveLeft(){
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}