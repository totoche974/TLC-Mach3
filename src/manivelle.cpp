#include <Arduino.h>
#include "cmdClavier.h"
#include <BleKeyboard.h>
#include <AiEsp32RotaryEncoder.h>

extern BleKeyboard Keyboard;
extern Manivelle MAN;
extern Bouton bouton;

AiEsp32RotaryEncoder Encoder = AiEsp32RotaryEncoder(MAN.CodRotA, MAN.CodRotB, MAN.inter);

void manivelle(uint8_t newkey)
{

  bool tmpBtState = digitalRead(TMP_BT);

  MAN.codRotIncrement = Encoder.readEncoder() / 4; // Génère 4 impulsions (https://www.logre.eu/wiki/Codeur_rotatif_incrémental)

  if (MAN.codRotIncrement != 0)
     { // Changement de MS affiché
     if (MAN.codRotIncrement < 0)
    {
      //if (digitalRead(Pin_Ctrl) == LOW)
      if (Keyboard.press(128) || Keyboard.press(132) && tmpBtState)
      //if (Keyboard.press(128) || Keyboard.press(132))
      { // Touche Ctrl à droite ou à gauche
        //Keyboard.press(128);
        printf("MAN.codRotIncrement < 0\n");
        Keyboard.press(MAN.changeAxe);
        delay(50);
        Keyboard.releaseAll();
      }
    }
  }

  if (MAN.codRotIncrement > 0)
  {
    //if (digitalRead(Pin_Ctrl) == LOW)
    if (Keyboard.press(128) || Keyboard.press(132) && tmpBtState)
    //if (Keyboard.press(128) || Keyboard.press(132))
    { // Touche Ctrl à droite ou à gauche
      //{
      //Keyboard.press(128);
      printf("MAN.codRotIncrement > 0\n");
      Keyboard.write(MAN.changeAxe1);
      delay(50);
      Keyboard.releaseAll();
      //}
    }
    MAN.codRotIncrement = 0; // Remise à Zéro du codeur
    Encoder.reset(0);        // TODO
  }                          // end coderot

  
  if (digitalRead(bouton.Axe_X) == LOW) {
     printf("Axe_X\n");
     MAN.changeAxe = KEY_LEFT_ARROW;
     MAN.changeAxe1 = KEY_RIGHT_ARROW;
     //X  Serial.println("Axe X ");
    }

  if (digitalRead(bouton.Axe_Y) == LOW) {
     printf("Axe_Y\n");
     MAN.changeAxe = KEY_UP_ARROW;
     MAN.changeAxe1 = KEY_DOWN_ARROW;
     //Serial.println("Axe Y ");
    }

  if (digitalRead(bouton.Axe_Z) == LOW) {
     printf("Axe_Z\n");
     MAN.changeAxe = KEY_PAGE_UP;    //211
     MAN.changeAxe1 = KEY_PAGE_DOWN; //214
     //  Serial.println("Axe Z ");
    }

  if (digitalRead(bouton.Axe_A) == LOW) {
     printf("Axe_A\n");
     MAN.changeAxe = KEY_HOME;
     MAN.changeAxe1 = KEY_END;
     //  Serial.println("Axe A ");
    }
  printf("\n");
  delay(1000);
}

void OnOff()
{
  MAN.interState = digitalRead(MAN.inter);
  if (MAN.interState != MAN.lastInterState)
  {
    if (MAN.interState == 1)
    {
      if (MAN.ledState == 1)
      {
        (digitalRead(MAN.inter) == 0);
        MAN.ledState = 0;
      }
      else
      {
        (digitalRead(MAN.inter) == 1);
        MAN.ledState = 1;
      }
    }
    MAN.lastInterState = MAN.interState;
  }
  digitalWrite(MAN.ledPin, MAN.ledState);
  delay(20);
}

/*

https://www.developpez.net/forums/d1928365/general-developpement/programmation-systeme/embarque/arduino/fonction-interrupteur-on-off-bouton-poussoir/

const int inter = 2;    //pin pour le bouton
const int ledPin =  13;     //pin pour la lED
 
int interrupteur = LOW;       //valeur de l'interrupeteur
int lastState = 0;             //valeur pour changement d'état du bouton
int btState = 0;        //etat fugitif du bouton    
 
 
void setup() {
  Serial.begin(9600);
  // Initialisation de la LED en sortie
  pinMode(ledPin, OUTPUT);     
  // Initialisation du bouton en entrée
  pinMode(inter, INPUT);    
}
 
void loop(){
  onOff(inter, lastState);   
}
 
 
int  onOff (int inter, int lastState) {
    btState = digitalRead(inter);
    //On regarde si le bouton est pressé
      if (btState == HIGH) {           
    //on regarde si il y a un changement d'état
      if (lastState == 1) {
        // on change l'état du bouton
          interrupteur=!interrupteur;
        // on reinitialise le lastState
          lastState=0;
      // on affiche l'état de l'interupteur virtuel sur la led
      digitalWrite(ledPin, interrupteur); 
    }     
  } else {
    //le bouton n'est pas pressé, on active le lastState
    lastState=1;
  }
return lastState;
}
*/
