#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "listes.h"
#include "piles.h"


void initPile(pile_t *pile) {
    assert(pile != NULL);
    pile->tete = NULL;
    pile->nb_val = 0;
    pile->nb_grp_comm = 0;
}


int taille(pile_t *pile) {
    assert(pile != NULL);
    return pile->nb_val + pile->nb_grp_comm;
}


void empiler(pile_t *pile, int val, cellule_t *groupe) {
    if (val != GRP_COMM) {
        ajouter_en_tete(pile, EMPTY, val, NULL);
        pile->nb_val++;
    } else {
        ajouter_en_tete(pile, GRP_COMM, GRP_COMM, groupe);
        pile->nb_grp_comm++;
    }
}


void depiler(pile_t *pile, int *out_pnt, cellule_t **groupe_pnt) {
    assert(pile != NULL);
    if (pile->tete == NULL) {
        printf("Erreur: Ne peut pas depiler une pile vide!\n");
        exit(4);
    } 
    if (out_pnt != NULL){
        *out_pnt = pile->tete->valeur;
        pile->nb_val--;
    } else if (groupe_pnt != NULL) {
        *groupe_pnt = pile->tete->groupe;
        pile->nb_grp_comm--;
    }
    detruire_tete(pile);
}


int au_moins_2_nombre(pile_t *pile) {
    assert(pile != NULL);
    return pile->nb_val >= 2;
}


int au_moins_2_grp_comm_et_1_nombre(pile_t *pile) {
    assert(pile != NULL);
    return pile->nb_grp_comm >= 2 && pile->nb_val >= 1;
}


int au_moins_2_element(pile_t *pile) {
    assert(pile != NULL);
    return (pile->nb_val + pile->nb_grp_comm) >= 2;
}


void addition(pile_t *pile) {
    if (!au_moins_2_nombre(pile)) {
        printf("Erreur: Pas assez d'element dans la pile!\n");
        exit(2);
    }
    int x, y;
    depiler(pile, &y, NULL);
    depiler(pile, &x, NULL);
    if (x == GRP_COMM || y == GRP_COMM) {
        printf("Erreur: Impossible de faire l'additon sur un groupe de commande!\n");
        exit(3);
    }
    empiler(pile, x + y, NULL);
}


void soustraction(pile_t *pile) {
    if (!au_moins_2_nombre(pile)) {
        printf("Erreur: Pas assez d'element dans la pile!\n");
        exit(2);
    } 
    int x, y;
    depiler(pile, &y, NULL);
    depiler(pile, &x, NULL);
    if (x == GRP_COMM || y == GRP_COMM) {
        printf("Erreur: Impossible de faire la soustraction sur un groupe de commande!\n");
        exit(3);
    } 
    empiler(pile, x - y, NULL);
}


void multiplication(pile_t *pile) {
    if (!au_moins_2_nombre(pile)) {
        printf("Erreur: Pas assez d'element dans la pile!\n");
        exit(2);
    }
    int x, y;
    depiler(pile, &y, NULL);
    depiler(pile, &x, NULL);
    if (x == GRP_COMM || y == GRP_COMM) {
        printf("Erreur: Impossible de faire la multiplication sur un groupe de commande!\n");
        exit(3);
    } 
    empiler(pile, x * y, NULL);
}


cellule_t *expr_conditionelle(pile_t *pile) {
    if (!au_moins_2_grp_comm_et_1_nombre(pile)) {
        printf("Erreur: Expression conditionelle mauvaise!\n");
        exit(5);
    } 
    int boolean; cellule_t *grp_comm_vrai, *grp_comm_faux;
    depiler(pile, NULL, &grp_comm_faux);
    depiler(pile, NULL, &grp_comm_vrai);
    depiler(pile, &boolean, NULL);
    if (boolean == GRP_COMM) {
        printf("Erreur: Expression conditionelle mauvaise!\n");
        exit(5);
    }
    if (boolean) {
        detruire_seq(&grp_comm_faux);
        return grp_comm_vrai;
    } else {
        detruire_seq(&grp_comm_vrai);
        return grp_comm_faux;
    }
}


cellule_t *executer(pile_t *pile) {
    assert(pile != NULL);
    if (pile->tete == NULL) {
        printf("Erreur: Ne peut pas faire l'execution sur une pile vide!\n");
        exit(4);
    } else if (pile->tete->commande != GRP_COMM || pile->tete->valeur != GRP_COMM) {
        printf("Erreur: Ne peut pas executer un nombre!\n");
        exit(6);
    }
    cellule_t *groupe;
    depiler(pile, NULL, &groupe);
    return groupe;
}


void echanger(pile_t *pile) {
    if (!au_moins_2_element(pile)) {
        printf("Erreur: Pas assez d'element dans la pile!\n");
        exit(2);
    }
    cellule_t *cel_1 = pile->tete;
    cellule_t *cel_2 = pile->tete->suivant;
    cellule_t *reste = pile->tete->suivant->suivant;
    pile->tete = cel_2;
    cel_2->suivant = cel_1;
    cel_1->suivant = reste;
}

void cloner(pile_t *pile) {
    if (vide(pile)) {
        printf("Erreur: Ne peut pas cloner sur une pile vide!\n");
        exit(4);
    }
    empiler(pile, pile->tete->valeur, dupliquer_seq(pile->tete->groupe));
}

cellule_t *boucle(pile_t *pile) {
    if (pile->nb_grp_comm == 0 || pile->nb_val == 0) {
        printf("Erreur: Pas assez d'element dans la pile!\n");
        exit(2);
    } else if (pile->tete->valeur == GRP_COMM) {
        printf("Erreur: Un groupe de commande ne peut pas etre l'entier de la boucle!\n");
        exit(3);
    } else if (pile->tete->suivant->valeur != GRP_COMM) {
        printf("Erreur: Ne peut pas executer un entier!\n");
        exit(3);
    }
    if (pile->tete->valeur == 0) {
        detruire_tete(pile);
        detruire_tete_avec_groupe(pile);
        return NULL;
    } else {
        pile->tete->valeur--;
        return dupliquer_seq(pile->tete->suivant->groupe);
    }
}


void ignorer(pile_t *pile) {
    if (vide(pile)) {
        printf("Erreur: Ne peut pas ignorer sur une pile vide!\n");
        exit(4);
    }
    cellule_t *groupe;
    depiler(pile, NULL, &groupe);
    detruire_seq(&groupe);
}


void rotation(pile_t *pile) {
    assert(pile != NULL);
    int nb_rotation, pas;
    depiler(pile, &pas, NULL);
    depiler(pile, &nb_rotation, NULL);
    pas = pas % nb_rotation;
    if (pas != 0) {
        cellule_t *old_tete = pile->tete;
        cellule_t *old_end_rotation = iloc(pile->tete, nb_rotation-1);
        cellule_t *new_end_rotation = iloc(pile->tete, nb_rotation-1 - pas);
        pile->tete = new_end_rotation->suivant;
        new_end_rotation->suivant = old_end_rotation->suivant;
        old_end_rotation->suivant = old_tete;
    }
}




