/*---------------------------------------------------------------------------------------  '*
  module ESP32 DEVKIT V1
  modifié gaston 83et l'aide superbe de speedf37, jpbbricole et totoche974
  avec la sélection des axes
  dernière mouture du 17/11

  modification du 06/12
  changement de la lib du bouton rotatif
  suppression de la lib #include <Encoder.h> remplacer par #include "AiEsp32RotaryEncoder.h" 
  https://github.com/igorantolic/ai-esp32-rotary-encoder

  modification du 09/12
  ajout de l'axe A

  modification du 15/12
  ajout d'un interrupteur de sécurite, empechant le démarage du bluetooth de la télécommande
  restructuration du programme : decoupag en plusieurs pages ; mise en place de structure

  modification du 30/12 
  avec l'aide de speedf37
  Implementation de l'anti-rebond sur les boutons STOP - PAUSE - START
  mise en place de la structure Mach3


Clé	Valeur      hex	  décimale
KEY_LEFT_CTRL   0x80  128
KEY_LEFT_SHIFT  0x81  129
KEY_LEFT_ALT    0x82  130
KEY_LEFT_GUI    0x83  131
KEY_RIGHT_CTRL  0x84  132
KEY_RIGHT_SHIFT 0x85  133
KEY_RIGHT_ALT   0x86  134
KEY_RIGHT_GUI   0x87  135
KEY_UP_ARROW    0xDA  218
KEY_DOWN_ARROW  0xD9  217
KEY_LEFT_ARROW  0xD8  216
KEY_RIGHT_ARROW 0xD7  215
KEY_BACKSPACE   0xB2  178
KEY_TAB         0xB3  179
KEY_RETURN      0xB0  176
KEY_ESC         0xB1  177
KEY_INSERT      0xD1  209
KEY_DELETE      0xD4  212
KEY_PAGE_UP     0xD3  211
KEY_PAGE_DOWN   0xD6  214
KEY_HOME        0xD2  210
KEY_END         0xD5  213
KEY_CAPS_LOCK   0xC1  193
KEY_F1          0xC2  194
KEY_F2          0xC3  195
KEY_F3          0xC4  196
KEY_F4          0xC5  197
KEY_F5          0xC6  198
KEY_F6          0xC7  199
KEY_F7          0xC8  200
KEY_F8          0xC9  201
KEY_F9          0xCA  202
KEY_F10         0xCB  203
KEY_F11         0xCC  204
KEY_F12         0xCD  205
*/

//installé ESP32-BLE-Keyboard.zip
//https://github.com/T-vK/ESP32-BLE-Keyboard
/**
 * @file main.cpp
 * @author 
 * @brief Télécommande bluetooth pour mach3 
 * @version 0.1
 * @date 2020-12-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <Arduino.h>
#include "cmdClavier.h"
#include "btMach3.h"
#include "manivelle.h"
#include <Keypad.h>
#include <BleKeyboard.h>
#include <AiEsp32RotaryEncoder.h>

extern Keypad keypad;
extern BleKeyboard Keyboard;
extern AiEsp32RotaryEncoder Encoder;

// definition des structure
Bouton bouton;
Manivelle MAN;
Clavier C;
// Mach3 M3;

//#define Pin_Ctrl 28

bool flag = true; // Flag de securité clavier
//const uint8_t led = 2;

void setup()
{

  Keyboard.begin();
  Encoder.begin();

  Serial.begin(115200);
  Serial.println("Starting Télécommande BLE mach3");

  pinMode(bouton.BT_SECU, INPUT_PULLUP); // CTRL bouton pour la manivelle

  pinMode(MAN.CodRotA, INPUT_PULLUP);
  pinMode(MAN.CodRotB, INPUT_PULLUP);
  pinMode(MAN.interState, INPUT_PULLUP);
  pinMode(MAN.ledState, OUTPUT);
  pinMode(bouton.Axe_X, INPUT_PULLUP);
  pinMode(bouton.Axe_Y, INPUT_PULLUP);
  pinMode(bouton.Axe_Z, INPUT_PULLUP);
  pinMode(bouton.Axe_A, INPUT_PULLUP);
  pinMode(START_BT, INPUT_PULLUP);
  pinMode(PAUSE_BT, INPUT_PULLUP);
  pinMode(ARRET_BT, INPUT_PULLUP);

  // TMP
  pinMode(TMP_BT, INPUT_PULLUP);
}

//attachInterrupt (pinNb, btMach3WK, RISING);

/*
 code VBScript à integrer dans mach3
  
  Message "Euréka.......Télécommande connectée “ 
  ou
  Message "Arrrgggg....... télécommande non connectée “
 */

void loop()
{

  char newkey = keypad.getKey();
  /*
  // mise en veille du clavier
   if (OnOff()) {
    if(flag)
    {
      if (Keyboard.isConnected()){
        digitalWrite(led, HIGH); //Keyboard.begin(); 
        }
        else Serial.println("Arrrgggg....... Keyboard non connecte");
      
      flag = false;
    }
*/
  /**
    * @file fonction correspondantes au fichier :btMach3.cpp - cmdClavier.cpp - manivelle.cpp
    * @author 
    * @brief Boutton de commande : STOP - PAUSE - ARRET
    * 
    * @copyright Copyright (c) 2020
    * 
    */
  //Anti rebond
  keypad.setDebounceTime(antiRebond);

  // Bouton mach3: STOP - PAUSE - START
  btMach3WK(ARRET_BT); btMach3WK(PAUSE_BT); btMach3WK(START_BT);
  //detachInterrupt(pinNb);

  manivelle(newkey);

  // if (Keyboard.isConnected() && newkey)
  // {
  //   switch (newkey)
  //   {
  //   case '1':
  //     Command_1(newkey);
  //     break;
  //   case '2':
  //     Command_2(newkey);
  //     break;
  //   case '3':
  //     Command_3(newkey);
  //     break;
  //   case '4':
  //     Command_4(newkey);
  //     break;
  //   case '5':
  //     Command_5(newkey);
  //     break;
  //   case '6':
  //     Command_6(newkey);
  //     break;
  //   case '7':
  //     Command_7(newkey);
  //     break;
  //   case '8':
  //     Command_8(newkey);
  //     break;
  //   case '9':
  //     Command_9(newkey);
  //     break;
  //   case '0':
  //     Command_0(newkey);
  //     break;
  //   case 'A':
  //     Command_0(newkey);
  //     break;
  //   case 'B':
  //     Command_0(newkey);
  //     break;
  //   case 'C':
  //     Command_0(newkey);
  //     break;
  //   case 'D':
  //     Command_0(newkey);
  //     break;
  //   case 'E':
  //     Command_0(newkey);
  //     break;
  //   case 'F':
  //     Command_0(newkey);
  //     break;

  //   } // fin du switch

  // } // fin du if Keyboard.isConnected

  //}// fin du test btSecu

} // end loop

//**********************************************************************************************

/*
    switch (key) {
      
      case'E':                                          // Entrée
        //if (digitalRead(Pin_Ctrl) == LOW)
        if ( Keyboard.press (130) || Keyboard.press (132) == true )  {      //newkey Ctrl à droite ou à gauche
            Keyboard.write('F');                                              // Réglage Avance en Manuel
            }
            else {
            Keyboard.press (KEY_RETURN);
            Keyboard.releaseAll();
            }
      break;

      case'1':
        if (digitalRead(Pin_Ctrl) == LOW)                // boucle pour garder le Ctrl appuyé
        {
          Keyboard.press (130);                          // Visu Automatique ALT-1
          Keyboard.press (49);                           // ecrit le chiffre 1
          Keyboard.release (49);
          delay(100);
          Keyboard.releaseAll();
        }

        Keyboard.write(219);
        Keyboard.write (225);                            
        Keyboard.releaseAll ();
        Keyboard.write(219);
        Keyboard.press (225);
        Keyboard.releaseAll ();

        break;

      case'2':
        if (digitalRead(Pin_Ctrl) == LOW)                  // boucle pour garder le Ctrl appuyé
        {
          Keyboard.press (130);                            // Visu Manuel ALT-2
          delay(100);
          Keyboard.press (50); Keyboard.release (50);      // presse le ciffre 2
          Keyboard.releaseAll();
        }
        else
            {
          Keyboard.write(226);                           
          Keyboard.releaseAll ();
        }
        break;

      case '3':
        {
        //while (digitalRead(Pin_Ctrl) == LOW)           // boucle pour garder le shift appuyé
        while ( Keyboard.press (129) || Keyboard.press (133) == true )
              {
              Keyboard.write(129);                          // KEY_LEFT_SHIFT  et remontée du Z
              //delay(20);
              Keyboard.write(211);                         // PgUp
              Keyboard.releaseAll();
              }
        }
        {
          Keyboard.write (211);                          // PgUp  montée pas à pas
          Keyboard.write (227);                           // écrit le chiffre 3
          Keyboard.releaseAll();
        }
        break;

      case '4':
        if (digitalRead(Pin_Ctrl) == LOW)               // boucle pour garder le Ctrl appuyé

        { Keyboard.write ('X');                         // écrit X dans le bandeau manuel
          Keyboard.release ('X');
          delay (400);
        }
        else
        {
          Keyboard.write(228);                            // écrit le chiffre 4
          Keyboard.releaseAll();
        }
        break;

      case '5':
        if (digitalRead(Pin_Ctrl) == LOW)               // boucle pour garder le Ctrl appuyé
        {
          Keyboard.write ('Y');                         // écrit Y dans le bandeau manuel
          Keyboard.release ('Y');
          delay (400);
        }
        else
        {
          Keyboard.write(219);
          Keyboard.write (229);                         // écrit le chiffre 5
          Keyboard.releaseAll ();
                                                        // **** BUG BUG BUG BUG BUG BUG BUG BUG ***
          Keyboard.write(219);
          Keyboard.write (229);                         // écrit le chiffre 5
          Keyboard.releaseAll ();
        }
        break;

      case '6':
        if (digitalRead(Pin_Ctrl) == LOW)              // boucle pour garder le Ctrl appuyé
        {
          Keyboard.write ('W');                       // en fait c'est le Z qui est écrit 
          Keyboard.release ('W');
          delay (400);
        }
        else
        {
          Keyboard.press (230);                        // écrit le chiffre 6
          Keyboard.release (230);
        }
        break;

      case '7':

        if (digitalRead(Pin_Ctrl) == LOW)               // boucle pour garder le Ctrl appuyé
        {
          delay(50);
          Keyboard.press(54);                           //signe "-"
          delay(50);
          Keyboard.release (54);
          delay (400);
        }
        else
        {
          Keyboard.press (231);                        // écrit le chiffre 7
          Keyboard.releaseAll ();
        }
        break;

      case '8':
        if (digitalRead(Pin_Ctrl) == LOW)               // boucle pour garder le Ctrl appuyé
        {
          delay(50);
          Keyboard.press(43);                           //signe "+"
          delay(50);
          Keyboard.release (43);
        }
        else
        {
          Keyboard.press (232);                        // écrit le chiffre 8
          Keyboard.release (232);
        }
        break;


      case '9':
        {
          while (digitalRead(Pin_Ctrl) == LOW)        // boucle pour garder le shift appuyé
          {
            Keyboard.write(129);                      //  129 Code ASCII de KEY_LEFT_SHIFT
            //delay(20);
            Keyboard.write(214);                      // newkey PgDn pour le Z  (214)
            Keyboard.releaseAll();
          }
        }
        {
          Keyboard.write(214);                        // PgUp  descente pas à pas
          Keyboard.write(233);                        // écrit le chiffre 9
          Keyboard.releaseAll();
        }
        break;

      case 'I':                                        // newkey F1 clavier déporté
        if (digitalRead(Pin_Ctrl) == LOW)
        {
          Keyboard.press (130);                         // Ouverture du menu fichier Gcode et fermeture
          delay(100);
          Keyboard.press (102); Keyboard.release (102);
          Keyboard.releaseAll();
        }
        Keyboard.press(179);                            // Tab Affichage panneau de droite  JOG
        delay(100);
        Keyboard.release(179);

        break;


      case 'U':                                          // newkey F2 clavier déporté

        if (digitalRead(Pin_Ctrl) == LOW)                // Arret/Départ cycle en Automatique
        {
          Keyboard.press (130);                          // newkey ALT_LEFT
          delay(100);
          Keyboard.press (158); Keyboard.release (158);  // newkey S avec ALT  Arret
          delay(1000);
        }
        else
        {
          Keyboard.press (130);                         // Départ cycle en Automatique
          delay(100);
          Keyboard.press (157); Keyboard.release (157); // newkey R avec ALT  Départ
        }
        break;

      case '0':                            // lettre O     // Ctrl O = remise à zéro des axes X et Y

        if (digitalRead(Pin_Ctrl) == LOW)                  // boucle pour garder le Ctrl appuyé
        {
          Keyboard.press(128);
          delay(100);
          Keyboard.press(79); Keyboard.release(79);
          Keyboard.releaseAll();
        }
        else
        {
          Keyboard.write(219);
          Keyboard.press (234);                      // chiffre 0
          Keyboard.release (234);

          Keyboard.write(219);
          Keyboard.press (234);                      // chiffre 0
          Keyboard.release (234);

        }
        break;

       case 'L':                                       // "Déplacemnt à Gauche"
        {
          while (digitalRead(Pin_Ctrl) == LOW)        // boucle pour garder le shift appuyé
          {
            {
              Keyboard.write(129);
              delay(20);
              Keyboard.write(KEY_LEFT_ARROW);        // flèche de Gauche"
            }
          }
        }
        Keyboard.write(KEY_LEFT_ARROW);
        break;

        Keyboard.releaseAll();


      case 'R':                                      // "Déplacement à Droite"
        {
          while (digitalRead(Pin_Ctrl) == LOW)       // boucle pour garder le shift appuyé
          {
            {
              Keyboard.write(129);
              delay(20);
              Keyboard.write(KEY_RIGHT_ARROW);      // "Déplacement à Droite"
            }
          }
        }
        Keyboard.write(KEY_RIGHT_ARROW);
        break;
        Keyboard.releaseAll();


      case 'B':                                      // "Déplacement Bas"
        {
          while (digitalRead(Pin_Ctrl) == LOW)       // boucle pour garder le shift appuyé
          {
            {
              Keyboard.press(129);
              delay (50);
              Keyboard.releaseAll();
            }
            Keyboard.write(217);                     // "Déplacemnt vers le bas"
            //Keyboard.write(174);
          }
        }
        Keyboard.write(217);
        break;

      case 'H':                                      // "Déplacement Haut"
        {
          while (digitalRead(Pin_Ctrl) == LOW)       // boucle pour garder le shift appuyé
          {
            {
              Keyboard.press(129);
              delay (50);
              Keyboard.releaseAll();
            }
            Keyboard.write(KEY_UP_ARROW);           // "Déplacemnt vers le haut"
            //Keyboard.write(175);
          }
        }
        Keyboard.write(KEY_UP_ARROW);
        break;
        
      

      case '#':                                     //  Manuel / Automatique ou début cycle

        if (digitalRead(Pin_Ctrl) == LOW)
        {
          Keyboard.press (128);                     // Début cycle
          Keyboard.press(165);                      // newkey W : code ascii = 87 - POURQUOI 165 ????????
          delay(100);
          Keyboard.releaseAll();

          Keyboard.press (128);
          Keyboard.press(165);                      // je répète deux fois la fonction
          delay(100);                               // pour qu'elle soit prise en compte
          Keyboard.releaseAll();                    //  Pourquoi ???????
        }
        else
        {
          Keyboard.press(128);                      // Change le mode de déplacement
          Keyboard.press(130);
          Keyboard.press('j');
          delay(100);
          Keyboard.releaseAll();
        }
        break;

      case '*':

        if (digitalRead(Pin_Ctrl) == LOW)
        {
          Keyboard.write (8);                       // étoile du clavier déporté pour le Backspace
          Keyboard.release (8);
          delay(100);
        }                                          //  ou
        else
        {
          Keyboard.press(130);                      // Réglage du saut 1.00, 0.10, 0.01
          Keyboard.press('j');
          delay(100);
          Keyboard.releaseAll();
        }
        break;

      case 'C':       // esc du clavier déporté     // ESC  ou  Passage Continu / Saut

        if (digitalRead(Pin_Ctrl) == LOW)
        {
          Keyboard.press(128);
          Keyboard.press('j');
          delay(100);
          Keyboard.releaseAll();
        }
        else
        {
          Keyboard.press(177);
          delay(100);
          Keyboard.release(177);
        }
        break;
    }
    delay(100);
    Keyboard.releaseAll();
    */
//---------------------------- Choix de l'axe -------------------------------

/*
    if (digitalRead(BT.Axe_X) == LOW) {
      BT.changeAxe = KEY_LEFT_ARROW;
      changeAxe1 = KEY_RIGHT_ARROW;
      //X  Serial.println("Axe X ");
      }

    if (digitalRead(BT.Axe_Y) == LOW) {
      changeAxe = KEY_UP_ARROW;
      changeAxe1 = KEY_DOWN_ARROW;
      //    Serial.println("Axe Y ");
      }

    if (digitalRead(BT.Axe_Z) == LOW) {
      changeAxe = (KEY_PAGE_UP);              //211
      changeAxe1 = (KEY_PAGE_DOWN);           //214
      //  Serial.println("Axe Z ");
      }
    
    if (digitalRead(BT.Axe_A) == LOW) {
      changeAxe = KEY_HOME;
      changeAxe1 = KEY_END;
      //  Serial.println("Axe A ");
      }
*/

// ----------------------- initialisation codeur -----------------------------

/*
    codRotIncrement = Encoder.readEncoder() /4;
    // Génère 4 impulsions (https://www.logre.eu/wiki/Codeur_rotatif_incrémental)

    if (codRotIncrement != 0) { // Changement de MS affiché 
       if (codRotIncrement < 0)
      {
      //if (digitalRead(Pin_Ctrl) == LOW)
      if ( Keyboard.press (128) || Keyboard.press (132) == true ) {     // newkey Ctrl à droite ou à gauche
        //Keyboard.press(128);
        Keyboard.press (changeAxe);
        delay(50);
        Keyboard.releaseAll();
         }
      }
    }

      if (codRotIncrement > 0)
      {
        //if (digitalRead(Pin_Ctrl) == LOW)
        if ( Keyboard.press (128) || Keyboard.press (132) == true ) {     // newkey Ctrl à droite ou à gauche
        {
        //Keyboard.press(128);
        Keyboard.write (changeAxe1);
        delay(50);
        Keyboard.releaseAll();
        }
      }
      codRotIncrement = 0; // Remise à Zéro du codeur
      Encoder.reset(0);
    }// end coderot
    */

//} // end bleKeyboard.isConnected

/*
    if (!flag) {
      Keyboard.end();
      digitalWrite(led, LOW);
      flag = true;
    
  } // fin du test btSecu
  }*/

/*}*/

//}   // end loop

// fin du prog