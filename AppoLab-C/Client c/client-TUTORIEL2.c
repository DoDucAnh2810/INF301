#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

void capitalize(char * reponse, char * buffer) {
    int i;
    for (i = 0; i < MAXREP; i++) {
        if (islower(reponse[i]))
            buffer[i] = reponse[i] - 'a' + 'A';
        else
            buffer[i] = reponse[i];
    }
}

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char buffer[MAXREP];

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12115958 DO", reponse);
    envoyer_recevoir("load TUTORIEL", reponse);
    envoyer_recevoir("depart", reponse);
    envoyer_recevoir("OK", reponse);
    envoyer_recevoir("OUI", reponse);
    while (strcmp(reponse, "") != 0) {
        capitalize(reponse, buffer);
        envoyer_recevoir(buffer, reponse);
    }

    return 0;
}
