#include "client.h"
#include "crypteOperations.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

void crypteMove_decoder_special(char * enc, char * txt) {
    char buffer[2000000]; 
    int id_enc, mod_8;
    int len_txt = 100;
    id_enc = strlen(enc) - 1;
    
    while (id_enc >= 0) {
        mod_8 = enc[id_enc] % 8;
        strcpy(buffer, txt + len_txt - mod_8);
        txt[len_txt - mod_8] = '\0';
        strcat(buffer, txt);
        strcpy(txt + 1, buffer);
        txt[0] = enc[id_enc--];
        len_txt++;
        printf("%d\n", id_enc);
    }
    txt[len_txt] = '\0';
}

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    
    char txt[2000000] = ""; char enc[2000000] = ""; char aide[101]; char clef[101]; int switch_val[100]; int val_list[100]; int len_switch = 0; char passe[101];
    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12115958 DO", reponse);
    envoyer_recevoir("load OneMillion", reponse);
    crypteMove_decoder(reponse, txt);
    printf("\n%s\n", txt);
    txt[0] = '\0';
    envoyer_recevoir("aide", aide);
    int i;
    for (i = 0; i < 9999; i++) {
        strcat(enc, aide);
    }
    for (i = 0; i < 100; i++) {
        txt[i] = -100 + i;
    }
    txt[100] = '\0';
    enc[999900] = '\0';
    crypteMove_decoder_special(enc, txt);
    for (i = 0; i < 100; i++) {
        if (txt[i] >= 0)
            passe[i] = txt[i];
        else {
            passe[i] = ' ';
            val_list[len_switch] = i;
            switch_val[len_switch] = txt[i] + 100;
            len_switch++;
        }
    }
    passe[100] = '\0';
    txt[0] = '\0';
    envoyer_recevoir("start", reponse);
    crypteMove_decoder(reponse, clef);
    for (i = 0; i < len_switch; i++) {
        passe[val_list[i]] = clef[switch_val[i]];
    }
    envoyer_recevoir(passe, reponse);
    crypteMove_decoder(reponse, txt);
    printf("\n%s\n", txt);
    txt[0] = '\0';

    envoyer_recevoir("C'est fini?", reponse);
    return 0;
}