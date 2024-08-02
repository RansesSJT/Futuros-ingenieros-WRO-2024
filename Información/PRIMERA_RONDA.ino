#include <Servo.h>          // Incluye la biblioteca Servo
#include <NewPing.h>        // Incluye la biblioteca NewPing
#include <AFMotor.h>        // Incluye la biblioteca AFMotor

#define TRIG_PIN A4
#define ECHO_PIN A5
#define MAX_DISTANCE 300 // Distancia máxima en cm
#define MAX_SPEED 255    // Velocidad máxima del motor

// Inicialización de objetos
Servo servoUltrasonic;
Servo servoSteering;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Configuración de los motores
AF_DCMotor motor(1); // Conectado al canal 1 de la Shield

// Variables de tiempo y distancia
unsigned long startTime;
bool isAvoiding = false;

void setup() {
  // Inicializar los servomotores
  servoUltrasonic.attach(10); // Conexión en Servo2 del Motor Shield L293D
  servoSteering.attach(9);    // Conexión en Servo1 del Motor Shield L293D
  
  // Inicialización del motor
  motor.setSpeed(MAX_SPEED); // Velocidad inicial del motor

  // Inicialización serial
  Serial.begin(9600);
  
  // Inicia el movimiento
  motor.run(FORWARD);
  startTime = millis(); // Guarda el tiempo de inicio
}

void loop() {
  // Obtener la distancia del objeto
  int distance = sonar.ping_cm();
  avanzar();
  
  // Imprimir la distancia para depuración
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Si se detecta un objeto a menos de 50 cm y no está evitando actualmente
  if (distance > 0 && distance < 60 && !isAvoiding) {
    isAvoiding = true;
  
    motor.setSpeed(MAX_SPEED);
    esquivarbordes();

    isAvoiding = false;
  }
  // Detener después de 3 minutos (180,000 milisegundos)
  if (millis() - startTime >= 180000) {
    motor.run(RELEASE);
    while (true); // Detener el programa
  }
}

void avanzar() {
  motor.setSpeed(MAX_SPEED);
  motor.run(FORWARD);
}
void avanzarrecto (){
 motor.setSpeed(MAX_SPEED);
  motor.run(FORWARD);  
  servoSteering.write(90);
}

void reversa() {
  motor.setSpeed(MAX_SPEED);
  motor.run(BACKWARD);
}

void giroder() {
  servoSteering.write(120);
  motor.setSpeed(MAX_SPEED);
  avanzar();
  delay(2200);
}

void esquivarbordes() {
  reversa();
  delay(1000); // Mantener el retroceso durante 1 segundo
  giroder();
 avanzarrecto();
  motor.setSpeed(MAX_SPEED);
  avanzarrecto();
}
