
#include "terrain.h"
#include "robot.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Largeur d'un terrain */
int largeur(Terrain *t) {
  return t->largeur;
}

/* Hauteur d'un terrain */
int hauteur(Terrain *t) {
  return t->hauteur;
}

/* Indique si la case de coordonnées (x,y) est libre
   Renvoie vrai ssi les 3 conditions suivantes sont vraies :
    - 0 <= x < largeur
    - 0 <= y < hauteur
    - t.tab[x][y] = LIBRE
 */
int est_case_libre(Terrain *t, int x, int y) {
  return ((0 <= x && x < largeur(t)) &&
          (0 <= y && y < hauteur(t)) &&
          (t->tab[x][y] == LIBRE));
}


erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y) {
  if (f == NULL) {
    return ERREUR_FICHIER;
  }

  char car;

  // Lecture de la largeur
  if (feof(f)) 
    return ERREUR_FICHIER;
  fscanf(f, "%d", &t->largeur);
  if (largeur(t) < 0 || largeur(t) > DIM_MAX) {
    printf("Erreur: Largeur invalide.\n");
    return ERREUR_FICHIER;
  }
  if (feof(f)) 
    return ERREUR_FICHIER;
  fscanf(f, "%c", &car);
  if (car == '\r') {
    if (feof(f)) 
      return ERREUR_FICHIER;
    fscanf(f, "%c", &car);
  }
  if (car != '\n') {
    printf("Erreur: La largeur doit etre un nombre sur une ligne separee.\n");
    return ERREUR_FICHIER;
  }

  // Lecture de la hauteur
  if (feof(f)) 
    return ERREUR_FICHIER;
  fscanf(f, "%d", &t->hauteur);
  if (hauteur(t) < 0 || hauteur(t) > DIM_MAX) {
    printf("Erreur: Hauteur invalide.\n");
    return ERREUR_FICHIER;
  }
  if (feof(f)) 
    return ERREUR_FICHIER;
  fscanf(f, "%c", &car);
  if (car == '\r') {
    if (feof(f)) 
      return ERREUR_FICHIER;
    fscanf(f, "%c", &car);
  }
  if (car != '\n') {
    printf("Erreur: La hauteur doit etre un nombre sur une ligne separee.\n");
    return ERREUR_FICHIER;
  }

  // Lecture du terrain
  int lig, col, nb_init = 0; 
  for (lig = 0; lig < hauteur(t); lig++) {
    for (col = 0; col < largeur(t); col++) {
      if (feof(f)) 
        return ERREUR_FICHIER;
      fscanf(f, "%c", &car);
      if (car == '\r') {
        if (col != 0) {
          printf("Erreur: Forme du terrain non conformee aux dimensions!\n");
          return ERREUR_FICHIER;
        } else {
          if (feof(f)) 
            return ERREUR_FICHIER;
          fscanf(f, "%c", &car);
        }
      }
      if (car == '\n') {
        if (col != 0) {
          printf("Erreur: Forme du terrain non conformee aux dimensions!\n");
          return ERREUR_FICHIER;
        } else {
          if (feof(f)) 
            return ERREUR_FICHIER;
          fscanf(f, "%c", &car);
        }
      }
      switch (car) {
        case '.':
          t->tab[col][lig] = LIBRE;
          break;
        case '#':
          t->tab[col][lig] = ROCHER;
          break;
        case '~':
          t->tab[col][lig] = EAU;
          break;
        case 'C':
          if (nb_init > 0) {
            printf("Erreur: Plusieurs positions initiales détectees.\n");
            return ERREUR_FICHIER;
          }
          *x = col;
          *y = lig;
          nb_init++;
          break;
        default:
          printf("Erreur: Caratere inconnue avec le ASCII code %d.\n", car);
          return ERREUR_FICHIER;
      }
    }
  }
  if (nb_init == 0) {
    printf("Erreur: Position initiale manquante.\n");
    return ERREUR_FICHIER;
  }
  return OK;
}


/* Affichage d'un terrain t sur la sortie standard */
void afficher_terrain(Terrain *t) {
  int lig, col;
  for (lig = 0; lig < hauteur(t); lig++) {
    for (col = 0; col < largeur(t); col++) {
      switch (t->tab[col][lig]) {
        case LIBRE:
          printf(". ");
          break;
        case ROCHER:
          printf("# ");
          break;
        case EAU:
          printf("~ ");
          break;
      }
    }
    printf("\n");
  }
}

/* Écriture d'un terrain t dans un fichier f ouvert en écriture.
   x et y contiennent les coordonnées du robot
   Le terrain est écrit au format lisible par lire_terrain */
void ecrire_terrain(FILE *f, Terrain *t, int x, int y) {
  fprintf(f, "%d\n", largeur(t));
  fprintf(f, "%d\n", hauteur(t));
  int col, lig;
  for (lig = 0; lig < hauteur(t); lig++) {
    for (col = 0; col < largeur(t); col++) {
      if (col == x && lig == y) 
        fprintf(f, "C");
      else
        switch (t->tab[col][lig]) {
          case LIBRE:
            fprintf(f, ".");
            break;
          case ROCHER:
            fprintf(f, "#");
            break;
          case EAU:
            fprintf(f, "~");
            break;
        }
    }
    fprintf(f, "\n");
  }
}