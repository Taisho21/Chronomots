#define LECTURE_H

#include <stdio.h>       
#include "projet.h"      


char* lire_mot_dynamique(FILE *f, InfoMem *infoMem);
void saisir_mots_bannis(ListeBan *liste,int n);
int est_mot_banni(char *mot, ListeBan *liste);