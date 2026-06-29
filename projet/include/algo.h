#ifndef ALGOS_H
#define ALGOS_H

#include "projet.h"

void ajouter_dans_liste(Liste *tete, char *nouveau_mot, InfoMem *mem, int est_double);
void triFusion(Liste *lst, int est_double);
void tri_bulle(Liste *lst, int est_double);
void afficher_liste(Liste tete,int n);
void tri_bulle_tab(Tableau *t);
void tri_rapide_tab(Tableau *t);
void init_tab(Tableau *t);
void ajouter_dans_tableau(Tableau *t, char *mot);
void afficher_tableau(Tableau *t, int n);
int est_mieux_place(Mot *a, Mot *b);
#endif