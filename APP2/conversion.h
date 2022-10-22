#ifndef CONVERSION_H
#define CONVERSION_H


#include "listes.h"


struct depth {
    sequence_t *seq;
    struct depth *suivant;
};
typedef struct depth depth_t;

struct depth_liste {
    depth_t *tete;
};
typedef struct depth_liste depth_liste_t;


void conversion (char *texte, sequence_t *seq);


#endif