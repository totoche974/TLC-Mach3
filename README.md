# TLC-Mach3

Ce projet héberge tout ce qu'il faut pour construire une télécommande de CNC.

## Composition de la télécommande

- 16 touches configurable via le fichier commandClavier.cpp
- 3 touches STOP , PAUSE , START 
- 1 touche de sécurité
- 1 afficheur LCD 
- 1 manivelle encodeur pour de déplacement des axes XYZA
- 1 sélecteur d'axe rotatif 4 positions
- 1 bouton poussoir pour la visu de la batterie

TODO : image montage fritzing

# Lancer le projet

## Environnement de travail

VS Code
plateformIO
Les lib externes utilisés et leur rôle

doxygen

## Génération de la documentation

Pour générer la documentation :
```shell
doxygen doxygen.config
```

# Matériel

## Schéma

Schéma de la carte "ESP32 HUZZAH FEATHER32"


Nous utilisons la carte Adafruit Huzzah ESP32 Feather:
![Adafruit Huzzah ESP32 Feather](https://makeabilitylab.github.io/physcomp/esp32/assets/images/AdafruitHuzzah32PinDiagram.png "Schéma de Adafruit Huzzah ESP32 Feather")

## Batterie

Pour la batterie on utilise, 2 LiPo 18650 de 3Amp câblé en // 
surveillé par un module MAX17043, qui nous donne le voltage ainsi que le %
de charge restante.

Arrivé à 20% de charge restante, une led clignotante signale qu'il faut
commencer la recharge de la baterie



