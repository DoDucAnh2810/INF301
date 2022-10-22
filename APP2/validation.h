#ifndef VALIDATION_H
#define VALIDATION_H


#include "listes.h"
#include "piles.h"


void validation_pas_vide(pile_t *pile);

void validation_calculs(pile_t *pile);

void validation_expr_conditionelle(pile_t *pile);

void validation_executer(pile_t *pile);

void validation_echanger(pile_t *pile);

void validation_boucle(pile_t *pile);


#endif