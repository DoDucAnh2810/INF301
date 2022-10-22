#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "piles.h"
 

/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}



int interprete (sequence_t* seq, bool debug)
{
    if (!silent_mode) {
        printf ("Programme: ");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }

    cellule_t *groupe; cellule_t *nouveau_processus;  
    char commande; int valeur, ret;     
    pile_t pile;
    init_pile(&pile);

    while (!vide(seq)) {
        extraire_commande(seq, &commande, &groupe);

        switch (commande) {
            case 'A':
                ret = avance();
                if (ret == VICTOIRE) {
                    detruire_groupe(&seq->tete);
                    detruire_groupe(&pile.tete);
                    return VICTOIRE; 
                } else if (ret == RATE) { 
                    detruire_groupe(&seq->tete);
                    detruire_groupe(&pile.tete);
                    return RATE;   
                }
                break; 
            case 'D':
                droite();
                break;
            case 'G':
                gauche();
                break;
            case '0' ... '9':
                empiler(&pile, commande - '0', NULL); 
                break;
            case GROUPE:
                empiler(&pile, GROUPE, groupe);
                break;
            case '+':
                addition(&pile);
                break;
            case '-':
                soustraction(&pile);
                break;
            case '*':
                multiplication(&pile);
                break;
            case 'M':
                depiler(&pile, &valeur, NULL);
                ret = mesure(valeur);
                empiler(&pile, ret, NULL);
                break;
            case 'P':
                depiler(&pile, &valeur, NULL);
                pose(valeur);
                break;
            case '?':
                nouveau_processus = expr_conditionelle(&pile);
                seq->tete = concatenation_groupe(nouveau_processus, seq->tete);
                break;
            case '!':
                nouveau_processus = executer(&pile);
                seq->tete = concatenation_groupe(nouveau_processus, seq->tete);
                break;
            case 'B':
                nouveau_processus = boucle(&pile);
                if (nouveau_processus != NULL)
                    ajouter_en_tete(seq, 'B', EMPTY, NULL);
                seq->tete = concatenation_groupe(nouveau_processus, seq->tete);
                break;
            case 'X':
                echanger(&pile);
                break;
            case 'C':
                cloner(&pile);
                break;
            case 'I':
                ignorer(&pile);
                break;
            case 'R':
                rotation(&pile);
                break;
            case 'Z':
                inverser(&pile);
                break;
            default:
                eprintf("Caractère inconnu: '%c'\n", commande);
        }
        if (!silent_mode){
            afficherCarte();
            printf ("Programme: ");
            afficher(seq);
            printf ("Pile: ");
            afficher(&pile);
            printf("\n");
            if (debug) stop();
        }
    }
    detruire_groupe(&pile.tete);
    return CIBLERATEE;
}
