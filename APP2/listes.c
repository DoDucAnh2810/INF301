#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
 

/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


cellule_t* nouvelleCellule (void) {
    cellule_t *cel = malloc(sizeof(cellule_t));
    return cel;
}

cellule_t *queue(cellule_t *cel) {
    if (cel == NULL)
        return NULL;
    cellule_t *tmp = cel;
    while (tmp->suivant != NULL) 
        tmp = tmp->suivant;
    return tmp;
}

cellule_t *iloc(cellule_t *cel, int i) {
    if (i < 0) {
        printf("Erreur: Indice invalide!\n");
        exit(10);
    }
    if (i == 0)
        return cel;
    else 
        return iloc(cel->suivant, i - 1);
}


void detruireCellule (cellule_t *cel) {
    free(cel);
}


void detruireSeq_recur_aux (cellule_t *cel) {
    if (cel != NULL) {
        if (cel->command == GRP_COMM && cel->valeur == GRP_COMM) {
            detruireSeq_recur_aux(cel->grp_comm_tete);
        }
        detruireSeq_recur_aux(cel->suivant);
        detruireCellule(cel);
    }
}
void detruireSeq(cellule_t **cel_pnt) {
    detruireSeq_recur_aux(*cel_pnt);
    *cel_pnt = NULL;
}



int vide(sequence_t *seq) {
    return seq == NULL || seq->tete == NULL;
}


void extraireCommande (sequence_t *seq, char *commande, cellule_t **grp_comm_tete) {
    assert(seq != NULL);
    *commande = seq->tete->command;
    *grp_comm_tete = seq->tete->grp_comm_tete;
    cellule_t *suiv = seq->tete->suivant;
    detruireCellule(seq->tete);
    seq->tete = suiv;
}


void ajouter_en_tete(cellule_t **seq_tete_pnt, char comm, int valeur, cellule_t *grp_comm_tete) {
    cellule_t *new_tete = nouvelleCellule();
    if (new_tete == NULL) {
        printf("Erreur Fatale: Plus de memoire pour proceder la commande!\n");
        exit(1);
    }
    new_tete->command = comm;
    new_tete->valeur = valeur;
    new_tete->grp_comm_tete = grp_comm_tete;
    new_tete->suivant = *(seq_tete_pnt);
    *seq_tete_pnt = new_tete;
}


void ajouter_en_queue(cellule_t *seq_tete, char comm, int valeur, cellule_t *grp_comm_tete) {
    assert(seq_tete != NULL);
    cellule_t *new_queue = nouvelleCellule();
    new_queue->command = comm;
    new_queue->valeur = valeur;
    new_queue->grp_comm_tete = grp_comm_tete;
    new_queue->suivant = NULL;
    queue(seq_tete)->suivant = new_queue;
}

cellule_t *dupliquerSeq(cellule_t *cel) {
    if (cel == NULL)
        return NULL;
    cellule_t *duplication = nouvelleCellule();
    duplication->command = cel->command;
    duplication->valeur = cel->valeur;
    duplication->grp_comm_tete = dupliquerSeq(cel->grp_comm_tete);
    duplication->suivant = dupliquerSeq(cel->suivant);
    return duplication;
}

cellule_t *concatenerSeq(cellule_t *seq_tete_1, cellule_t *seq_tete_2) {
    if (seq_tete_1 == NULL) {
        return seq_tete_2;
    }
    queue(seq_tete_1)->suivant = seq_tete_2;
    return seq_tete_1;
}


cellule_t *conversion_recur_aux_plus(char *texte, int len_txt, int *i) {
    while (*i < len_txt && isspace(texte[*i])) 
        *i += 1;
    if (*i >= len_txt || texte[*i] == '}') {
        *i += 1;
        return NULL;
    } else {
        cellule_t *cel = nouvelleCellule();
        if (cel == NULL) {
            printf("Erreur Fatale: Plus de memoire pour proceder la commande!\n");
            exit(1);
        }
        if (texte[*i] == '{') {
            cel->command = GRP_COMM;
            cel->valeur = GRP_COMM;
            *i += 1;
            cel->grp_comm_tete = conversion_recur_aux_plus(texte, len_txt, i);
        } else {
            cel->command = texte[*i];
            cel->valeur = EMPTY;
            cel->grp_comm_tete = NULL;
            *i += 1;
        }
        cel->suivant = conversion_recur_aux_plus(texte, len_txt, i);
        return cel;
    }
}

void conversion (char *texte, sequence_t *seq) {
    assert(seq != NULL && seq->tete == NULL);
    //conversion_recur_aux(texte, &(seq->tete));
    int i = 0;
    seq->tete = conversion_recur_aux_plus(texte, strlen(texte), &i);
}


void afficher_recur_aux(cellule_t *seq_tete, char space) {
    cellule_t *cel = seq_tete;
    while (cel != NULL) {
        if (cel->command == GRP_COMM && cel->valeur == GRP_COMM) {
            printf("{ ");
            afficher_recur_aux(cel->grp_comm_tete, space);
            printf("} ");
        } else if (cel->command == EMPTY) 
            printf("%d%c", cel->valeur, space);
        else
            printf("%c%c", cel->command, space);
        cel = cel->suivant;
    }
}
void afficher (sequence_t* seq, char space) {
    assert (seq != NULL); /* Le pointeur doit être valide */
    afficher_recur_aux(seq->tete, space);
    printf("\n");
}

