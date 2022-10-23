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
    int i;
    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12115958 DO", reponse);
    envoyer_recevoir("load leGateau", reponse);
    envoyer_recevoir("start", reponse);
    int j; int flag = 1; int stop = 0;
    while (strcmp(reponse, "") != 0) {
        if (reponse[0] == 'Y' && reponse[1] == 'o' && reponse[2] == 'u' && reponse[3] == ' ' && reponse[4] == 'f'){
            fgets (buffer, MAXMSG, stdin);
            envoyer_recevoir(buffer, reponse);            
        } else if (reponse[0] == 'P' && reponse[1] == 'r' && reponse[2] == 'e' && reponse[3] == 't' && reponse[4] == 'e'){
            fgets (buffer, MAXMSG, stdin);
            envoyer_recevoir(buffer, reponse);
            stop = 1;
        } else if (stop){
            fgets (buffer, MAXMSG, stdin);
            envoyer_recevoir(buffer, reponse);
        } else {
            i = 0;
            if (flag)
                while((!(isdigit(reponse[i]) && isdigit(reponse[i+1]) && isdigit(reponse[i+2]) && isdigit(reponse[i+3]) && isdigit(reponse[i+4])))) {
                    i++;
                }
            else
                i = 100000000;
            if (i >= (int)strlen(reponse)) {
                i = strrchr(reponse, ' ') - reponse + 1;
                flag = 0;
            } else {
                j = i;
                while(isdigit(reponse[j]))
                    j++;
                reponse[j] = '\0';
            }
            strcpy(buffer, reponse + i);
            envoyer_recevoir(buffer, reponse);
        }
    }
    return 0;
}
