#include "client.h"
#include "crypteOperations.h"
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


    char txt[MAXREP]; // char enc[MAXREP]; char aide[MAXREP]; char clef[MAXREP]; int len_txt = 0;
    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12115958 DO", reponse);

    envoyer_recevoir("load LostCause", reponse);
    crypteSeq_decoder(reponse, txt);
    printf("\n%s\n", txt);
    txt[0] = '\0';

    envoyer_recevoir("aide", reponse);
    crypteSeq_decoder(reponse, txt);
    printf("\n%s\n", txt);
    txt[0] = '\0';

    envoyer_recevoir("start", reponse);
    crypteAssoc_decoder(reponse, txt);
    printf("\n%s\n", txt);
    txt[0] = '\0';

    envoyer_recevoir("tout va bien", reponse);
    envoyer_recevoir("C'est fini?", reponse);
    return 0;
}