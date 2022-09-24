#ifndef __CRYPTEOPERATIONS_H__
#define __CRYPTEOPERATIONS_H__
#include "client.h"
#include <stdio.h>
#include <string.h>

void crypteMove_encoder(char * txt, char * enc);

void crypteMove_decoder(char * enc, char * txt);

void crypteSeq_encoder(char * txt, char * enc);

void crypteSeq_decoder(char * enc, char * txt);

void crypteAssoc_encoder(char * txt, char * enc);

void crypteAssoc_decoder(char * enc, char * txt);

#endif