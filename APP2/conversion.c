#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "listes.h"
#include "validation.h"
#include "conversion.h"


void ajouter_depth(depth_liste_t *depth_liste, sequence_t *seq) {
    depth_t *new_depth = malloc(sizeof(depth_t));
    if (new_depth == NULL || seq == NULL) {
        eprintf("main: ajouter_depth: Erreur: Plus de memoire\n");
        exit(1);
    } 
    new_depth->seq = seq;
    new_depth->seq->tete = NULL;
    new_depth->suivant = depth_liste->tete;
    depth_liste->tete = new_depth;
}


void detruire_depth(depth_liste_t *depth_liste) {
    depth_t *old_depth = depth_liste->tete;
    depth_liste->tete = depth_liste->tete->suivant;
    free(old_depth->seq);
    free(old_depth);   
}


void conversion (char *texte, sequence_t *seq) {
    assert(seq != NULL && seq->tete == NULL);
    int len_txt = strlen(texte);
    validation_texte_conversion(texte, len_txt);
    depth_liste_t depth_liste; 
    ajouter_depth(&depth_liste, seq);
    int i;
    for (i = len_txt - 1; i >= 0; i--) {
        if (texte[i] == '}') {
            ajouter_depth(&depth_liste, malloc(sizeof(sequence_t)));
        } else if (texte[i] == '{') {
            ajouter_en_tete(depth_liste.tete->suivant->seq, GROUPE, GROUPE, depth_liste.tete->seq->tete);
            detruire_depth(&depth_liste);
        } else if (!isspace(texte[i])) {
            ajouter_en_tete(depth_liste.tete->seq, texte[i], EMPTY, NULL);
        }
    }
    free(depth_liste.tete);
}