# Medidor de Humedad con Arduino y Bluetooth

Este proyecto mide la humedad y temperatura ambiente usando un sensor DHT11/DHT22 y envía los datos al celular mediante Bluetooth HC-05.

## Componentes necesarios
- Arduino UNO/NANO
- Sensor DHT11 o DHT22
- Módulo Bluetooth HC-05
- Protoboard
- Cables jumper
- Batería o fuente 5V

## Conexiones

### Sensor DHT11/DHT22
- VCC -> 5V
- GND -> GND
- DATA -> Pin digital 7

### Módulo Bluetooth HC-05
- VCC -> 5V
- GND -> GND
- TX -> Pin digital 10
- RX -> Pin digital 11

## Código del Arduino

```cpp
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11   // Cambia a DHT22 si usas ese sensor

DHT dht(DHTPIN, DHTTYPE);

// Pines para Bluetooth HC-05
const int BT_TX = 10;
const int BT_RX = 11;

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Sistema de medicion de humedad iniciado");
}

void loop() {
  delay(2000);

  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error leyendo el sensor DHT");
    return;
  }

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print("%  Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");

  // Enviar datos por Serial para el modulo Bluetooth
  Serial.print("HUMEDAD:");
  Serial.print(humedad);
  Serial.print("%;TEMPERATURA:");
  Serial.print(temperatura);
  Serial.println("C");
}
```

## Cómo conectar el módulo Bluetooth

El módulo HC-05 usa comunicación serial. En Arduino:
- TX del HC-05 -> RX del Arduino (pin 11)
- RX del HC-05 -> TX del Arduino (pin 10)

Importante: si usas comunicación serial con Arduino IDE, puedes usar `SoftwareSerial` para no interferir con el monitor serial.

## App para celular
Puedes usar cualquiera de estas apps para ver la lectura:
- Serial Bluetooth Terminal
- Bluetooth Terminal HC-05
- Arduino Bluetooth Controller

## Como visualizar los datos en el celular
1. Enciende el HC-05 y empareja con tu teléfono.
2. Abre la app Bluetooth terminal.
3. Conéctate al HC-05.
4. Verás mensajes como:
   - `HUMEDAD:55.00%;TEMPERATURA:28.00C`

## Mejoras posibles
- Añadir alarma si la humedad es muy alta o baja
- Guardar datos en una base de datos
- Añadir pantalla LCD
- Crear una app con botones para activar ventiladores

## Nota
Necesitas instalar la librería `DHT` en Arduino IDE antes de compilar:
- Ir a Arduino IDE > Sketch > Incluir librería > Administrar bibliotecas
- Buscar: `DHT sensor library`
- Instalar la librería de Adafruit

