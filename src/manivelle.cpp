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
  //if (digitalRead(bouton.BT_SECU) == LOW) { printf("Boutton BT_SECU - OK\n");

  //bool tmpBtState = digitalRead(TMP_BT);

  MAN.codRotIncrement = Encoder.readEncoder() / 4; // Génère 4 impulsions (https://www.logre.eu/wiki/Codeur_rotatif_incrémental)

  if (MAN.codRotIncrement != 0)
  { // Changement de MS affiché
    if (MAN.codRotIncrement < 0)
    {
      if (digitalRead(bouton.BT_SECU) == LOW)
      //if (Keyboard.press(128) || Keyboard.press(132) && tmpBtState)
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
    if (digitalRead(bouton.BT_SECU) == LOW)
    //if (Keyboard.press(128) || Keyboard.press(132) && tmpBtState)
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

  // if  (digitalRead(bouton.BT_SECU) == LOW) {
  //     printf("Boutton BT_SECU = LOW\n");
  // }

  if ((digitalRead(bouton.Axe_X) == LOW) && (digitalRead(bouton.BT_SECU) == LOW))
  {
    printf("Axe_X\n");
    printf("Boutton BT_SECU = OK\n");
    MAN.changeAxe = KEY_LEFT_ARROW;
    MAN.changeAxe1 = KEY_RIGHT_ARROW;
    // Avoir les sens de rotation de CodRotA et CodRotB
    if (digitalRead(MAN.CodRotA) == LOW)
    {
      printf("Manivelle CodRotA LOW\n");
    }
    if (digitalRead(MAN.CodRotB) == LOW)
    {
      printf("Manivelle CodRotB LOW\n");
    }
    if (digitalRead(MAN.CodRotA) == HIGH)
    {
      printf("Manivelle CodRotA HIGH\n");
    }
    if (digitalRead(MAN.CodRotB) == HIGH)
    {
      printf("Manivelle CodRotB HIGH\n");
    }
  }

  if ((digitalRead(bouton.Axe_Y) == LOW) && (digitalRead(bouton.BT_SECU) == LOW))
  {
    printf("Axe_Y\n");
    printf("Boutton BT_SECU = OK\n");
    MAN.changeAxe = KEY_UP_ARROW;
    MAN.changeAxe1 = KEY_DOWN_ARROW;
  }

  if ((digitalRead(bouton.Axe_Z) == LOW) && (digitalRead(bouton.BT_SECU) == LOW))
  {
    printf("Axe_Z\n");
    printf("Boutton BT_SECU = OK\n");
    MAN.changeAxe = KEY_PAGE_UP;    //211
    MAN.changeAxe1 = KEY_PAGE_DOWN; //214
  }

  if ((digitalRead(bouton.Axe_A) == LOW) && (digitalRead(bouton.BT_SECU) == LOW))
  {
    printf("Axe_A\n");
    printf("Boutton BT_SECU = OK\n");
    MAN.changeAxe = KEY_HOME;
    MAN.changeAxe1 = KEY_END;
  }
  //}
  printf("défile\n");
  // TODO: à retirer
  delay(100);
  //} fin du if du  BT_SECU
}

// TODO: voir si c'est toujours utile
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
