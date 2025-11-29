#include "MPUModule.h"

// ---------- MPUManager ----------
//variables privadas
MPUManager::MPUManager(uint8_t sdaPin, uint8_t sclPin)
  : _sda(sdaPin), _scl(sclPin) {}

void MPUManager::begin() {
  Wire.begin(_sda, _scl);
  //indica la libreria que use Wire
  mpu.setWire(&Wire);
  // inicia cada sensor
  mpu.beginAccel();
  mpu.beginGyro();
  mpu.beginMag();
  delay(DELAY); // pequeño retraso para estabilizar
}

// actualiza las muestras mas recientes
void MPUManager::update() {
  mpu.accelUpdate();
  mpu.gyroUpdate();
  mpu.magUpdate();
}

// devuelve la lectura acelerómetro
float MPUManager::accelX() const { return mpu.accelX(); }
float MPUManager::accelY() const { return mpu.accelY(); }
float MPUManager::accelZ() const { return mpu.accelZ(); }

// giroscopio
float MPUManager::gyroX() const { return mpu.gyroX(); }
float MPUManager::gyroY() const { return mpu.gyroY(); }
float MPUManager::gyroZ() const { return mpu.gyroZ(); }

// magnetómetro
float MPUManager::magX() const { return mpu.magX(); }
float MPUManager::magY() const { return mpu.magY(); }
float MPUManager::magZ() const { return mpu.magZ(); }


// ---------- Printer ----------
// guarda las referencia al MPUManager
Printer::Printer(MPUManager &mpuRef) : _mpu(mpuRef) {}

void Printer::printForPlotter() {
  // imprime solo acelerómetro separados por espacios (para Serial Plotter)
  Serial.print(_mpu.accelX(), DECIMALES);
  Serial.print(' ');
  Serial.print(_mpu.accelY(), DECIMALES);
  Serial.print(' ');
  Serial.println(_mpu.accelZ(), DECIMALES);
}

// imprimir las lecturas
// acelerometro (1g = 9.81 m/s^2)
void Printer::printVerbose() {
  Serial.print("Acelerómetro (g): ");
  Serial.print("X="); Serial.print(_mpu.accelX(), DECIMALES);
  Serial.print("  Y="); Serial.print(_mpu.accelY(), DECIMALES);
  Serial.print("  Z="); Serial.println(_mpu.accelZ(), DECIMALES);

// giroscopio (1°/s= 1 grado sobre segundo)
  Serial.print("Giroscopio (°/s): ");
  Serial.print("X="); Serial.print(_mpu.gyroX(), DECIMALES);
  Serial.print("  Y="); Serial.print(_mpu.gyroY(), DECIMALES);
  Serial.print("  Z="); Serial.println(_mpu.gyroZ(), DECIMALES);

// magnetometro (1µT = 1 microtesla)
  Serial.print("Magnetómetro (µT): ");
  Serial.print("X="); Serial.print(_mpu.magX(), DECIMALES);
  Serial.print("  Y="); Serial.print(_mpu.magY(), DECIMALES);
  Serial.print("  Z="); Serial.println(_mpu.magZ(), DECIMALES);

  Serial.println("-------------------------------");
}
