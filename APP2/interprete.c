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
    // Version temporaire a remplacer par une lecture des commandes dans la
    // liste chainee et leur interpretation.
    assert(seq != NULL);
    
    pile_t pile;
    initPile(&pile);

    if (!silent_mode) { 
        printf ("Programme: ");
        afficher(seq, ' ');
        printf ("\n");
        if (debug) stop();
    }


    char commande; int valeur; cellule_t *groupe; cellule_t *nouveau_processus;
    int ret;         //utilisée pour les valeurs de retour

    while (!vide(seq)) {
        extraire_commande(seq, &commande, &groupe);

        switch (commande) {
            /* Ici on avance tout le temps, à compléter pour gérer d'autres commandes */

            case 'A':
                ret = avance();
                if (ret == VICTOIRE) {
                    detruire_seq(&seq->tete);
                    detruire_seq(&pile.tete);
                    return VICTOIRE; 
                } else if (ret == RATE) { 
                    detruire_seq(&seq->tete);
                    detruire_seq(&pile.tete);
                    return RATE;   
                }
                break; /* à ne jamais oublier !!! */
            case 'D':
                droite();
                break;
            case 'G':
                gauche();
                break;
            case '0' ... '9':
                empiler(&pile, commande - '0', NULL); 
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
            case GRP_COMM:
                empiler(&pile, GRP_COMM, groupe);
                break;
            case '?':
                nouveau_processus = expr_conditionelle(&pile);
                seq->tete = concatener_seq(nouveau_processus, seq->tete);
                break;
            case '!':
                nouveau_processus = executer(&pile);
                seq->tete = concatener_seq(nouveau_processus, seq->tete);
                break;
            case 'X':
                echanger(&pile);
                break;
            case 'C':
                cloner(&pile);
                break;
            case 'B':
                nouveau_processus = boucle(&pile);
                if (nouveau_processus != NULL)
                    ajouter_en_tete(seq, 'B', EMPTY, NULL);
                seq->tete = concatener_seq(nouveau_processus, seq->tete);
                break;
            case 'I':
                ignorer(&pile);
                break;
            case 'R':
                rotation(&pile);
                break;
            default:
                eprintf("Caractère inconnu: '%c'\n", commande);
        }
        /* Affichage pour faciliter le debug */
        if (!silent_mode) {
            afficherCarte();
            printf ("Programme: ");
            afficher(seq, ' ');
            printf ("Pile: ");
            afficher(&pile, ' ');
            printf("\n");
            if (debug) stop();
        }
    }
    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */
    detruire_seq(&pile.tete);
    assert(pile.tete == NULL);
    return CIBLERATEE;
}
