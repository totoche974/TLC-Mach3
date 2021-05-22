/**
 * @note Spécifie que le compilateur n’intègre le fichier d’en-tête
 *       qu’une seule fois lors de la compilation d'un fichier source.
 */
#pragma once

//typedef struct Bouton Bouton;

// const uint8_t TMP_BT = 39; // GPIO39

struct Bouton
{
    /**
     * @note Ajout de resistance de 10K pour passer les
     * pins 34 et 35 en PULLUP
     * 
     * Obligation d'appuyer sur le bouton (BT_SECU) pour pouvoir utiliser la manivelle  
     */

    uint8_t BT_SECU = 14; // pin 26 - GPIO14

    uint8_t Axe_X = 34; // pin 19 - GPIO34 - BT tester = OK
    uint8_t Axe_Y = 35; // pin 20 - GPIO35 - BT tester = OK
    uint8_t Axe_Z = 32; // pin 21 - GPIO32 - BT tester = OK
    uint8_t Axe_A = 33; // pin 22 - GPIO33 - BT tester = OK
    //uint8_t Secu  = 3;
};

const uint8_t ARRET_BT = 25; //pin 23 - GPIO25 - BT tester = OK
const uint8_t PAUSE_BT = 26; //pin 24 - GPIO26 - BT tester = OK
const uint8_t START_BT = 27; //pin 25 - GPIO27 - BT tester = OK

//typedef struct Manivelle Manivelle;
struct Manivelle
{

    uint8_t CodRotA = 19; // S2 - D19 - GPIO19
    uint8_t CodRotB = 18; // S1 - D18 - GPIO18
    uint8_t changeAxe;
    uint8_t changeAxe1;
    uint8_t codRotIncrement = 0; // Direction de l'encodeur +1 ou -1
    uint8_t compteur = 0;

    uint8_t inter = 5;
    uint8_t ledPin = 35; // TODO: to fix
    uint8_t interState = 0;
    uint8_t lastInterState = 0;
    uint8_t ledState = 0;
};

//typedef struct Clavier Clavier;

struct Clavier
{
    byte lig_1 = 21;
    byte lig_2 = 22;
    byte lig_3 = 23;
    byte lig_4 = 24;
    //byte lig_5 = ;
    byte col_1 = 13;
    byte col_2 = 12;
    byte col_3 = 14;
    byte col_4 = 15;

    // unsigned int anti_rebond = 50; //5 ms
};

const byte ROWS = 4; //4 lignes
const byte COLS = 4; //4 colonnes

const unsigned antiRebond = 10;

// void btMach3(); // Bouton mach3: STOP - PAUSE - START

//void manivelle(uint8_t newkey);
void OnOff(); // mise en sécurité de la télécommande

void Command_1(char newkey); // action :
void Command_2(char newkey); //
void Command_3(char newkey); //
void Command_4(char newkey); //
void Command_5(char newkey); //
void Command_6(char newkey); //
void Command_7(char newkey); //
void Command_8(char newkey); //
void Command_9(char newkey); //
void Command_0(char newkey); //
void Command_A(char newkey); //
void Command_B(char newkey); //
void Command_C(char newkey); //
void Command_D(char newkey); //
void Command_E(char newkey); //
void Command_F(char newkey); //