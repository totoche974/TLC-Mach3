/**
 * @note Spécifie que le compilateur n’intègre le fichier d’en-tête
 *       qu’une seule fois lors de la compilation d'un fichier source.
 */
#pragma once

#ifndef _CMD_CLAVIER_H
#define _CMD_CLAVIER_H
//typedef struct Bouton Bouton;

// const uint8_t TMP_BT = 39; // GPIO39

// CodRotA : sens horaire
// CodRotB : sens antihoraire
const uint8_t CodRotA = 18; // S2 - D18 - GPIO18
const uint8_t CodRotB = 19; // S1 - D19 - GPIO19

//typedef struct Manivelle Manivelle;
struct Manivelle
{
    uint8_t changeAxe;
    uint8_t changeAxe1;
    uint8_t codRotIncrement = 0; // Direction de l'encodeur +1 ou -1
    uint8_t compteur = 0;

    // uint8_t inter = 5;
    uint8_t ledPin = 35; // TODO: to fix
    uint8_t interState = 0;
    uint8_t lastInterState = 0;
    uint8_t ledState = 0;
};

//typedef struct Clavier Clavier;

struct Clavier
{
    byte lig_1 = 0;
    byte lig_2 = 1;
    byte lig_3 = 2;
    byte lig_4 = 3;

    byte col_1 = 4;
    byte col_2 = 5;
    byte col_3 = 6;


    // unsigned int anti_rebond = 50; //5 ms
};

const byte ROWS = 4; //4 lignes
const byte COLS = 3; //3 colonnes

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

#endif // _CMD_CLAVIER_H
