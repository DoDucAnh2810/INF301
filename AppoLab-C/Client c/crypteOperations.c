#include "client.h"
#include <stdio.h>
#include <string.h>

void crypteMove_encoder(char * txt, char * enc) {
    char buffer[MAXREP]; 
    int i = 0, j, mod_8, len;
    while (txt[0] != '\0') {
        enc[i++] = txt[0];
        mod_8 = txt[0] % 8;
        len = strlen(txt);
        if (len > mod_8) {
            for (j = 0; j < mod_8; j++) {
                buffer[j] = txt[j+1];
            }
            buffer[mod_8] = '\0';
            for (j = mod_8 + 1; j <= len; j++) {
                txt[j - mod_8 - 1] = txt[j];
            }
            strcat(txt, buffer);
        } else {
            for (j = 1; j <= len; j++) {
                txt[j-1] = txt[j];
            }
        }
    }
    enc[i] = '\0';
}

void crypteMove_decoder(char * enc, char * txt) {
    char buffer[MAXREP]; 
    int len_txt, id_enc, mod_8, i;
    len_txt = 0;
    id_enc = strlen(enc) - 1;
    
    while (id_enc >= 0) {
        mod_8 = enc[id_enc] % 8;
        if (len_txt > mod_8) {
            strcpy(buffer, txt + len_txt - mod_8);
            txt[len_txt - mod_8] = '\0';
            strcat(buffer, txt);
            strcpy(txt + 1, buffer);
        } else {
            for (i = len_txt; i >= 0; i--) {
                txt[i+1] = txt[i];
            }
        }
        txt[0] = enc[id_enc--];
        len_txt++;
    }
    txt[len_txt] = '\0';
}

void crypteSeq_encoder(char * txt, char * enc) {
    char seq[256] = "";
    char * seen_pt; int seen_loc;
    char tmp_char; int i;
    unsigned long global_id = 0; int len_seq = 0;
    while (global_id < strlen(txt)) {
        seen_pt = strchr(seq, txt[global_id]);
        if (seen_pt == NULL) {
            enc[global_id] = txt[global_id];
            seq[len_seq] = txt[global_id];
            seq[len_seq + 1] = '\0';
            len_seq++;
        } else {
            seen_loc = seen_pt - seq;
            tmp_char = seq[seen_loc];
            if (seen_loc == 0) 
                enc[global_id] = seq[len_seq - 1];
            else 
                enc[global_id] = seq[seen_loc - 1];
            if (seen_loc < len_seq - 1) {
                for (i = seen_loc + 1; i < len_seq; i++) {
                    seq[i-1] = seq[i];
                }
                seq[len_seq - 1] = tmp_char;
            }
        }
        global_id++;
    }
    enc[global_id] = '\0';
}

void crypteSeq_decoder(char * enc, char * txt) {
    char seq[256] = "";
    char * seen_pt; int seen_loc; int replace_loc;
    char tmp_char; int i;
    unsigned long global_id = 0; int len_seq = 0;
    while (global_id < strlen(enc)) {
        seen_pt = strchr(seq, enc[global_id]);
        if (seen_pt == NULL) {
            txt[global_id] = enc[global_id];
            seq[len_seq] = enc[global_id];
            seq[len_seq + 1] = '\0';
            len_seq++;
        } else {
            seen_loc = seen_pt - seq;
            if (seen_loc == len_seq - 1) 
                replace_loc = 0;
            else 
                replace_loc = seen_loc + 1;
            txt[global_id] = seq[replace_loc];
            tmp_char = seq[replace_loc];
            if (replace_loc < len_seq - 1) {
                for (i = replace_loc + 1; i < len_seq; i++) {
                    seq[i-1] = seq[i];
                }
                seq[len_seq - 1] = tmp_char;
            }
        }
        global_id++;
    }
    txt[global_id] = '\0';
}

void crypteAssoc_encoder(char * txt, char * enc) {
    char seq[256] = ""; char assoc[128];
    char * seen_pt; int seen_loc , replace_loc;
    int seen_char, replace_char, i; char buf_char;
    unsigned long global_id = 0; int len_seq = 0;
    while (global_id < strlen(txt)) {
        seen_char = txt[global_id];
        seen_pt = strchr(seq, seen_char);
        if (seen_pt == NULL) {
            seq[len_seq] = txt[global_id];
            seq[len_seq + 1] = '\0';
            len_seq++;
            assoc[seen_char] = seen_char;
        } else {
            seen_loc = seen_pt - seq;
            if (seen_loc == 0)
                replace_loc = len_seq - 1;
            else
                replace_loc = seen_loc - 1;
            replace_char = seq[replace_loc];
            buf_char = assoc[seen_char];
            assoc[seen_char] = assoc[replace_char];
            assoc[replace_char] = buf_char;
            if (seen_loc < len_seq - 1) {
                for (i = seen_loc + 1; i < len_seq; i++) {
                    seq[i-1] = seq[i];
                }
                seq[len_seq - 1] = seen_char;
            }
        }
        enc[global_id] = assoc[seen_char];
        global_id++;
    }
    enc[global_id] = '\0';
}

void crypteAssoc_decoder(char * enc, char * txt) {
    char seq[256] = ""; char assoc[128];
    char * seen_pt; int seen_loc , replace_loc;
    int seen_char, replace_char, i; char buf_char;
    unsigned long global_id = 0; int len_seq = 0;
    while (global_id < strlen(enc)) {
        seen_char = enc[global_id];
        seen_pt = strchr(seq, seen_char);
        if (seen_pt == NULL) {
            seq[len_seq] = enc[global_id];
            seq[len_seq + 1] = '\0';
            len_seq++;
            assoc[seen_char] = seen_char;
        } else {
            seen_loc = seen_pt - seq;
            if (seen_loc == len_seq - 1)
                replace_loc = 0;
            else
                replace_loc = seen_loc + 1;
            replace_char = seq[replace_loc];
            buf_char = assoc[seen_char];
            assoc[seen_char] = assoc[replace_char];
            assoc[replace_char] = buf_char;
            if (seen_loc < len_seq - 1) {
                for (i = seen_loc + 1; i < len_seq; i++) {
                    seq[i-1] = seq[i];
                }
                seq[len_seq - 1] = seen_char;
            }
        }
        txt[global_id] = assoc[seen_char];
        global_id++;
    }
    txt[global_id] = '\0';
}