#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12115958 DO", reponse);
    envoyer_recevoir("load tutoriel", reponse);
    envoyer_recevoir("depart", reponse);
    envoyer_recevoir("oui", reponse);
    envoyer_recevoir("4", reponse);
    envoyer_recevoir("blanc", reponse);
    envoyer_recevoir("Pincemoi", reponse);
    envoyer_recevoir("tutoriel", reponse);
    envoyer_recevoir("C'est fini?", reponse);

    return 0;
}
