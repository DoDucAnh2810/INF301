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


cellule_t* nouvelle_cellule (void) {
    cellule_t *cel = malloc(sizeof(cellule_t));
    if (cel == NULL) {
        printf("Erreur Fatale: Plus de memoire pour proceder la commande!\n");
        exit(1);
    }
    return cel;
}

void ajouter_en_tete(sequence_t *seq, char commande, int valeur, cellule_t *groupe) {
    cellule_t *new_tete = nouvelle_cellule();
    new_tete->commande = commande;
    new_tete->valeur = valeur;
    new_tete->groupe = groupe;
    new_tete->suivant = seq->tete;
    seq->tete = new_tete;
}


void detruire_cellule (cellule_t *cel) {
    free(cel);
}

void detruire_seq_auxiliary (cellule_t *cel) {
    if (cel != NULL) {
        if (cel->commande == GRP_COMM && cel->valeur == GRP_COMM) {
            detruire_seq_auxiliary(cel->groupe);
        }
        detruire_seq_auxiliary(cel->suivant);
        detruire_cellule(cel);
    }
}
void detruire_seq(cellule_t **cel_pnt) {
    detruire_seq_auxiliary(*cel_pnt);
    *cel_pnt = NULL;
}

void detruire_tete(sequence_t *seq) {
    assert(seq != NULL);
    cellule_t *old_tete = seq->tete;
    seq->tete = seq->tete->suivant;
    detruire_cellule(old_tete);
}

void detruire_tete_avec_groupe(sequence_t *seq) {
    assert(seq != NULL);
    detruire_seq(&seq->tete->groupe);
    detruire_tete(seq);
}


cellule_t *iloc(cellule_t *cel, int i) {
    assert(i >= 0);
    if (i == 0)
        return cel;
    else 
        return iloc(cel->suivant, i - 1);
}

cellule_t *queue(cellule_t *cel) {
    assert(cel != NULL);
    while (cel->suivant != NULL) 
        cel = cel->suivant;
    return cel;
}

cellule_t *dupliquer_seq(cellule_t *cel) {
    if (cel == NULL)
        return NULL;
    cellule_t *duplication = nouvelle_cellule();
    duplication->commande = cel->commande;
    duplication->valeur = cel->valeur;
    duplication->groupe = dupliquer_seq(cel->groupe);
    duplication->suivant = dupliquer_seq(cel->suivant);
    return duplication;
}

cellule_t *concatener_seq(cellule_t *seq_tete_1, cellule_t *seq_tete_2) {
    if (seq_tete_1 == NULL)
        return seq_tete_2;
    queue(seq_tete_1)->suivant = seq_tete_2;
    return seq_tete_1;
}


int vide(sequence_t *seq) {
    return seq == NULL || seq->tete == NULL;
}

void extraire_commande (sequence_t *seq, char *commande, cellule_t **groupe) {
    assert(seq != NULL);
    *commande = seq->tete->commande;
    *groupe = seq->tete->groupe;
    detruire_tete(seq);
}


cellule_t *conversion_recur_aux_plus(char *texte, int len_txt, int *i) {
    while (*i < len_txt && isspace(texte[*i])) 
        *i += 1;
    if (*i >= len_txt || texte[*i] == '}') {
        *i += 1;
        return NULL;
    } else {
        cellule_t *cel = nouvelle_cellule();

        if (texte[*i] == '{') {
            cel->commande = GRP_COMM;
            cel->valeur = GRP_COMM;
            *i += 1;
            cel->groupe = conversion_recur_aux_plus(texte, len_txt, i);
        } else {
            cel->commande = texte[*i];
            cel->valeur = EMPTY;
            cel->groupe = NULL;
            *i += 1;
        }
        cel->suivant = conversion_recur_aux_plus(texte, len_txt, i);
        return cel;
    }
}

void ajouter_depth(sequence_list_t *depth_list, sequence_t *seq) {
    sequence_cellule_t *new_depth = malloc(sizeof(sequence_cellule_t));
    if (seq == NULL)
        seq = malloc(sizeof(sequence_t));
    new_depth->seq = seq;
    new_depth->seq->tete = NULL;
    new_depth->suivant = depth_list->tete;
    depth_list->tete = new_depth;
}
void detruire_top_depth(sequence_list_t *depth_list, int top_level) {
    sequence_cellule_t *old_depth = depth_list->tete;
    depth_list->tete = depth_list->tete->suivant;
    if (!top_level)
        free(old_depth->seq);
    free(old_depth);   
}
void conversion (char *texte, sequence_t *seq) {
    assert(seq != NULL && seq->tete == NULL);
    sequence_list_t depth_list; 
    ajouter_depth(&depth_list, seq);
    int i;
    for (i = strlen(texte) - 1; i >= 0; i--) {
        if (texte[i] == '}') {
            ajouter_depth(&depth_list, NULL);
        } else if (texte[i] == '{') {
            ajouter_en_tete(depth_list.tete->suivant->seq, GRP_COMM, GRP_COMM, depth_list.tete->seq->tete);
            detruire_top_depth(&depth_list, false);
        } else if (!isspace(texte[i])) {
            ajouter_en_tete(depth_list.tete->seq, texte[i], EMPTY, NULL);
        }
    }
    detruire_top_depth(&depth_list, true);
   //int i = 0;
   //seq->tete = conversion_recur_aux_plus(texte, strlen(texte), &i);
}


void afficher_auxiliary(cellule_t *seq_tete, char space) {
    cellule_t *cel = seq_tete;
    while (cel != NULL) {
        if (cel->commande == GRP_COMM && cel->valeur == GRP_COMM) {
            printf("{ ");
            afficher_auxiliary(cel->groupe, space);
            printf("} ");
        } else if (cel->commande == EMPTY) 
            printf("%d%c", cel->valeur, space);
        else
            printf("%c%c", cel->commande, space);
        cel = cel->suivant;
    }
}
void afficher (sequence_t* seq, char space) {
    assert (seq != NULL); /* Le pointeur doit être valide */
    afficher_auxiliary(seq->tete, space);
    printf("\n");
}
