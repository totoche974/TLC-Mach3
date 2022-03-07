# TLC-Mach3

Ce projet héberge tout ce qu'il faut pour construire une télécommande de CNC.

# Documentation

## Schéma

Schéma de la carte "DOIT dev kit v1 Expressif"
ou
"ESP32 générique ESP-WROOM-32"

Schéma de ESP32 générique ESP-WROOM-32:
![ESP32 générique ESP-WROOM-32](https://microcontrollerslab.com/wp-content/uploads/2019/02/ESP32-pinout-mapping.png "Schéma de ESP32 générique ESP-WROOM-32")

Nous utilisons maintenant la carte Adafruit Huzzah ESP32 Feather:
![Adafruit Huzzah ESP32 Feather](https://makeabilitylab.github.io/physcomp/esp32/assets/images/AdafruitHuzzah32PinDiagram.png "Schéma de Adafruit Huzzah ESP32 Feather")

## Batterie

Pour la batterie qu'on utilise, on connait les renseignements suivants :

| Etat batterie  | tension en Volt | Mesure du capteur analogique |
| :------------- |:---------------:|:----------------------------:|
| pleine         | 4.2             |  Non available               |
| service        | 3.7             |  Non available               |
| vide           | 3.2             |  Non available               |

Pour pouvoir calculer le pourcentage de batterie restant, ce tableau est à compléter au mieux.
