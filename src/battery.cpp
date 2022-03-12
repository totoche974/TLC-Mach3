
#include <Arduino.h>
#include <cmath>
#include <algorithm>

// ADC : Analogy Digital Convertion
const int PIN_ADC = A13;

int getSensorValue()
{
  return analogRead(PIN_ADC);
}

float computeTension(int sensorValue)
{
  // [V] = [V.sensor^(-1)] * [sensor] - [V]
  // [V] = [V / sensor] * [sensor] - [V]
  return 0.0019 * sensorValue - 0.46303;
}

int computeLoadPercent(float tension)
{
  // On veut
  // 4.2 V => 100% de charge
  // 3.2 V => 0% de charge

  // On ramène l'intervalle de tension [3,2 ; 4,2] à l'intervalle [0 ; 1,0]
  float tensionWk = tension - 3.2;
  // Multiplié par 100 et arrondir à l'entier le plus proche pour
  // obtenir le pourcentage
  int pourcentage = std::min(100, (int)round(tensionWk * 100));

  return pourcentage;
}

float getTension()
{
  int sensorValue = getSensorValue();
  // printf("sensorValue %d\n", sensorValue);
  return computeTension(sensorValue);
}

int getLoadBattery()
{
  return computeLoadPercent(getTension());
}