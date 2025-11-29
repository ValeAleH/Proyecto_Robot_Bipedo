#ifndef MPU_MODULE_H
#define MPU_MODULE_H

#include <Wire.h>
#include <MPU9250_asukiaaa.h>
#define BAUDRATE  115200
#define INICIAL   0
#define DECIMALES 3
#define DELAY     1000
// MPUManager: inicializa y actualiza el sensor (MPU9250_asukiaaa)
// Printer: imprime para Serial Plotter (ax ay az) y salida detallada

class MPUManager {
public:
  MPUManager(uint8_t sdaPin = 21, uint8_t sclPin = 22);
  void begin();
  void update(); // actualiza lecturas internas

  // devuelven ultimas lecturas (acelerómetro, giroscopio, magnetómetro)
  float accelX() const;
  float accelY() const;
  float accelZ() const;

  float gyroX() const;
  float gyroY() const;
  float gyroZ() const;

  float magX() const;
  float magY() const;
  float magZ() const;

// instancia interna de la libreria
private:
  MPU9250_asukiaaa mpu;
  uint8_t _sda;
  uint8_t _scl;
};

// toma referencia de MPUManager
class Printer {
public:
  Printer(MPUManager &mpuRef);
  void printForPlotter(); // imprime "ax ay az" (una línea)
  void printVerbose();    // imprime salida humana detallada

private:
  MPUManager &_mpu;
};

#endif // MPU_MODULE_H
