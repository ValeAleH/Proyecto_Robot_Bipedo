#include "MPUModule.h"

// Pines I2C 
#define SDA_PIN 21
#define SCL_PIN 22

// Intervalos (ms)
const unsigned long PLOTTER_INTERVAL = 50;  // 20 Hz para Serial Plotter
const unsigned long VERBOSE_INTERVAL = 500; // salida humana cada 500 ms
//NO imprime en cada ciclo del loop, sino solo cada cierto tiempo

// objetos globales
MPUManager mpu(SDA_PIN, SCL_PIN);
// recibe referencia del mpu
Printer printer(mpu);

// temporizadores no bloqueantes
unsigned long lastPlotter = INICIAL;
unsigned long lastVerbose = INICIAL;

void setup() {
  Serial.begin(BAUDRATE);

  Serial.println("Iniciando MPU9250...");
  mpu.begin();
  Serial.println("MPU9250 listo.\n");

  lastPlotter = millis();
  lastVerbose = millis();
}

void loop() {
  // controlar el tiempo de ahora
  unsigned long now = millis();

  // actualizar sensor lo más seguido posible
  mpu.update();

  // salida para Serial Plotter (ax ay az)
  if (now - lastPlotter >= PLOTTER_INTERVAL) {
    printer.printForPlotter();
    lastPlotter = now;
  }

  // salida detallada para lectura humana
  //funciona como un cronometro no bloqueante
  if (now - lastVerbose >= VERBOSE_INTERVAL) {
    printer.printVerbose();
    lastVerbose = now;
  }

}
