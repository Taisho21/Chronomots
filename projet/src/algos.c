#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/projet.h"
#include "../include/algo.h" // au cas ou on se trompe dans l'ecrtiture du proto ( permet de verifier la coherence)

int compteur(Liste l){ //compte le nombre noeuds/cellules de la liste chainee
    int longueur = 0;
    while(l != NULL){
        longueur ++;
        l = l->suivant;
    }
    return longueur;
}

int est_mieux_place(Mot *a, Mot *b) { // verifie si l'ordre de deux cellules (selon le nombre d'occurrences) sont bien placees, sinon on echange
    if (a->occurrences > b->occurrences) return 1;
    if (a->occurrences < b->occurrences) return 0;
    char *s1 = a->mot;
    char *s2 = b->mot;

    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }

    if (*s1 < *s2) {
        return 1;
    }

    return 0;
}



void fusion(Liste *un, Liste *deux, int est_double) {  //fusion combinee
    if (*un == NULL) {
        *un = *deux;
        if (est_double && *un != NULL) (*un)->precedent = NULL;
        *deux = NULL;
        return;
    }
    if (*deux == NULL) return;

    Noeud *p1 = *un;
    Noeud *p2 = *deux;
    Noeud *head = NULL;
    Noeud *back = NULL;

    // Choix du premier élément
    if (est_mieux_place(&p1->mot, &p2->mot)) {
        head = p1; p1 = p1->suivant;
    } else {
        head = p2; p2 = p2->suivant;
    }
    
    if (est_double) head->precedent = NULL; // On n'active que si demandé
    back = head;

    while (p1 != NULL && p2 != NULL) {
        if (est_mieux_place(&p1->mot, &p2->mot)) {
            back->suivant = p1;
            if (est_double) p1->precedent = back; // Mise à jour conditionnelle
            back = p1; p1 = p1->suivant;
        } else {
            back->suivant = p2;
            if (est_double) p2->precedent = back; // Mise à jour conditionnelle
            back = p2; p2 = p2->suivant;
        }
    }

    // Rattachement final
    if (p1 != NULL) {
        back->suivant = p1;
        if (est_double) p1->precedent = back;
    } else {
        back->suivant = p2;
        if (est_double) p2->precedent = back;
    }

    *un = head;
    *deux = NULL;
}
void diviserListe(Liste source, Liste *gauche, Liste *droite) {
    if(source == NULL || source->suivant == NULL){
        *gauche = source;
        *droite = NULL;
        return;
    }
    int longueur = compteur(source);
    Noeud *courant = source;

    int milieu = (longueur-1)/2;

    courant = source;
    for(int i =0; i<milieu ; i++){
        courant = courant->suivant;
    }
    *gauche = source;
    *droite = courant->suivant;
    if (*droite != NULL) (*droite)->precedent = NULL; // Nettoyage du lien retour (cas ou c'est une double liste chainee)
    courant->suivant = NULL;
    courant->suivant = NULL;
}


void triFusion(Liste *lst, int est_double) { // Ajoutez le paramètre ici
    Noeud *tete = *lst;
    if (tete == NULL || tete->suivant == NULL) {
        return; 
    }

    Liste a = NULL;
    Liste b = NULL;

    diviserListe(tete, &a, &b);

    // Transmettez le flag aux appels récursifs
    triFusion(&a, est_double);
    triFusion(&b, est_double);

    *lst = a;       
    fusion(lst, &b, est_double); // Transmettez le flag à la fusion
}
//j'ai copié tri a bulle AP2 L1 en changeant la deuxième boucle J parce qu'on est sur des listes chainées.

void tri_bulle(Liste *lst, int est_double) { //le parametre est utile pour la coherence des signatures et pour le main, il ne change pas le fonctionnement en soit 
    int n = compteur(*lst);

    for(int i = 0; i < n - 1; i++) {
        Noeud *actu = *lst;
        for(int j = 0; j < n - 1 - i; j++) {
            Noeud *suiv = actu->suivant;
            if(suiv != NULL) {
                if(!est_mieux_place(&actu->mot, &suiv->mot)) {  // jai change la condition, on utilise est_mieux, si on veut avoir le meme ordre que tri fusion
                    Mot temp = actu->mot;
                    actu->mot = suiv->mot;
                    suiv->mot = temp;
                }
            }
            actu = actu->suivant;
        }
    }
}


void ajouter_dans_liste(Liste *tete, char *nouveau_mot, InfoMem *mem, int est_double) {
    Liste courant = *tete;
    while (courant != NULL) {
        if (strcmp(courant->mot.mot, nouveau_mot) == 0) { //strcmp compare deux chaines de caracteres
            courant->mot.occurrences++;
            myFree(nouveau_mot, mem, strlen(nouveau_mot) + 1);
            return; 
        }
        courant = courant->suivant;
    }


    Noeud* nouveau = (Noeud*)myMalloc(sizeof(Noeud), mem);  //combinaisons des deux
    nouveau->mot.mot = nouveau_mot;
    nouveau->mot.occurrences = 1;
    nouveau->suivant = *tete;
    nouveau->precedent = NULL;

   if (est_double && *tete != NULL) {
        (*tete)->precedent = nouveau; // Lien retour uniquement en mode double
    }
    *tete = nouveau;
}



void afficher_liste(Liste tete, int n) {
    int compt = 0;

    while (tete != NULL && (n ==0 || compt < n) ) { // si n = 0 alors on prend tout car h24 vrai sinon si c faux on regarde compt 
    printf("Mot: %s | Occurrences: %d\n", tete->mot.mot, tete->mot.occurrences);
    tete = tete->suivant;
    compt ++;
    }
    printf("\n");
}