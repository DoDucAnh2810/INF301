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
    char commande;
    int valeur;
    struct cellule *groupe;
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
    int nb_val;
    int nb_grp_comm;
};
typedef struct sequence sequence_t;

struct sequence_cellule {
    sequence_t *seq;
    struct sequence_cellule *suivant;
};
typedef struct sequence_cellule sequence_cellule_t;

struct sequence_list {
    sequence_cellule_t *tete;
};
typedef struct sequence_list sequence_list_t;

cellule_t* nouvelle_cellule (void);

cellule_t *iloc(cellule_t *cel, int i);

cellule_t *queue(cellule_t *cel);

void detruire_cellule (cellule_t*);

void detruire_seq (cellule_t **cel_pnt);

void detruire_tete(sequence_t *seq);

void detruire_tete_avec_groupe(sequence_t *seq);

cellule_t *dupliquer_seq(cellule_t *cel);

cellule_t *concatener_seq(cellule_t *seq_tete_1, cellule_t *seq_tete_2);

int vide(sequence_t *seq);

void extraire_commande (sequence_t* seq, char *commande, cellule_t **groupe_pnt);

void ajouter_en_tete(sequence_t *seq, char comm, int valeur, cellule_t *groupe);

void conversion (char *texte, sequence_t *seq);

void afficher_auxiliary(cellule_t *seq_tete, char space);

void afficher (sequence_t* seq, char space);


#endif
