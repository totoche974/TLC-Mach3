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
| plein          | 2423            | 4.2                          |
| intermédiaire  | 2387            | 4.02                         |
| intermédiaire  | 2351            | 3.98                         |
| intermédiaire  | 2290            | 3.88                         |
| intermédiaire  | 2240            | 3.80                         |
| intermédiaire  | 2210            | 3.75                         |

A partir des données du tableau, faire le calcul de regression linéaire pour avoir
l'équation de la droite entre la valeur du senseur analogique mésurée et la tension
de la batterie (mesurée par multimètre).

En utilisant ce site :  
[Quick Linear Regression Calculator](https://www.socscistatistics.com/tests/regression/default.aspx)

On obtient l'équation suivante :  
ŷ = 0.0019X - 0.46303

où `X` représente la valeur du senseur analogique, et `ŷ` la tension de la batterie.

Pour estimer la charge de la batterie, on utilise une relation linéaire, qui dit :
4.2 V => 100% de charge
3.2 V => 0% de charge

Tout en sachant que cette relation est une approximation grossière de l'état de charge 
de la batterie. Pour plus d'information, consulter [ce lien](https://learn.adafruit.com/assets/979).

