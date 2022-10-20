#include "terrain.h"
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *f;
  Terrain t;
  int x, y;
  erreur_terrain err;
  char nom_fichier[NOM_TAILLE_MAX];

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  err = lire_terrain(f, &t, &x, &y);
  while (err == ERREUR_FICHIER) {
    printf("Veuillez saisir un autre fichier : ");
    scanf("%s", nom_fichier);
    f = fopen(nom_fichier, "r");
    err = lire_terrain(f, &t, &x, &y);
  }
  FILE *g;
  g = fopen("terr_out.txt", "w");
  ecrire_terrain(g, &t, x, y);
  fclose(f);
  afficher_terrain(&t);
  printf("Position initiale du robot : (%d, %d)\n", x, y);
}
