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
    int decal; char passe[20] = "hasta la revolucion"; int i;
    envoyer_recevoir("login 12115958 DO", reponse);

    envoyer_recevoir("load planB", reponse);
    envoyer_recevoir("aide", reponse);
    decal = 'C' - reponse[0];
    for (i = 0; i < 19; i++) {
        if (passe[i] != ' ')  {
            passe[i] += decal;
            if (passe[i] < 'a')
                passe[i] += 26;
            else if (passe[i] > 'z')
                passe[i] -= 26;
        }
    }
    envoyer_recevoir("start", reponse);
    envoyer_recevoir(passe, reponse);
    envoyer_recevoir("C'est fini?", reponse);
    return 0;
}