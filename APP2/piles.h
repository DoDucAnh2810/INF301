#ifndef PILES_H
#define PILES_H


#include "listes.h"

typedef sequence_t pile_t;


void initPile(pile_t *pile);

void empiler(pile_t *pile, int val, cellule_t *groupe);

void depiler(pile_t *pile, int *out_pnt, cellule_t **groupe_pnt);

void addition(pile_t *pile);

void soustraction(pile_t *pile);

void multiplication(pile_t *pile);

cellule_t *expr_conditionelle(pile_t *pile);

cellule_t *executer(pile_t *pile);

cellule_t *boucle(pile_t *pile);

void echanger(pile_t *pile);

void cloner(pile_t * pile);

void ignorer(pile_t *pile);

void rotation(pile_t *pile);


#endif