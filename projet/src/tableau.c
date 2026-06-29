#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/projet.h"
#include "../include/lecture.h"
#include "../include/algo.h"

void init_tab(Tableau *t){
    t->capacite = 10;
    t->taille = 0;
    t->tab = (Mot*)malloc(sizeof(Mot)*t->capacite);
}


void ajouter_dans_tableau(Tableau *t, char *mot){
    for(int i = 0; i<t->taille; i ++){
        if(strcmp(t->tab[i].mot, mot) == 0){ //si mot dedans ++ occurence
            t->tab[i].occurrences ++;
            return;
        }
    }
    if(t->taille >= t->capacite){ //Augmenter MEMOIRE
        t->capacite *=2;
        t->tab = realloc(t->tab, sizeof(Mot)*t->capacite);

    }
    //il existe pas donc il est la 
    t->tab[t->taille].mot = mot;
    t->tab[t->taille].occurrences = 1;
    t->taille ++;

}


void tri_bulle_tab(Tableau *t) {
    for (int i = 0; i < t->taille - 1; i++) {
        for (int j = 0; j < t->taille - 1 - i; j++) {

            if (est_mieux_place(&t->tab[j+1], &t->tab[j])) {//& parce que estmieux place attend des pointeurs
                Mot temp = t->tab[j];
                t->tab[j] = t->tab[j+1];
                t->tab[j+1] = temp;
            }
        }
    }
}

int comparateur_mots(const void *a, const void *b) {
    // On "cast" en Mot* pour accéder aux champs
    const Mot *elementA = (const Mot *)a;
    const Mot *elementB = (const Mot *)b;

    int diff = elementB->occurrences - elementA->occurrences;
    
    if (diff != 0) return diff;

    return strcmp(elementA->mot, elementB->mot); //si diff 0 on regarde ordre alphabétique

}

void tri_rapide_tab(Tableau *t) {
    qsort(t->tab, t->taille, sizeof(Mot), comparateur_mots);
}

void afficher_tableau(Tableau *t, int n) {
    int max = (n == 0 || n > t->taille) ? t->taille : n; //pareil que l'autre si n == 0 alors on parcourt tout sinon on stop à n
    for (int i = 0; i < max; i++) {
        printf("Mot: %s | Occurrences: %d\n", t->tab[i].mot, t->tab[i].occurrences);
    }
}