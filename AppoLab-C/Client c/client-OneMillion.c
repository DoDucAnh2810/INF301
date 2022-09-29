#include "client.h"
#include "crypteOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXMSG MAXREP

void crypteMove_decoder_fast(char * enc, char * txt) {
    char * buffer = (char *)malloc(8000000);
    int start_buf = 7999999;
    int end_buf = 7999999;
    int len_buf = 0;
    int mod_8, i;
    int id_enc = strlen(enc) - 1;
    unsigned long len_txt = strlen(txt);
    if (len_txt > 0) {
        strcpy(buffer + start_buf - len_txt, txt);
        start_buf -= len_txt;
        len_buf = len_txt;
    }
    while (id_enc >= 0) {
        mod_8 = enc[id_enc] % 8;
        if (len_buf > mod_8) {
            for (i = end_buf - mod_8; i < end_buf; i++) {
                buffer[i - len_buf]  = buffer[i];
            }
            start_buf -= mod_8;
            end_buf -= mod_8;
        } 
        buffer[--start_buf] = enc[id_enc--];
        len_buf++;
    }
    buffer[end_buf] = '\0';
    strcpy(txt, buffer + start_buf);
    free(buffer);
}

int main() {
    clock_t start, end;
    double cpu_time_used;
    char reponse[MAXREP]; // pour stocker la réponse du serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    
    char txt[2000000] = ""; char enc[2000000] = ""; char aide[101];/* char clef[101] = "";*/ int switch_val[100]; int val_list[100]; int len_switch = 0; char passe[101];
    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12115958 DO", reponse);
    envoyer_recevoir("load OneMillion", reponse);
    crypteMove_decoder_fast(reponse, txt);
    printf("\n%s\n", txt);
    txt[0] = '\0';
    envoyer_recevoir("aide", aide);
    int i;
    for (i = 0; i < 9999; i++) {
        strcat(enc, aide);
    }
    strcat(enc, "0123456789");
    for (i = 0; i < 100; i++) {
        txt[i] = -100 + i;
    }
    txt[100] = '\0';
    enc[999900] = '\0';
    start = clock();
    crypteMove_decoder_fast(enc, txt);
    end = clock();
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
    envoyer_recevoir(passe, reponse);

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    crypteMove_decoder_fast(reponse, txt);
    printf("\n%s\n", txt);
    txt[0] = '\0';

    envoyer_recevoir("C'est fini?", reponse);
    printf("%f seconds to execute \n", cpu_time_used);
    return 0;
}