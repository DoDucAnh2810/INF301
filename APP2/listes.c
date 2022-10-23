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
 

bool silent_mode = false;


cellule_t* nouvelle_cellule (void) { // create a new cell
    cellule_t *cel = malloc(sizeof(cellule_t));
    if (cel == NULL) {
        eprintf("main: nouvelle_cellule: Erreur: Plus de memoire\n");
        exit(1);
    }
    return cel;
}


void ajouter_en_tete(sequence_t *seq, char commande, int valeur, cellule_t *groupe) { // add a cell to the head of a linked list
    // create new cell
    cellule_t *new_tete = nouvelle_cellule();
    new_tete->commande = commande;
    new_tete->valeur = valeur;
    new_tete->groupe = groupe;
    
    // change the head
    new_tete->suivant = seq->tete;
    seq->tete = new_tete;
}


void detruire_cellule (cellule_t *cel) { // free the memory at a cell
    free(cel);
}


void detruire_groupe_auxiliary (cellule_t *cel) { // free ALL memory related to a cell
    cellule_t *old_cel;
    while (cel != NULL) {
        if (cel->commande == GROUPE) // the cell also contains a group to be free
            detruire_groupe_auxiliary(cel->groupe); // recursively destroy it
        old_cel = cel;
        cel = cel->suivant;
        detruire_cellule(old_cel);
    }
} 
void detruire_groupe(cellule_t **groupe_pointeur) { // free ALL memory related to a cell pointer and set that cell to be NULL
    detruire_groupe_auxiliary(*groupe_pointeur);
    *groupe_pointeur = NULL;
}


void detruire_tete(sequence_t *seq) {
    assert(seq != NULL && seq->tete != NULL);
    cellule_t *old_tete = seq->tete;
    seq->tete = seq->tete->suivant;
    detruire_cellule(old_tete);
}


cellule_t *iloc(sequence_t *seq, int i) {
    assert(seq != NULL && seq->tete != NULL && i >= 0);
    cellule_t *cel = seq->tete;
    while (cel->suivant != NULL && i > 0) {
        cel = cel->suivant;
        i--;
    }
    if (i > 0) {
        eprintf("main: iloc: Erreur: Index hors plage\n");
        exit(2);
    }
    return cel;
    
}


cellule_t *queue(cellule_t *cel) {
    assert(cel != NULL);
    while (cel->suivant != NULL) 
        cel = cel->suivant;
    return cel;
}


cellule_t *concatenation_groupe(cellule_t *groupe_1, cellule_t *groupe_2) {
    if (groupe_1 == NULL)
        return groupe_2;
    queue(groupe_1)->suivant = groupe_2;
    return groupe_1;
}


cellule_t *duplication_groupe(cellule_t *cel) {
    if (cel == NULL)
        return NULL;
    cellule_t *duplication = nouvelle_cellule();
    duplication->commande = cel->commande;
    duplication->valeur = cel->valeur;
    duplication->groupe = duplication_groupe(cel->groupe);
    duplication->suivant = duplication_groupe(cel->suivant);
    return duplication;
}


int taille(sequence_t *seq) {
    assert(seq != NULL);
    return seq->nb_valeur + seq->nb_groupe;
}


int vide(sequence_t *seq) {
    return seq == NULL || seq->tete == NULL;
}


void extraire_commande (sequence_t *seq, char *commande, cellule_t **groupe) {
    assert(seq != NULL && seq->tete != NULL);
    *commande = seq->tete->commande;
    *groupe = seq->tete->groupe;
    detruire_tete(seq);
}


void afficher_auxiliary(cellule_t *groupe) {
    cellule_t *cel = groupe;
    while (cel != NULL) {
        if (cel->commande == GROUPE) {
            printf("{ ");
            afficher_auxiliary(cel->groupe);
            printf("} ");
        } else if (cel->commande == EMPTY) 
            printf("%d ", cel->valeur);
        else
            printf("%c ", cel->commande);
        cel = cel->suivant;
    }
}
void afficher (sequence_t *seq) {
    assert (seq != NULL);
    afficher_auxiliary(seq->tete);
    printf("\n");
}
