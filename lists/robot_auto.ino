/*
  ROBOT AUTO ARDUINO - Control de movimiento básico
  Compatible con: Arduino UNO, MEGA, NANO
  
  Componentes necesarios:
  - Arduino UNO/NANO/MEGA
  - 2 Motores DC con módulo L298N
  - 4 Ruedas
  - Batería 9V o powerbank
  - Sensor ultrasónico HC-SR04 (opcional)
  - LEDs indicadores (opcional)
*/

// ========== PINES MOTOR IZQUIERDO ==========
const int motorIzq_IN1 = 8;   // Control 1 motor izquierdo
const int motorIzq_IN2 = 9;   // Control 2 motor izquierdo
const int motorIzq_EN = 10;   // PWM velocidad motor izquierdo

// ========== PINES MOTOR DERECHO ==========
const int motorDer_IN1 = 11;  // Control 1 motor derecho
const int motorDer_IN2 = 12;  // Control 2 motor derecho
const int motorDer_EN = 13;   // PWM velocidad motor derecho

// ========== PINES SENSOR ULTRASÓNICO ==========
const int trigPin = 2;        // Pin TRIG
const int echoPin = 3;        // Pin ECHO

// ========== VARIABLES ==========
int velocidad = 255;          // Velocidad máxima (0-255)
int distancia = 0;

void setup() {
  Serial.begin(9600);
  
  // Configurar pines como salidas
  pinMode(motorIzq_IN1, OUTPUT);
  pinMode(motorIzq_IN2, OUTPUT);
  pinMode(motorIzq_EN, OUTPUT);
  
  pinMode(motorDer_IN1, OUTPUT);
  pinMode(motorDer_IN2, OUTPUT);
  pinMode(motorDer_EN, OUTPUT);
  
  // Sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.println("ROBOT INICIADO");
  delay(1000);
}

void loop() {
  distancia = medirDistancia();
  
  if (distancia > 20) {
    // Si hay espacio, avanzar
    avanzar();
    Serial.println("Avanzando...");
  } else {
    // Si hay obstáculo, detener y retroceder
    detener();
    delay(500);
    retroceder();
    delay(800);
    detener();
    delay(500);
    girarDerecha();
    delay(600);
  }
}

// ========== FUNCIONES DE MOVIMIENTO ==========

// Avanzar hacia adelante
void avanzar() {
  // Motor izquierdo adelante
  digitalWrite(motorIzq_IN1, HIGH);
  digitalWrite(motorIzq_IN2, LOW);
  analogWrite(motorIzq_EN, velocidad);
  
  // Motor derecho adelante
  digitalWrite(motorDer_IN1, HIGH);
  digitalWrite(motorDer_IN2, LOW);
  analogWrite(motorDer_EN, velocidad);
}

// Retroceder hacia atrás
void retroceder() {
  // Motor izquierdo atrás
  digitalWrite(motorIzq_IN1, LOW);
  digitalWrite(motorIzq_IN2, HIGH);
  analogWrite(motorIzq_EN, velocidad);
  
  // Motor derecho atrás
  digitalWrite(motorDer_IN1, LOW);
  digitalWrite(motorDer_IN2, HIGH);
  analogWrite(motorDer_EN, velocidad);
}

// Girar a la derecha
void girarDerecha() {
  // Motor izquierdo adelante
  digitalWrite(motorIzq_IN1, HIGH);
  digitalWrite(motorIzq_IN2, LOW);
  analogWrite(motorIzq_EN, velocidad);
  
  // Motor derecho atrás
  digitalWrite(motorDer_IN1, LOW);
  digitalWrite(motorDer_IN2, HIGH);
  analogWrite(motorDer_EN, velocidad);
}

// Girar a la izquierda
void girarIzquierda() {
  // Motor izquierdo atrás
  digitalWrite(motorIzq_IN1, LOW);
  digitalWrite(motorIzq_IN2, HIGH);
  analogWrite(motorIzq_EN, velocidad);
  
  // Motor derecho adelante
  digitalWrite(motorDer_IN1, HIGH);
  digitalWrite(motorDer_IN2, LOW);
  analogWrite(motorDer_EN, velocidad);
}

// Detener todos los motores
void detener() {
  analogWrite(motorIzq_EN, 0);
  analogWrite(motorDer_EN, 0);
  Serial.println("Detenido");
}

// ========== SENSOR ULTRASÓNICO ==========

// Medir distancia en cm
int medirDistancia() {
  // Enviar pulso
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Recibir echo
  long duracion = pulseIn(echoPin, HIGH);
  int distancia = duracion * 0.034 / 2;
  
  return distancia;
}

// ========== CONTROL SERIAL (opcional) ==========

void controlarPorSerial() {
  if (Serial.available()) {
    char comando = Serial.read();
    
    switch(comando) {
      case 'W':  // Adelante
      case 'w':
        avanzar();
        break;
      case 'S':  // Atrás
      case 's':
        retroceder();
        break;
      case 'A':  // Izquierda
      case 'a':
        girarIzquierda();
        break;
      case 'D':  // Derecha
      case 'd':
        girarDerecha();
        break;
      case 'X':  // Detener
      case 'x':
        detener();
        break;
    }
  }
}
