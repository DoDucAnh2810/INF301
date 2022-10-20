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

#define MAX_DEPTH 512000

#define GRP_COMM -128

#define EMPTY -127

#define DEJA_FAIT '\0'

extern bool silent_mode;

struct cellule {
    char command;
    int valeur;
    struct cellule *grp_comm_tete;
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
    int nb_val;
    int nb_grp_comm;
};
typedef struct sequence sequence_t;


cellule_t* nouvelleCellule (void);

cellule_t *iloc(cellule_t *cel, int i);

void detruireCellule (cellule_t*);

void detruireSeq (cellule_t **cel_pnt);

cellule_t *dupliquerSeq(cellule_t *cel);

cellule_t *concatenerSeq(cellule_t *seq_tete_1, cellule_t *seq_tete_2);

int vide(sequence_t *seq);

void extraireCommande (sequence_t* seq, char *commande, cellule_t **grp_comm_tete_pnt);

void ajouter_en_tete(cellule_t **seq_tete, char comm, int valeur, cellule_t *grp_comm_tete);

void ajouter_en_queue(cellule_t *seq_tete, char comm, int valeur, cellule_t *grp_comm_tete);

void conversion (char *texte, sequence_t *seq);

void afficher (sequence_t* seq, char space);


#endif
