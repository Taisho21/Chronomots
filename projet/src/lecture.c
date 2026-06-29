#include <stdio.h>
#include <string.h>
#include <ctype.h> // Nécessaire pour isalpha et tolower
#include "../include/projet.h"

char* lire_mot_dynamique(FILE *f, InfoMem *mem) {
    int c;
    char *mot = NULL;
    size_t taille = 0;
    int en_cours = 0; 

    while ((c = fgetc(f)) != EOF) {
        // Vérification : si le caractère n'est PAS une lettre, ni un tiret, ni une apostrophe
        if (!isalpha(c) && (c != '-') && (c != '\'')) { //isalpha permet de tester si un caractère est alphabétique
            if (en_cours) {                             // c!= '\'' afin de prendre en compte le ' sinon ça fait ''' 
                mot = myRealloc(mot, taille + 1, mem, taille);  // On alloue un dernier octet pour le caractère de fin de chaîne '\0'
                mot[taille] = '\0';
                return mot; // On retourne le mot complet au programme
            }
        } 
        // Sinon, on ignore simplement les espaces/ponctuations avant le prochain mot
        else {
            en_cours = 1;
            // Si mot est NULL, myRealloc devient comme un myMalloc
            mot = myRealloc(mot, taille + 1, mem, taille);
            mot[taille] = tolower(c);  // On stocke le caractère converti en minuscule
            taille++;
        }
    }
    // gestion du cas ou le fichier se termine juste après un mot
    if (taille > 0) {
        mot = myRealloc(mot, taille + 1, mem, taille);
        mot[taille] = '\0';
        return mot;
    }

    return NULL; // renvoie NULL si on atteint EOF sans avoir trouve aucun mot
}


void saisir_mots_bannis(ListeBan *liste, int n) {


    if (n > MAX_MOT_BAN) {
        printf("C'est trop ! Je limite a %d mots.\n", MAX_MOT_BAN);
        n = MAX_MOT_BAN;
    }

    liste->nombre_mot = 0; 

    if (n <= 0) return;
    if(n == 0)return;

    printf("Entrez les %d mots (separes par espace) :\n", n);
    for (int i = 0; i < n; i++) {
        // On écrit directement dans le tableau
        scanf("%s", liste->tab[i]); 

        // On convertit tout en minuscule pour être sûr que ça marche
        for(int j = 0; liste->tab[i][j] != '\0' ; j++){
            liste->tab[i][j] = tolower(liste->tab[i][j]);
        }
        
        liste->nombre_mot++;
    }

}

int est_mot_banni(char *mot, ListeBan *liste) {
    // On parcourt le tableau des mots interdits
    if(liste->nombre_mot == 0)return 0;
    for (int i = 0; i < liste->nombre_mot; i++) {
        if (strcmp(mot, liste->tab[i]) == 0) {
            return 1; // VRAI : le mot est interdit
        }
    }
    return 0; // FAUX : le mot est accepté
}