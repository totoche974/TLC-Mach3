/**
 * @note Spécifie que le compilateur n’intègre le fichier d’en-tête
 *       qu’une seule fois lors de la compilation d'un fichier source.
 */
#pragma once

#ifndef _CMD_CLAVIER_H
#define _CMD_CLAVIER_H

// const int PIN_SDA = (int)GPIO_NUM_22;
// const int PIN_SCL = (int)GPIO_NUM_23;

void initCommandClavier();
void runCommandClavier();

void DisableWifi();

#endif // _CMD_CLAVIER_H
