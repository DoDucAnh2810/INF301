#include <stdlib.h>
#include <assert.h>
#include "listes.h"
#include "validation.h"
#include "piles.h"


void init_pile(pile_t *pile) {
    assert(pile != NULL);
    pile->tete = NULL;
    pile->nb_valeur = 0;
    pile->nb_groupe = 0;
}


void empiler(pile_t *pile, int val, cellule_t *groupe) {
    if (val != GROUPE) {
        ajouter_en_tete(pile, EMPTY, val, NULL);
        pile->nb_valeur++;
    } else {
        ajouter_en_tete(pile, GROUPE, GROUPE, groupe);
        pile->nb_groupe++;
    }
}


void depiler(pile_t *pile, int *out_pnt, cellule_t **groupe_pnt) {
    validation_pas_vide(pile);
    if (out_pnt != NULL){
        *out_pnt = pile->tete->valeur;
        pile->nb_valeur--;
    } else if (groupe_pnt != NULL) {
        *groupe_pnt = pile->tete->groupe;
        pile->nb_groupe--;
    }
    detruire_tete(pile);
}


void addition(pile_t *pile) {
    validation_calculs(pile);
    int x, y;
    depiler(pile, &y, NULL);
    depiler(pile, &x, NULL);
    empiler(pile, x + y, NULL);
}


void soustraction(pile_t *pile) {
    validation_calculs(pile);
    int x, y;
    depiler(pile, &y, NULL);
    depiler(pile, &x, NULL);
    empiler(pile, x - y, NULL);
}


void multiplication(pile_t *pile) {
    validation_calculs(pile);
    int x, y;
    depiler(pile, &y, NULL);
    depiler(pile, &x, NULL);
    empiler(pile, x * y, NULL);
}


cellule_t *expr_conditionelle(pile_t *pile) {
    validation_expr_conditionelle(pile);
    int boolean; cellule_t *groupe_vrai, *groupe_faux;
    depiler(pile, NULL, &groupe_faux);
    depiler(pile, NULL, &groupe_vrai);
    depiler(pile, &boolean, NULL);
    if (boolean) {
        detruire_groupe(&groupe_faux);
        return groupe_vrai;
    } else {
        detruire_groupe(&groupe_vrai);
        return groupe_faux;
    }
}


cellule_t *executer(pile_t *pile) {
    validation_executer(pile);
    cellule_t *groupe;
    depiler(pile, NULL, &groupe);
    return groupe;
}


void echanger(pile_t *pile) {
    validation_echanger(pile);
    cellule_t *cel_1 = pile->tete;
    cellule_t *cel_2 = pile->tete->suivant;
    cellule_t *reste = pile->tete->suivant->suivant;
    pile->tete = cel_2;
    cel_2->suivant = cel_1;
    cel_1->suivant = reste;
}

void cloner(pile_t *pile) {
    validation_pas_vide(pile);
    empiler(pile, pile->tete->valeur, duplication_groupe(pile->tete->groupe));
}

cellule_t *boucle(pile_t *pile) {
    validation_boucle(pile);
    if (pile->tete->valeur == 0) {
        detruire_tete(pile);
        detruire_tete_avec_groupe(pile);
        return NULL;
    } else {
        pile->tete->valeur--;
        return duplication_groupe(pile->tete->suivant->groupe);
    }
}


void ignorer(pile_t *pile) {
    validation_pas_vide(pile);
    cellule_t *groupe;
    depiler(pile, NULL, &groupe);
    detruire_groupe(&groupe);
}


void rotation(pile_t *pile) {
    validation_rotation(pile);
    int nb_rotation, pas;
    depiler(pile, &pas, NULL);
    depiler(pile, &nb_rotation, NULL);
    pas = pas % nb_rotation;
    if (pas == 0) 
        return;
    cellule_t *old_tete = pile->tete;
    cellule_t *old_end_rotation = iloc(pile, nb_rotation-1);
    cellule_t *new_end_rotation = iloc(pile, nb_rotation-1 - pas);
    pile->tete = new_end_rotation->suivant;
    new_end_rotation->suivant = old_end_rotation->suivant;
    old_end_rotation->suivant = old_tete;
}


void inverser(pile_t *pile) {
    assert(pile != NULL);
    cellule_t *precedant = NULL, *cel = pile->tete, *suivant;
    while (cel != NULL) {
        suivant = cel->suivant;
        cel->suivant = precedant;
        precedant = cel;
        cel = suivant;
    }
    pile->tete = precedant;
}




