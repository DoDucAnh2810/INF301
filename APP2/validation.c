#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listes.h"
#include "validation.h"


void validation_texte_conversion(char *texte, int len_txt) {
    assert(texte != NULL);
    int i, depth = 0;
    for (i = 0; i < len_txt; i++) {
        if (texte[i] == '{') {
            depth++;
        } else if (texte[i] == '}') {
            depth--;
            if (depth < 0) {
                eprintf("main: conversion: Erreur: Fermeture de parenthèse inattendue au caractère %d du programme\n", i + 1);
                exit(3);
            }
        }
    }
    if (depth > 0) {
        eprintf("main: conversion: Erreur: Plus de parenthèse ouvrante que de parenthèse fermante\n");
        exit(4);
    }
}


void validation_pas_vide(pile_t *pile) {
    assert(pile != NULL);
    if (vide(pile)) {
        eprintf("main: depiler: Erreur: Ne peut pas depiler une pile vide\n");
        exit(5);
    }
}


void validation_calculs(pile_t *pile) {
    assert(pile != NULL);
    if (pile->nb_valeur < 2) {
        eprintf("main: calculs: Erreur: Pas assez de valeur dans la pile\n");
        exit(6);
    }
    if (iloc(pile, 0)->commande != EMPTY || iloc(pile, 1)->commande != EMPTY) {
        eprintf("main: calculs: Erreur: Impossible de faire un calcul sur une commande ou un groupe\n");
        exit(7);
    }
}


void validation_expr_conditionelle(pile_t *pile) {
    assert(pile != NULL);
    if (pile->nb_valeur < 1 || pile->nb_groupe < 2) {
        eprintf("main: expr_conditionelle: Erreur: Pas assez d'element dans la pile\n");
        exit(8);
    }
    if (iloc(pile, 0)->commande != GROUPE || iloc(pile, 1)->commande != GROUPE || iloc(pile, 2)->commande != EMPTY) {
        eprintf("main: expr_conditionelle: Erreur: Expression conditionelle mauvaise!\n");
        exit(9);
    }
}


void validation_executer(pile_t *pile) {
    validation_pas_vide(pile);
    if (iloc(pile, 0)->commande != GROUPE) {
        eprintf("main: executer: Erreur: Impossible d'executer un nombre ou une caractere\n");
        exit(10);
    }
}


void validation_echanger(pile_t *pile) {
    assert(pile != NULL);
    if (taille(pile) < 2) {
        eprintf("main: echanger: Erreur: Pas assez d'element dans la pile\n");
        exit(11);
    }
}


void validation_boucle(pile_t *pile) {
    assert(pile != NULL);
    if (pile->nb_groupe == 0 || pile->nb_valeur == 0) {
        eprintf("main: boucle: Erreur: Pas assez d'element dans la pile\n");
        exit(12);
    } 
    if (iloc(pile, 0)->commande != EMPTY) {
        eprintf("main: boucle: Erreur: Un groupe ou une commande ne peut pas etre l'entier de la boucle\n");
        exit(13);
    } 
    if (iloc(pile, 1)->commande == EMPTY) {
        eprintf("main: boucle: Erreur: Impossible d'executer une valeur\n");
        exit(14);
    }
}


void validation_rotation(pile_t *pile) {
    validation_calculs(pile);
    if (iloc(pile, 1)->valeur > taille(pile)) {
        eprintf("main: rotation: Erreur: Nombre d'elements rotatifs est superieur a la taille de la pile\n");
        exit(15);
    }
}