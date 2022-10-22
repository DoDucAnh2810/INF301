#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listes.h"
#include "validation.h"


void validation_pas_vide(pile_t *pile) {
    assert(pile != NULL);
    if (vide(pile)) {
        eprintf("main: depiler: Erreur: Ne peut pas depiler une pile vide\n");
        exit(3);
    }
}


void validation_calculs(pile_t *pile) {
    assert(pile != NULL);
    if (pile->nb_valeur < 2) {
        eprintf("main: calculs: Erreur: Pas assez de nombre dans la pile\n");
        exit(4);
    }
    if (iloc(pile, 0)->commande != EMPTY || iloc(pile, 1)->commande != EMPTY) {
        eprintf("main: calculs: Erreur: Impossible de faire un calcul sur une commande ou un groupe\n");
        exit(5);
    }
}


void validation_expr_conditionelle(pile_t *pile) {
    assert(pile != NULL);
    if (pile->nb_valeur == 0 || pile->nb_groupe < 2) {
        eprintf("main: expr_conditionelle: Erreur: Pas assez d'element dans la pile\n");
        exit(6);
    }
    if (iloc(pile, 0)->commande != GROUPE || iloc(pile, 1)->commande != GROUPE || iloc(pile, 2)->commande != EMPTY) {
        eprintf("main: expr_conditionelle: Erreur: Expression conditionelle mauvaise!\n");
        exit(7);
    }
}


void validation_executer(pile_t *pile) {
    validation_pas_vide(pile);
    if (iloc(pile, 0)->commande != GROUPE) {
        eprintf("main: executer: Erreur: Impossible d'executer un nombre ou une caractere\n");
        exit(8);
    }
}


void validation_echanger(pile_t *pile) {
    assert(pile != NULL);
    if ((pile->nb_valeur + pile->nb_groupe) < 2) {
        eprintf("main: echanger: Erreur: Pas assez d'element dans la pile\n");
        exit(9);
    }
}


void validation_boucle(pile_t *pile) {
    assert(pile != NULL);
    if (pile->nb_groupe == 0 || pile->nb_valeur == 0) {
        eprintf("main: boucle: Erreur: Pas assez d'element dans la pile\n");
        exit(10);
    } 
    if (iloc(pile, 0)->commande != EMPTY) {
        eprintf("main: boucle: Erreur: Un groupe ou une commande ne peut pas etre l'entier de la boucle\n");
        exit(11);
    } 
    if (iloc(pile, 1)->commande == EMPTY) {
        eprintf("main: boucle: Erreur: Impossible d'executer un nombre\n");
        exit(12);
    }
}