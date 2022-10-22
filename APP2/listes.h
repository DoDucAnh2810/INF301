#ifndef LISTES_H
#define LISTES_H

#include <stdbool.h>

/*
 * Pour réaliser des tests de performance, désactiver tous les 
 * affichages.
 * Pour cela, le plus simple est de redefinir les fonctions principales 
 * en decommentant les 3 lignes suivantes et en commentant l'ancienne 
 * definition de 'eprintf' juste dessous.
 */

#ifdef SILENT
 
#define printf(fmt, ...) (0)
#define eprintf(fmt, ...) (0)
#define putchar(c) (0)

#else

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#endif


#define GROUPE -128
#define EMPTY -127

extern bool silent_mode;

struct cellule {
    char commande;
    int valeur;
    struct cellule *groupe;
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
    int nb_valeur;
    int nb_groupe;
};
typedef struct sequence sequence_t;


cellule_t* nouvelle_cellule (void);

void ajouter_en_tete(sequence_t *seq, char comm, int valeur, cellule_t *groupe);

void detruire_cellule (cellule_t*);

void detruire_groupe (cellule_t **cel_pointeur);

void detruire_tete(sequence_t *seq);

void detruire_tete_avec_groupe(sequence_t *seq);

cellule_t *iloc(sequence_t *seq, int i);

cellule_t *queue(cellule_t *cel);

cellule_t *concatenation_groupe(cellule_t *groupe_1, cellule_t *groupe_2);

cellule_t *duplication_groupe(cellule_t *cel);

int vide(sequence_t *seq);

void extraire_commande (sequence_t* seq, char *commande, cellule_t **groupe_pnt);

void afficher (sequence_t* seq);


#endif
